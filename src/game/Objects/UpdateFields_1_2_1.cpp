// Patch: 1.2.1
// Build: 4150

static std::array<UpdateFieldData, 230> const g_updateFieldsData =
{{
    { TYPEMASK_OBJECT, "OBJECT_FIELD_GUID", 0x000, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_OBJECT, "OBJECT_FIELD_TYPE", 0x002, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_OBJECT, "OBJECT_FIELD_ENTRY", 0x003, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_OBJECT, "OBJECT_FIELD_SCALE_X", 0x004, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_OBJECT, "OBJECT_FIELD_PADDING", 0x005, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_OBJECT, "OBJECT_END", 0x6, 0, UF_TYPE_NONE, UF_FLAG_NONE },
    { TYPEMASK_ITEM, "ITEM_FIELD_OWNER", 0x006, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM, "ITEM_FIELD_CONTAINED", 0x008, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM, "ITEM_FIELD_CREATOR", 0x00A, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM, "ITEM_FIELD_GIFTCREATOR", 0x00C, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM, "ITEM_FIELD_STACK_COUNT", 0x00E, 1, UF_TYPE_INT, UF_FLAG_OWNER_ONLY + UF_FLAG_UNK2 },
    { TYPEMASK_ITEM, "ITEM_FIELD_DURATION", 0x00F, 1, UF_TYPE_INT, UF_FLAG_OWNER_ONLY + UF_FLAG_UNK2 },
    { TYPEMASK_ITEM, "ITEM_FIELD_SPELL_CHARGES", 0x010, 5, UF_TYPE_INT, UF_FLAG_OWNER_ONLY + UF_FLAG_UNK2 },
    { TYPEMASK_ITEM, "ITEM_FIELD_FLAGS", 0x015, 1, UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM, "ITEM_FIELD_ENCHANTMENT", 0x016, 21, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM, "ITEM_FIELD_PROPERTY_SEED", 0x02B, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM, "ITEM_FIELD_RANDOM_PROPERTIES_ID", 0x02C, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM, "ITEM_FIELD_ITEM_TEXT_ID", 0x02D, 1, UF_TYPE_INT, UF_FLAG_OWNER_ONLY },
    { TYPEMASK_ITEM, "ITEM_FIELD_DURABILITY", 0x02E, 1, UF_TYPE_INT, UF_FLAG_OWNER_ONLY + UF_FLAG_UNK2 },
    { TYPEMASK_ITEM, "ITEM_FIELD_MAXDURABILITY", 0x02F, 1, UF_TYPE_INT, UF_FLAG_OWNER_ONLY + UF_FLAG_UNK2 },
    { TYPEMASK_ITEM, "ITEM_END", 0x030, 0, UF_TYPE_NONE, UF_FLAG_NONE },
    { TYPEMASK_CONTAINER, "CONTAINER_FIELD_NUM_SLOTS", 0x02A, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_CONTAINER, "CONTAINER_ALIGN_PAD", 0x02B, 1, UF_TYPE_BYTES, UF_FLAG_NONE },
    { TYPEMASK_CONTAINER, "CONTAINER_FIELD_SLOT_1", 0x02C, 40, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_CONTAINER, "CONTAINER_END", 0x054, 0, UF_TYPE_NONE, UF_FLAG_NONE },
    { TYPEMASK_UNIT, "UNIT_FIELD_CHARM", 0x006, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_SUMMON", 0x008, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_CHARMEDBY", 0x00A, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_SUMMONEDBY", 0x00C, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_CREATEDBY", 0x00E, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_TARGET", 0x010, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_PERSUADED", 0x012, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_CHANNEL_OBJECT", 0x014, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_HEALTH", 0x016, 1, UF_TYPE_INT, UF_FLAG_DYNAMIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_POWER1", 0x017, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_POWER2", 0x018, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_POWER3", 0x019, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_POWER4", 0x01A, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_POWER5", 0x01B, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_MAXHEALTH", 0x01C, 1, UF_TYPE_INT, UF_FLAG_DYNAMIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_MAXPOWER1", 0x01D, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_MAXPOWER2", 0x01E, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_MAXPOWER3", 0x01F, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_MAXPOWER4", 0x020, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_MAXPOWER5", 0x021, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_LEVEL", 0x022, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_FACTIONTEMPLATE", 0x023, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_BYTES_0", 0x024, 1, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_VIRTUAL_ITEM_SLOT_DISPLAY", 0x025, 3, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_VIRTUAL_ITEM_INFO", 0x028, 6, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_FLAGS", 0x02E, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_AURA", 0x02F, 56, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_AURALEVELS", 0x067, 10, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_AURAAPPLICATIONS", 0x071, 10, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_AURAFLAGS", 0x07B, 7, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_AURASTATE", 0x082, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_BASEATTACKTIME", 0x083, 2, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_RANGEDATTACKTIME", 0x085, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_UNIT, "UNIT_FIELD_BOUNDINGRADIUS", 0x086, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_COMBATREACH", 0x087, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_DISPLAYID", 0x088, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_NATIVEDISPLAYID", 0x089, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_MOUNTDISPLAYID", 0x08A, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_MINDAMAGE", 0x08B, 1, UF_TYPE_FLOAT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY + UF_FLAG_SPECIAL_INFO },
    { TYPEMASK_UNIT, "UNIT_FIELD_MAXDAMAGE", 0x08C, 1, UF_TYPE_FLOAT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY + UF_FLAG_SPECIAL_INFO },
    { TYPEMASK_UNIT, "UNIT_FIELD_MINOFFHANDDAMAGE", 0x08D, 1, UF_TYPE_FLOAT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY + UF_FLAG_SPECIAL_INFO },
    { TYPEMASK_UNIT, "UNIT_FIELD_MAXOFFHANDDAMAGE", 0x08E, 1, UF_TYPE_FLOAT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY + UF_FLAG_SPECIAL_INFO },
    { TYPEMASK_UNIT, "UNIT_FIELD_BYTES_1", 0x08F, 1, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_PETNUMBER", 0x090, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_PET_NAME_TIMESTAMP", 0x091, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_PETEXPERIENCE", 0x092, 1, UF_TYPE_INT, UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_PETNEXTLEVELEXP", 0x093, 1, UF_TYPE_INT, UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_DYNAMIC_FLAGS", 0x094, 1, UF_TYPE_INT, UF_FLAG_DYNAMIC },
    { TYPEMASK_UNIT, "UNIT_CHANNEL_SPELL", 0x095, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_MOD_CAST_SPEED", 0x096, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_CREATED_BY_SPELL", 0x097, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_NPC_FLAGS", 0x098, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_NPC_EMOTESTATE", 0x099, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_TRAINING_POINTS", 0x09A, 1, UF_TYPE_TWO_SHORT, UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_STAT0", 0x09B, 1, UF_TYPE_INT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_STAT1", 0x09C, 1, UF_TYPE_INT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_STAT2", 0x09D, 1, UF_TYPE_INT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_STAT3", 0x09E, 1, UF_TYPE_INT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_STAT4", 0x09F, 1, UF_TYPE_INT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_RESISTANCES", 0x0A0, 7, UF_TYPE_INT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY + UF_FLAG_SPECIAL_INFO },
    { TYPEMASK_UNIT, "UNIT_FIELD_ATTACK_POWER", 0x0A7, 1, UF_TYPE_INT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_BASE_MANA", 0x0A8, 1, UF_TYPE_INT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_ATTACK_POWER_MODS", 0x0A9, 1, UF_TYPE_TWO_SHORT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_BYTES_2", 0x0AA, 1, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT, "UNIT_FIELD_RANGED_ATTACK_POWER", 0x0AB, 1, UF_TYPE_INT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_RANGED_ATTACK_POWER_MODS", 0x0AC, 1, UF_TYPE_TWO_SHORT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_MINRANGEDDAMAGE", 0x0AD, 1, UF_TYPE_FLOAT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_MAXRANGEDDAMAGE", 0x0AE, 1, UF_TYPE_FLOAT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT, "UNIT_FIELD_PADDING", 0x0AF, 1, UF_TYPE_INT, UF_FLAG_NONE },
    { TYPEMASK_UNIT, "UNIT_END", 0x0B0, 0, UF_TYPE_NONE, UF_FLAG_NONE },
    { TYPEMASK_PLAYER, "PLAYER_SELECTION", 0x0AA, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER, "PLAYER_DUEL_ARBITER", 0x0AC, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER, "PLAYER_FLAGS", 0x0AE, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER, "PLAYER_GUILDID", 0x0AF, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER, "PLAYER_GUILDRANK", 0x0B0, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER, "PLAYER_BYTES", 0x0B1, 1, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER, "PLAYER_BYTES_2", 0x0B2, 1, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER, "PLAYER_BYTES_3", 0x0B3, 1, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER, "PLAYER_DUEL_TEAM", 0x0B4, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER, "PLAYER_GUILD_TIMESTAMP", 0x0B5, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_INV_SLOT_HEAD", 0x0B6, 46, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_PACK_SLOT_1", 0x0E4, 32, UF_TYPE_GUID, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_BANK_SLOT_1", 0x104, 48, UF_TYPE_GUID, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_BANKBAG_SLOT_1", 0x134, 12, UF_TYPE_GUID, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_VENDORBUYBACK_SLOT", 0x140, 2, UF_TYPE_GUID, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FARSIGHT", 0x142, 2, UF_TYPE_GUID, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_COMBO_TARGET", 0x144, 2, UF_TYPE_GUID, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_BUYBACK_NPC", 0x146, 2, UF_TYPE_GUID, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_XP", 0x148, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_NEXT_LEVEL_XP", 0x149, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_SKILL_INFO_1_1", 0x14A, 384, UF_TYPE_TWO_SHORT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_QUEST_LOG_1_1", 0x2CA, 60, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_CHARACTER_POINTS1", 0x306, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_CHARACTER_POINTS2", 0x307, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_TRACK_CREATURES", 0x308, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_TRACK_RESOURCES", 0x309, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_CHAT_FILTERS", 0x30A, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_BLOCK_PERCENTAGE", 0x30B, 1, UF_TYPE_FLOAT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_DODGE_PERCENTAGE", 0x30C, 1, UF_TYPE_FLOAT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_PARRY_PERCENTAGE", 0x30D, 1, UF_TYPE_FLOAT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_CRIT_PERCENTAGE", 0x30E, 1, UF_TYPE_FLOAT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_EXPLORED_ZONES_1", 0x30F, 32, UF_TYPE_BYTES, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_REST_STATE_EXPERIENCE", 0x32F, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_COINAGE", 0x330, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_POSSTAT0", 0x331, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_POSSTAT1", 0x332, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_POSSTAT2", 0x333, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_POSSTAT3", 0x334, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_POSSTAT4", 0x335, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_NEGSTAT0", 0x336, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_NEGSTAT1", 0x337, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_NEGSTAT2", 0x338, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_NEGSTAT3", 0x339, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_NEGSTAT4", 0x33A, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_RESISTANCEBUFFMODSPOSITIVE", 0x33B, 7, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_RESISTANCEBUFFMODSNEGATIVE", 0x342, 7, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_MOD_DAMAGE_DONE_POS", 0x349, 7, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_MOD_DAMAGE_DONE_NEG", 0x350, 7, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_MOD_DAMAGE_DONE_PCT", 0x357, 7, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_BYTES", 0x35E, 1, UF_TYPE_BYTES, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_AMMO_ID", 0x35F, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_PVP_MEDALS", 0x360, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_BUYBACK_ITEM_ID", 0x361, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_BUYBACK_RANDOM_PROPERTIES_ID", 0x362, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_BUYBACK_SEED", 0x363, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_BUYBACK_PRICE", 0x364, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_BUYBACK_DURABILITY", 0x365, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_BUYBACK_COUNT", 0x366, 1, UF_TYPE_INT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER, "PLAYER_FIELD_PADDING", 0x367, 1, UF_TYPE_INT, UF_FLAG_NONE },
    { TYPEMASK_PLAYER, "PLAYER_END", 0x368, 0, UF_TYPE_NONE, UF_FLAG_NONE },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_DISPLAYID", 0x006, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_FLAGS", 0x007, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_ROTATION", 0x008, 4, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_STATE", 0x00C, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_TIMESTAMP", 0x00D, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_POS_X", 0x00E, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_POS_Y", 0x00F, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_POS_Z", 0x010, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_FACING", 0x011, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_DYN_FLAGS", 0x012, 1, UF_TYPE_INT, UF_FLAG_DYNAMIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_FACTION", 0x013, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_TYPE_ID", 0x014, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_LEVEL", 0x015, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT, "GAMEOBJECT_END", 0x016, 0, UF_TYPE_NONE, UF_FLAG_NONE },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_CASTER", 0x006, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_BYTES", 0x008, 1, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_SPELLID", 0x009, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_RADIUS", 0x00A, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_POS_X", 0x00B, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_POS_Y", 0x00C, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_POS_Z", 0x00D, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_FACING", 0x00E, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_PAD", 0x00F, 1, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_END", 0x010, 0, UF_TYPE_NONE, UF_FLAG_NONE },
    { TYPEMASK_CORPSE, "CORPSE_FIELD_OWNER", 0x006, 2, UF_TYPE_GUID, UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE, "CORPSE_FIELD_FACING", 0x008, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE, "CORPSE_FIELD_POS_X", 0x009, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE, "CORPSE_FIELD_POS_Y", 0x00A, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE, "CORPSE_FIELD_POS_Z", 0x00B, 1, UF_TYPE_FLOAT, UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE, "CORPSE_FIELD_DISPLAY_ID", 0x00C, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE, "CORPSE_FIELD_ITEM", 0x00D, 19, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE, "CORPSE_FIELD_BYTES_1", 0x020, 1, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE, "CORPSE_FIELD_BYTES_2", 0x021, 1, UF_TYPE_BYTES, UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE, "CORPSE_FIELD_GUILD", 0x022, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE, "CORPSE_FIELD_FLAGS", 0x023, 1, UF_TYPE_INT, UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE, "CORPSE_END", 0x024, 0, UF_TYPE_NONE, UF_FLAG_NONE },
}};