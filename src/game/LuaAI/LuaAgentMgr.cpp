
#include "LuaAgent.h"
#include "LuaAgentMgr.h"
#include "AccountMgr.h"
#include "Database/DatabaseImpl.h"
#include "Group.h"

class LuaAgentLoginQueryHolder : public LoginQueryHolder
{
public:
	int logicID;
	std::string spec;
	ObjectGuid masterGuid;
	LuaAgentLoginQueryHolder(uint32 accountId, ObjectGuid guid, ObjectGuid masterGuid, int logicID, std::string spec)
		: LoginQueryHolder(accountId, guid), masterGuid(masterGuid), logicID(logicID), spec(spec) { }
};


class LuaAgentCharacterHandler
{
public:
	void HandleLoginCallback(QueryResult* /*dummy*/, SqlQueryHolder* holder)
	{
		if (!holder)
			return;

		LuaAgentLoginQueryHolder* lqh = dynamic_cast<LuaAgentLoginQueryHolder*>(holder);
		if (!lqh) {
			sLog.Out(LOG_BASIC, LOG_LVL_ERROR, "LuaAgent - login callback failed to cast SqlQueryHolder");
			delete holder;
			return;
		}

		// copy holder values
		ObjectGuid masterGuid = lqh->masterGuid;
		ObjectGuid myGuid = lqh->GetGuid();
		int logicID = lqh->logicID;
		std::string spec = lqh->spec;

		// already logged in or master's gone
		if (!sObjectMgr.GetPlayer(lqh->masterGuid) || sObjectMgr.GetPlayer(lqh->GetGuid()))
		{
			delete holder;
			return;
		}

		// Deleted in LuaAgentMgr::LogoutAgent
		WorldSession* session = new WorldSession(lqh->GetAccountId(), nullptr, sAccountMgr.GetSecurity(lqh->GetAccountId()), 0, LOCALE_enUS);
		session->SetToLoading();
		session->HandlePlayerLogin(lqh); // will delete lqh
		sLuaAgentMgr.OnAgentLogin(session, myGuid, masterGuid, logicID, spec);

	}
} luaChrHandler;


LuaAgentMgr::LuaAgentMgr() : m_bLuaCeaseUpdates(false), m_bLuaReload(false), L(nullptr), m_bGroupAllInProgress(false)
{

}


LuaAgentMgr::~LuaAgentMgr()
{

}


void LuaAgentMgr::Update(uint32 diff)
{

	// reload requested
	if (m_bLuaReload)
	{
		sWorld.SendServerMessage(SERVER_MSG_CUSTOM, "Lua reload started");

		m_bLuaReload = false;
		m_bLuaCeaseUpdates = false;

		for (auto& agent : m_agents)
		{
			// reset all
		}

		sWorld.SendServerMessage(SERVER_MSG_CUSTOM, "Lua reload finished");
	}

	// lua error on initialization
	if (m_bLuaCeaseUpdates)
		return;

	for (auto& it : m_agents)
	{
		LuaAgent* agent = it.second->GetLuaAI();
		if (!agent)
		{
			LogoutAgent(it.first);
			continue;
		}

		agent->Update(diff);
		agent->UpdateSession(diff);
	}

	__AddAgents(); // process login queue
	__RemoveAgents(); // process logout queue

}


Player* LuaAgentMgr::GetAgent(ObjectGuid guid)
{
	LuaAgentMap::const_iterator it = m_agents.find(guid);
	return (it == m_agents.end()) ? nullptr : it->second;
}


const LuaAgentInfoHolder* LuaAgentMgr::GetLoginInfo(ObjectGuid guid)
{
	auto it = m_toAdd.find(guid);
	return (it == m_toAdd.end()) ? nullptr : &(it->second);
}


LuaAgentMgr::CheckResult LuaAgentMgr::CheckAgentValid(std::string charName, uint32 masterAccountId)
{
	ObjectGuid guid = sObjectMgr.GetPlayerGuidByName(charName);
	// character with name doesn't exist
	if (guid.IsEmpty())
		return CHAR_DOESNT_EXIST;
	// already logged in
	if (sObjectAccessor.FindPlayerNotInWorld(guid))
		return CHAR_ALREADY_LOGGED_IN;
	// bot's account doesn't exist
	if (sObjectMgr.GetPlayerAccountIdByGUID(guid) == 0)
		return CHAR_ACCOUNT_DOESNT_EXIST;
	// already a bot
	if (GetAgent(guid))
		return CHAR_ALREADY_EXISTS;
	// already queued to add as bot
	if (GetLoginInfo(guid))
		return CHAR_ALREADY_IN_QUEUE;
	// master logged out
	WorldSession* masterSession = sWorld.FindSession(masterAccountId);
	if (!masterSession)
		return CHAR_MASTER_SESSION_NOT_FOUND;
	// master on char select
	if (!masterSession->GetPlayer())
		return CHAR_MASTER_PLAYER_NOT_FOUND;
	return CHAR_OK;
}


