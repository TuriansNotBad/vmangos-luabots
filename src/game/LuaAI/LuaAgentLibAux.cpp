
#include "LuaAgentLibPlayer.h"
#include "LuaAgentLibUnit.h"
#include "LuaAgentLibAux.h"
#include "LuaAgentLibWorldObj.h"
#include "LuaAgentUtils.h"
#include "LuaAgentMgr.h"
#include "ScriptedInstance.h"
#include "GridNotifiers.h"
#include "GridSearchers.h"
#include "eastern_kingdoms/dun_morogh/gnomeregan/gnomeregan.h"
#include "PathFinder.h"


enum
{
	NPC_WALKING_BOMB = 7915
};


namespace
{
	class AllObjectsOfEntry
	{
	public:
		AllObjectsOfEntry(uint32 uiEntry) : m_uiEntry(uiEntry){}
		bool operator() (Object* pUnit) { return pUnit->GetEntry() == m_uiEntry; }

	private:
		uint32 m_uiEntry;
	};

	class AllObjects
	{
	public:
		AllObjects() {}
		bool operator() (Object* pUnit) { return true; }
	};

	class AllCreatures
	{
	public:
		AllCreatures(bool aliveOnly) : m_alive(aliveOnly) {}
		bool operator() (Unit* pUnit) { return !m_alive || pUnit->IsAlive(); }
		
	private:
		bool m_alive;
	};

	class AllCreaturesEx
	{
	public:
		AllCreaturesEx(Unit* searcher, bool aliveOnly, ReputationRank repLTE, bool allowPlayers, uint32 entry, float zr, bool bPath)
			: m_alive(aliveOnly), m_searcher(searcher), m_allowPlayers(allowPlayers), m_repLTE(repLTE), m_entry(entry), m_checkPath(bPath), m_zr(zr) {}
		bool operator() (Unit* pUnit)
		{
			if (m_alive && !pUnit->IsAlive()) return false;
			if (pUnit->GetReactionTo(m_searcher) > m_repLTE) return false;
			if (pUnit->IsPlayer() != m_allowPlayers) return false;
			if (m_entry > 0 && pUnit->GetEntry() != m_entry) return false;
			if (m_zr > 0.f && std::abs(pUnit->GetPositionZ() - m_searcher->GetPositionZ()) > m_zr) return false;
			if (m_checkPath)
			{
				if (pUnit->GetDistance(m_searcher, SizeFactor::None) < 1.f)
					return pUnit->IsWithinLOSInMap(m_searcher);
				PathFinder path(m_searcher);
				path.calculate(pUnit->GetPositionX(), pUnit->GetPositionY(), pUnit->GetPositionZ(), false);
				PathType pathType = path.getPathType();
				if (pathType & PATHFIND_NORMAL)
				{
					path.CutPathWithDynamicLoS();
					if (path.getPath().size() < 2) return false;
					return path.Length() > 0.1f;
				}
				return false;
			}
			return true;
		}

	private:
		float m_zr;
		bool m_alive, m_allowPlayers, m_checkPath;
		ReputationRank m_repLTE;
		Unit* m_searcher;
		uint32 m_entry;
	};

	class AllCreaturesOfEntry
	{
	public:
		AllCreaturesOfEntry(uint32 uiEntry, bool aliveOnly) : m_uiEntry(uiEntry), m_alive(aliveOnly) {}
		bool operator() (Unit* pUnit) { return pUnit->GetEntry() == m_uiEntry && (!m_alive || pUnit->IsAlive()); }

	private:
		uint32 m_uiEntry;
		bool m_alive;
	};

	void GetCreatureListAt(std::list<Creature*>& lList, float x, float y, Map* map, float fMaxRange, bool aliveOnly, bool dont_load)
	{
		ASSERT(map);
		AllCreatures check(aliveOnly);
		MaNGOS::CreatureListSearcher<AllCreatures> searcher(lList, check);
		Cell::VisitGridObjects(x, y, map, searcher, fMaxRange, dont_load);
	}

