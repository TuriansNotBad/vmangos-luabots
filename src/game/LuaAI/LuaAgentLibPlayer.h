#ifndef MANGOS_LuaAgentLibPlayer_H
#define MANGOS_LuaAgentLibPlayer_H

#include "lua.hpp"

namespace LuaBindsAI {
	static const char* PlayerMtName = "LuaAI.Player";

	// Creates metatable for the AI userdata with name specified by AI::Unit_MTNAME
	void BindPlayer(lua_State* L);
	// Creates metatable for the AI userdata with name specified by AI::Unit_MTNAME.
	// Registers all the functions listed in LuaBindsBot::Unit_BindLib with that metatable.
	void Player_CreateMetatable(lua_State* L);
	Player* Player_GetPlayerObject(lua_State* L, int idx = 1);
	void Player_CreateUD(Player* player, lua_State* L);

	// talents

	int Player_GetTalentTbl(lua_State* L);
	int Player_GetTalentRank(lua_State* L);
	int Player_HasTalent(lua_State* L);
	int Player_LearnTalent(lua_State* L);
	int Player_ResetTalents(lua_State* L);

	// packets

	int Player_SendCastSpellUnit(lua_State* L);

	static const struct luaL_Reg Player_BindLib[]{
		// talents
		{"GetTalentTbl", Player_GetTalentTbl},
		{"GetTalentRank", Player_GetTalentRank},
		{"HasTalent", Player_HasTalent},
		{"LearnTalent", Player_LearnTalent},
		{"ResetTalents", Player_ResetTalents},

		// packets
		{"SendCastSpellUnit", Player_SendCastSpellUnit},

		{NULL, NULL}
	};


}

#endif