LuaAgentMgr::CheckResult LuaAgentMgr::AddAgent(std::string charName, uint32 masterAccountId, int logicID, std::string spec)
{
	CheckResult check = CheckAgentValid(charName, masterAccountId);
	if (check == CHAR_OK)
		m_toAdd.emplace(sObjectMgr.GetPlayerGuidByName(charName), LuaAgentInfoHolder(charName, masterAccountId, logicID, spec));
	return check;
}


void LuaAgentMgr::__AddAgents()
{
	for (std::map<ObjectGuid, LuaAgentInfoHolder>::iterator it = m_toAdd.begin(); it != m_toAdd.end();)
	{
		LuaAgentInfoHolder& info = it->second;
		if (info.status != LuaAgentInfoHolder::OFFLINE)
		{
			it++;
			continue;
		}

		printf("__AddAgents processing %s\n", info.name.c_str());

		if (WorldSession* masterSession = sWorld.FindSession(info.masterAccountId))
		{
			if (!masterSession->GetPlayer())
			{
				it = m_toAdd.erase(it);
				continue;
			}

			ObjectGuid guid = sObjectMgr.GetPlayerGuidByName(info.name);
			uint32 accountId = sObjectMgr.GetPlayerAccountIdByGUID(guid);
			LuaAgentLoginQueryHolder* holder = new LuaAgentLoginQueryHolder(accountId, guid, masterSession->GetPlayer()->GetObjectGuid(), info.logicID, info.spec);
			if (!holder->Initialize())
			{
				delete holder;                                      // delete all unprocessed queries
				it = m_toAdd.erase(it);
				continue;
			}

			CharacterDatabase.DelayQueryHolder(&luaChrHandler, &LuaAgentCharacterHandler::HandleLoginCallback, holder);
			info.status = LuaAgentInfoHolder::LOADING;
		}
		else
		{
			it = m_toAdd.erase(it);
			continue;
		}
		it++;
	}
}


void LuaAgentMgr::OnAgentLogin(WorldSession* session, ObjectGuid guid, ObjectGuid masterGuid, int logicID, std::string spec)
{
	EraseLoginInfo(guid);
	Player* player = session->GetPlayer();
	if (!player)
	{
		LogoutAgent(guid);
		sLog.Out(LOG_BASIC, LOG_LVL_ERROR, "LuaAgent - player ptr is null after log in. Removing agent %s.", guid.GetString());
		return;
	}

	m_agents[player->GetObjectGuid()] = player;
	player->CreateLuaAI(player, masterGuid, logicID);

	LuaAgent* ai = player->GetLuaAI();
	if (!ai)
	{
		LogoutAgent(guid);
		sLog.Out(LOG_BASIC, LOG_LVL_ERROR, "LuaAgent - ai failed to create after log in. Removing agent %s.", guid.GetString());
		return;
	}
	ai->SetSpec(spec);
}


void LuaAgentMgr::__RemoveAgents()
{
	for (auto& guid : m_toRemove)
		if (Player* player = GetAgent(guid))
		{
			if (WorldSession* session = player->GetSession())
			{
				session->LogoutPlayer(true);
				delete session;
			}
			m_agents.erase(guid);
		}
	m_toRemove.clear();
}


void LuaAgentMgr::LogoutAgent(ObjectGuid guid)
{
	m_toRemove.insert(guid);
}


void LuaAgentMgr::LogoutAllAgents()
{
	for (auto& itr : m_agents)
		m_toRemove.insert(itr.first);
}


void LuaAgentMgr::ReviveAll(Player* owner, float hp, bool sickness)
{
	for (auto& itr : m_agents)
	{
		Player* player = itr.second;
		if (!player || player->IsAlive() || !player->IsInWorld() || player->IsBeingTeleported()) continue;

		LuaAgent* agent = player->GetLuaAI();
		Player* master = nullptr;
		if (agent)
			master = ObjectAccessor::FindPlayer(agent->GetMasterGuid());

		// owned bots only
		if (master && owner->GetObjectGuid() == agent->GetMasterGuid())
			player->ResurrectPlayer(hp, sickness);
	}
}


void LuaAgentMgr::GroupAll(Player* owner)
{
	m_bGroupAllInProgress = true;
	for (auto& itr : m_agents)
	{
		Player* player = itr.second;
		if (!player || !player->IsInWorld() || player->IsBeingTeleported() || player->GetGroupInvite()) continue;

		if (LuaAgent* agent = player->GetLuaAI())
		{
			Player* master = ObjectAccessor::FindPlayer(agent->GetMasterGuid());

			if (master && owner->GetObjectGuid() == agent->GetMasterGuid())
				// already in my group?
				if (Group* group = master->GetGroup())
				{
					if (group->IsMember(player->GetObjectGuid()))
						continue;

					std::unique_ptr<WorldPacket> packet = std::make_unique<WorldPacket>(CMSG_GROUP_INVITE);
					*packet << std::string(player->GetName());
					master->GetSession()->QueuePacket(std::move(packet));
				}
				else
				{
					// Adds agent and master to group in the same logic frame
					// Necessary as group isn't truly created until at least 2 players join
					// failing to invite more members in the same frame
					WorldPacket packet(CMSG_GROUP_INVITE);
					packet << std::string(player->GetName());
					master->GetSession()->HandleGroupInviteOpcode(packet);
				}
		}
	}
	m_bGroupAllInProgress = false;
}