	void GetCreatureListAtEx(std::list<Creature*>& lList, float x, float y, Unit* seeker, float r,  float zr, bool aliveOnly, bool allowPlayers, ReputationRank repLTE, uint32 entry, bool checkPath, bool dont_load)
	{
		Map* map = seeker->GetMap();
		ASSERT(map);
		AllCreaturesEx check(seeker, aliveOnly, repLTE, allowPlayers, entry, zr, checkPath);
		MaNGOS::CreatureListSearcher<AllCreaturesEx> searcher(lList, check);
		Cell::VisitGridObjects(x, y, map, searcher, r, dont_load);
	}

	void GetObjectListAt(std::list<GameObject*>& lList, float x, float y, Map* map, float fMaxSearchRange, bool dont_load)
	{
		ASSERT(map);
		AllObjects check;
		MaNGOS::GameObjectListSearcher<AllObjects> searcher(lList, check);
		Cell::VisitGridObjects(x, y, map, searcher, fMaxSearchRange, dont_load);
	}

	void GetCreatureListWithEntryAt(std::list<Creature*>& lList, float x, float y, Map* map, uint32 entry, float fMaxRange, bool aliveOnly, bool dont_load)
	{
		ASSERT(map);
		AllCreaturesOfEntry check(entry, aliveOnly);
		MaNGOS::CreatureListSearcher<AllCreaturesOfEntry> searcher(lList, check);
		Cell::VisitGridObjects(x, y, map, searcher, fMaxRange, dont_load);
	}

	void GetObjectListWithEntryAt(std::list<GameObject*>& lList, float x, float y, Map* map, uint32 entry, float fMaxSearchRange, bool dont_load)
	{
		ASSERT(map);
		AllObjectsOfEntry check(entry);
		MaNGOS::GameObjectListSearcher<AllObjectsOfEntry> searcher(lList, check);
		Cell::VisitGridObjects(x, y, map, searcher, fMaxSearchRange, dont_load);
	}

	int GetUnitsHelper(lua_State* L, Unit* unit, float x, float y, float z, float r, float zr, bool alive_only, bool allow_players, lua_Integer repLTE, lua_Integer entry, bool check_path, bool dont_load)
	{
		if (repLTE < 0 || repLTE >= MAX_REPUTATION_RANK)
			luaL_error(L, "GetUnitsNearEx: invalid rep rank. Got %lld, allowed [0, %d)", repLTE, MAX_REPUTATION_RANK);

		lua_newtable(L);

		if (r > 0.f)
		{
			std::list<Creature*> units;
			GetCreatureListAtEx(units, x, y, unit, r, zr, alive_only, allow_players, ReputationRank(repLTE), entry, check_path, dont_load);
			lua_Integer idx = 1;
			for (auto& u : units)
			{
				lua_pushunitornil(L, u);
				lua_seti(L, -2, idx);
				++idx;
			}
		}

		return 1;
	}
}


void LuaBindsAI::BindLibAux(lua_State* L)
{
	lua_register(L, "import", import);
	lua_register(L, "GetUnitByGuid", GetUnitByGuid);
	lua_register(L, "GetUnitByGuidEx", GetUnitByGuidEx);
	lua_register(L, "GetUnitsNear", GetUnitsNear);
	lua_register(L, "GetUnitsAroundEx", GetUnitsAroundEx);
	lua_register(L, "GetUnitsNearEx", GetUnitsNearEx);
	lua_register(L, "GetObjectsNear", GetObjectsNear);
	lua_register(L, "GetUnitsWithEntryNear", GetUnitsWithEntryNear);
	lua_register(L, "GetObjectsWithEntryNear", GetObjectsWithEntryNear);
	lua_register(L, "GetObjectsWithEntryAround", GetObjectsWithEntryAround);
	lua_register(L, "GetObjectGOState", GetObjectGOState);
	lua_register(L, "GetObjectLootState", GetObjectLootState);
	lua_register(L, "GetObjectIsSpawned", GetObjectIsSpawned);
	lua_register(L, "GetPlayerByGuid", GetPlayerByGuid);
	lua_register(L, "GetPlayerById", GetPlayerById);
	lua_register(L, "GetSpellName", GetSpellName);
	lua_register(L, "isinteger", isinteger);
	lua_register(L, "Gnomeregan_GetFaceData", Gnomeregan_GetFaceData);
	lua_register(L, "Gnomeregan_GetBombs", Gnomeregan_GetBombs);
}


