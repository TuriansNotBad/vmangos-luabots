#ifndef MANGOS_LuaAgentLibAI_H
#define MANGOS_LuaAgentLibAI_H

#include "lua.hpp"

class LuaAgent;

namespace LuaBindsAI {

	// Creates metatable for the AI userdata with name specified by AI::AI_MTNAME
	void BindAI(lua_State* L);
	// Creates metatable for the AI userdata with name specified by AI::AI_MTNAME.
	// Registers all the functions listed in LuaBindsAI::AI_BindLib with that metatable.
	void AI_CreateMetatable(lua_State* L);
	LuaAgent* AI_GetAIObject(lua_State* L, int idx = 1);

	int AI_AddTopGoal(lua_State* L);

	// equip

	int AI_EquipCopyFromMaster(lua_State* L);
	int AI_EquipItem(lua_State* L);
	int AI_EquipDestroyAll(lua_State* L);
	int AI_EquipGetEnchantId(lua_State* L);
	int AI_EquipGetRandomProp(lua_State* L);
	int AI_EquipPrint(lua_State* L);
	int AI_UpdateVisibilityForMaster(lua_State* L);

	// commands

	int AI_CmdGetArgs(lua_State* L);
	int AI_CmdGetState(lua_State* L);
	int AI_CmdGetType(lua_State* L);
	int AI_CmdGetQMode(lua_State* L);
	int AI_CmdComplete(lua_State* L);
	int AI_CmdSetInProgress(lua_State* L);
	int AI_CmdFail(lua_State* L);
	int AI_CmdPrintAll(lua_State* L);

	int AI_GetSpec(lua_State* L);
	int AI_GetRole(lua_State* L);
	int AI_GetPartyIntelligence(lua_State* L);
	int AI_GetPlayer(lua_State* L);
	int AI_GetMaster(lua_State* L);
	int AI_GetMasterGuid(lua_State* L);

	int AI_SetRole(lua_State* L);

	static const struct luaL_Reg AI_BindLib[]{
		{"AddTopGoal", AI_AddTopGoal},

		// equip
		{"EquipCopyFromMaster", AI_EquipCopyFromMaster},
		{"EquipItem", AI_EquipItem},
		{"EquipDestroyAll", AI_EquipDestroyAll},
		{"EquipGetEnchantId", AI_EquipGetEnchantId},
		{"EquipGetRandomProp", AI_EquipGetRandomProp},
		{"EquipPrint", AI_EquipPrint},
		{"UpdateVisibilityForMaster", AI_UpdateVisibilityForMaster},

		// commands
		{"CmdArgs", AI_CmdGetArgs},
		{"CmdState", AI_CmdGetState},
		{"CmdType", AI_CmdGetType},
		{"CmdIsQMode", AI_CmdGetQMode},
		{"CmdComplete", AI_CmdComplete},
		{"CmdSetInProgress", AI_CmdSetInProgress},
		{"CmdFail", AI_CmdFail},
		{"CmdPrintAll", AI_CmdPrintAll},

		{"GetPartyIntelligence", AI_GetPartyIntelligence},
		{"GetRole", AI_GetRole},
		{"GetSpec", AI_GetSpec},
		{"GetMaster", AI_GetMaster},
		{"GetMasterGuid", AI_GetMasterGuid},
		{"GetPlayer", AI_GetPlayer},

		{"SetRole", AI_SetRole},

		{NULL, NULL}
	};

}

#endif