int LuaBindsAI::import(lua_State* L)
{
	std::string fname(luaL_checkstring(L, 1));
	sLuaAgentMgr.LuaDofile(fname);
	return 0;
}


int LuaBindsAI::isinteger(lua_State* L)
{
	lua_pushboolean(L, lua_isinteger(L, 1));
	return 1;
}


int LuaBindsAI::GetUnitByGuid(lua_State* L) {
	Player* player = Player_GetPlayerObject(L);
	const ObjectGuid& guid = Guid_GetGuidObject(L, 2)->guid;
	if (guid.IsEmpty())
		luaL_error(L, "GetUnitByGuid: guid was empty");
	lua_pushunitornil(L, player->GetMap()->GetUnit(guid));
	return 1;
}


int LuaBindsAI::GetUnitByGuidEx(lua_State* L) {
	Player* player = Player_GetPlayerObject(L);
	lua_Integer e = luaL_checkinteger(L, 2);
	lua_Integer c = luaL_checkinteger(L, 3);
	if (e < 0 || c < 0)
		luaL_error(L, "GetUnitByGuidEx: got negative number");
	ObjectGuid guid(HighGuid::HIGHGUID_UNIT, uint32(e), uint32(c));
	lua_pushunitornil(L, player->GetMap()->GetUnit(guid));
	return 1;
}


int LuaBindsAI::GetPlayerByGuid(lua_State* L) {
	const ObjectGuid& guid = Guid_GetGuidObject(L)->guid;
	if (guid.IsEmpty())
		luaL_error(L, "GetPlayerByGuid: guid was empty");
	lua_pushplayerornil(L, sObjectAccessor.FindPlayer(guid));
	return 1;
}


int LuaBindsAI::GetPlayerById(lua_State* L) {
	lua_Integer id = luaL_checkinteger(L, 1);
	if (id <= 0 || id > std::numeric_limits<uint32>::max())
		luaL_error(L, "GetPlayerById: id must be a valid uint32 != 0, got %I", id);
	ObjectGuid guid(HighGuid::HIGHGUID_PLAYER, uint32(id));
	lua_pushplayerornil(L, sObjectAccessor.FindPlayer(guid));
	return 1;
}


int LuaBindsAI::GetSpellName(lua_State* L) {
	lua_Integer spellID = luaL_checkinteger(L, 1);
	auto info_orig = sSpellMgr.GetSpellEntry(spellID);
	// spell not found
	if (!info_orig)
		luaL_error(L, "GetSpellName: spell %d not found", spellID);
	lua_pushstring(L, info_orig->SpellName[0].c_str());
	return 1;
}


int LuaBindsAI::GetObjectsNear(lua_State* L)
{
	Unit* unit = Unit_GetUnitObject(L, 1);
	lua_Number x = luaL_checknumber(L, 2);
	lua_Number y = luaL_checknumber(L, 3);
	lua_Number z = luaL_checknumber(L, 4);
	lua_Number r = luaL_checknumber(L, 5);
	bool dont_load = luaL_checkboolean(L, 6);

	lua_newtable(L);

	if (r > 0.f)
	{
		std::list<GameObject*> objs;
		GetObjectListAt(objs, x, y, unit->GetMap(), r, dont_load);
		lua_Integer idx = 1;
		for (auto& u : objs)
		{
			Guid_CreateUD(L, u->GetObjectGuid());
			lua_seti(L, -2, idx);
			++idx;
		}
	}

	return 1;
}


int LuaBindsAI::GetUnitsNear(lua_State* L)
{
	Unit* unit = Unit_GetUnitObject(L, 1);
	lua_Number x = luaL_checknumber(L, 2);
	lua_Number y = luaL_checknumber(L, 3);
	lua_Number z = luaL_checknumber(L, 4);
	lua_Number r = luaL_checknumber(L, 5);
	bool alive_only = luaL_checkboolean(L, 6);
	bool dont_load = luaL_checkboolean(L, 7);

	lua_newtable(L);

	if (r > 0.f)
	{
		std::list<Creature*> units;
		GetCreatureListAt(units, x, y, unit->GetMap(), r, alive_only, dont_load);
		lua_Integer idx = 1;
		for (auto& u : units)
		{
			lua_pushunitornil(L, u);
			lua_seti(L, -2, idx);
			++idx;
		}
	}

	return 1;
}


int LuaBindsAI::GetUnitsAroundEx(lua_State* L)
{
	Unit* unit = Unit_GetUnitObject(L, 1);
	lua_Number r = luaL_checknumber(L, 2);
	lua_Number zr = luaL_checknumber(L, 3);
	bool alive_only = luaL_checkboolean(L, 4);
	bool allow_players = luaL_checkboolean(L, 5);
	lua_Integer repLTE = luaL_checkinteger(L, 6);
	lua_Integer entry = luaL_checkinteger(L, 7);
	bool check_path = luaL_checkboolean(L, 8);
	bool dont_load = luaL_checkboolean(L, 9);

	return GetUnitsHelper(L, unit, unit->GetPositionX(), unit->GetPositionY(), unit->GetPositionZ(), r, zr, alive_only, allow_players, repLTE, entry, check_path, dont_load);
}


int LuaBindsAI::GetUnitsNearEx(lua_State* L)
{
	Unit* unit = Unit_GetUnitObject(L, 1);
	lua_Number x = luaL_checknumber(L, 2);
	lua_Number y = luaL_checknumber(L, 3);
	lua_Number z = luaL_checknumber(L, 4);
	lua_Number r = luaL_checknumber(L, 5);
	lua_Number zr = luaL_checknumber(L, 6);
	bool alive_only = luaL_checkboolean(L, 7);
	bool allow_players = luaL_checkboolean(L, 8);
	lua_Integer repLTE = luaL_checkinteger(L, 9);
	lua_Integer entry = luaL_checkinteger(L, 10);
	bool check_path = luaL_checkboolean(L, 11);
	bool dont_load = luaL_checkboolean(L, 12);

	return GetUnitsHelper(L, unit, x, y, z, r, zr, alive_only, allow_players, repLTE, entry, check_path, dont_load);
}


int LuaBindsAI::GetObjectsWithEntryNear(lua_State* L)
{
	Unit* unit = Unit_GetUnitObject(L, 1);
	lua_Integer entry = luaL_checkinteger(L, 2);
	lua_Number x = luaL_checknumber(L, 3);
	lua_Number y = luaL_checknumber(L, 4);
	lua_Number z = luaL_checknumber(L, 5);
	lua_Number r = luaL_checknumber(L, 6);
	bool dont_load = luaL_checkboolean(L, 7);

	if (entry <= 0)
		luaL_error(L, "GetObjectsWithEntryNear: entry must be positive");

	lua_newtable(L);

	if (r > 0.f)
	{
		std::list<GameObject*> objs;
		GetObjectListWithEntryAt(objs, x, y, unit->GetMap(), entry, r, dont_load);
		lua_Integer idx = 1;
		for (auto& u : objs)
		{
			Guid_CreateUD(L, u->GetObjectGuid());
			lua_seti(L, -2, idx);
			++idx;
		}
	}

	return 1;
}


int LuaBindsAI::GetObjectsWithEntryAround(lua_State* L)
{
	Unit* unit = Unit_GetUnitObject(L, 1);
	lua_Integer entry = luaL_checkinteger(L, 2);
	lua_Number r = luaL_checknumber(L, 3);
	bool dont_load = luaL_checkboolean(L, 4);

	if (entry <= 0)
		luaL_error(L, "_GetObjectsWithEntryNear: entry must be positive");

	lua_newtable(L);

	if (r > 0.f)
	{
		std::list<GameObject*> objs;
		GetObjectListWithEntryAt(objs, unit->GetPositionX(), unit->GetPositionY(), unit->GetMap(), entry, r, dont_load);
		lua_Integer idx = 1;
		for (auto& u : objs)
		{
			Guid_CreateUD(L, u->GetObjectGuid());
			lua_seti(L, -2, idx);
			++idx;
		}
	}

	return 1;
}


int LuaBindsAI::GetUnitsWithEntryNear(lua_State* L)
{
	Unit* unit = Unit_GetUnitObject(L, 1);
	lua_Integer entry = luaL_checkinteger(L, 2);
	lua_Number x = luaL_checknumber(L, 3);
	lua_Number y = luaL_checknumber(L, 4);
	lua_Number z = luaL_checknumber(L, 5);
	lua_Number r = luaL_checknumber(L, 6);
	bool alive_only = luaL_checkboolean(L, 7);
	bool dont_load = luaL_checkboolean(L, 8);

	if (entry <= 0)
		luaL_error(L, "_GetUnitsWithEntryNear: entry must be positive");

	lua_newtable(L);

	if (r > 0.f)
	{
		std::list<Creature*> units;
		GetCreatureListWithEntryAt(units, x, y, unit->GetMap(), entry, r, alive_only, dont_load);
		lua_Integer idx = 1;
		for (auto& u : units)
		{
			lua_pushunitornil(L, u);
			lua_seti(L, -2, idx);
			++idx;
		}
	}

	return 1;
}


int LuaBindsAI::GetObjectGOState(lua_State* L)
{
	Unit* unit = Unit_GetUnitObject(L, 1);
	ObjectGuid guid = Guid_GetGuidObject(L, 2)->guid;
	if (GameObject* go = unit->GetMap()->GetGameObject(guid))
	{
		lua_pushinteger(L, go->GetGoState());
		return 1;
	}
	return 0;
}


int LuaBindsAI::GetObjectLootState(lua_State* L)
{
	Unit* unit = Unit_GetUnitObject(L, 1);
	ObjectGuid guid = Guid_GetGuidObject(L, 2)->guid;
	if (GameObject* go = unit->GetMap()->GetGameObject(guid))
	{
		lua_pushinteger(L, go->getLootState());
		return 1;
	}
	return 0;
}


int LuaBindsAI::GetObjectIsSpawned(lua_State* L)
{
	Unit* unit = Unit_GetUnitObject(L, 1);
	ObjectGuid guid = Guid_GetGuidObject(L, 2)->guid;
	if (GameObject* go = unit->GetMap()->GetGameObject(guid))
	{
		lua_pushboolean(L, go->isSpawned());
		return 1;
	}
	return 0;
}


int LuaBindsAI::Gnomeregan_GetFaceData(lua_State* L)
{
	Player* player = Player_GetPlayerObject(L);
	if (player->GetZoneId() == 721u)
	{
		if (instance_gnomeregan* gnome = (instance_gnomeregan*) player->GetInstanceData())
		{
			const uint32 btnGuids[6] = {6582u, 6726u, 6748u, 11977u, 14140u, 15766u};
			const uint32 btnEntry[6] = {GO_BUTTON_1, GO_BUTTON_2, GO_BUTTON_3, GO_BUTTON_4, GO_BUTTON_5, GO_BUTTON_6};

			sBombFace* faces = gnome->GetBombFaces();
			lua_newtable(L);
			for (int i = 0; i < MAX_GNOME_FACES; ++i)
			{
				lua_newtable(L);
				lua_pushboolean(L, faces[i].m_bActivated);
				lua_setfield(L, -2, "active");
				lua_pushinteger(L, faces[i].m_uiBombTimer);
				lua_setfield(L, -2, "timer");
				Guid_CreateUD(L, ObjectGuid(faces[i].m_uiGnomeFaceGUID));
				lua_setfield(L, -2, "guid");
				ObjectGuid btnGuid(HIGHGUID_GAMEOBJECT, btnEntry[i], btnGuids[i]);
				Guid_CreateUD(L, btnGuid);
				lua_setfield(L, -2, "btnGuid");
				lua_seti(L, -2, i + 1);
			}
			return 1;
		}
	}
	lua_pushnil(L);
	return 1;
}


int LuaBindsAI::Gnomeregan_GetBombs(lua_State* L)
{
	Player* player = Player_GetPlayerObject(L);
	std::list<Creature*> bombList;
	GetCreatureListWithEntryInGrid(bombList, player, NPC_WALKING_BOMB, 250.0f);
	lua_newtable(L);
	lua_Integer idx = 1;
	for (auto& bomb : bombList)
	{
		lua_pushunitornil(L, bomb);
		lua_seti(L, -2, idx);
		++idx;
	}
	return 1;
}
