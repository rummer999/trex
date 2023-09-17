// Updated: 2023-02-06

#pragma once
namespace offsets
{
        // buttons
        const long IN_ATTACK = 0x07473fb8;            // [Buttons] -> in_attack+0x8 (0x07473fb8 + 0x8)+
        const long IN_ZOOM = 0x07474138;              //[Buttons]->in_zoom+
        // core
        const long REGION = 0x140000000;              // [Mine]          -> Region
        const long LEVEL = 0x16efe10;                 // [Miscellaneous] -> LevelName
        const long LOCAL_PLAYER = 0x2225648;       // [Miscellaneous] -> AVC_GameMovement+0x8 множить
        const long ENTITY_LIST = 0x1e754c8;           // [Miscellaneous] -> cl_entitylist
        // entity
        const long LOCAL_ORIGIN = 0x0188; // [DataMap.CBaseViewModel]    -> 	m_localOrigin 0x0188
        // player
        const long TEAM_NUMBER = 0x0480;                // [RecvTable.DT_BaseEntity]        -> m_iTeamNum +
        const long NAME = 0x05c1;                       // [RecvTable.DT_BaseEntity]        -> m_iName +
        const long SIGNIFIER_NAME = 0x05b8;              //[RecvTable.DT_BaseEntity]->m_iSignifierName +
        const long LIFE_STATE = 0x07d0;                 // [RecvTable.DT_Player]            -> m_lifeState +
        const long VEC_PUNCH_WEAPON_ANGLE = 0x24e8;     // [DataMap.C_Player]               -> m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle //PUNCH_ANGLES +
        const long VIEW_ANGLE = (0x25e4 - 0x14);        // [DataMap.C_Player]               -> m_ammoPoolCapacity - 0x14 //VIEW_ANGLES +
        const long BLEEDOUT_STATE = 0x2790;             // [RecvTable.DT_Player]            -> m_bleedoutState +
        const long ZOOMING = 0x1c81;                    // [RecvTable.DT_Player]            -> m_bZooming   чтения состояния зума у игрока +
        const long LAST_VISIBLE_TIME = 0x1a9d + 0x3;    // [Miscellaneous]                  -> CPlayer!lastVisibleTime     base +
        const long LAST_AIMEDAT_TIME = 0x1a9d + 0x3 + 0x8;  //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 +0x8 +
        //glow
        const long GLOW_ENABLE = 0x03f0 + 0x8;          //[RecvTable.DT_HighlightSettings]->m_highlightServerContextID + 0x8+
        const long GLOW_THROUGH_WALL = 0x03f0 + 0x10; // [RecvTable.DT_HighlightSettings] -> m_highlightServerContextID + 0x10+
        const long GLOW_COLOR = 0x200;                  // [Miscellaneous]                  -> glow_color+
        const long GLOW_MODE = 0x2c4 + 0x30;    //[?]->?
        const long CURRENT_SHIELDS = 0x01a0;               // [RecvTable.DT_BaseEntity]        -> m_shieldHealth +
        const long OFFSET_BONES = 0x0f80;             //       m_nForceBone    + 0x48      0x0ec8   
        const long PLAYER_THIRD_PERSON_SHOULDER_VIEW = 0x3728;  //", "RecvTable.DT_LocalPlayerExclusive", "m_thirdPersonShoulderView);
        const long BONES = 0x0ec8 + 0x48;                     // m_nForceBone + 0x48
        //weapon
        const long WEAPON_HANDLE = 0x1a44;               //[RecvTable.DT_Player]->m_latestPrimaryWeapons+
        const long WEAPON_INDEX = 0x1888;                //[RecvTable.DT_WeaponX]->m_weaponNameIndex+
        const long WEAPON_SEMIAUTO = 0x1a9d + 0x3 + 0x018c;       //[RecvTable.DT_BaseCombatCharacter]->m_hudInfo_visibilityTestAlwaysPasses + 0x3 + 0x018c+
        const long BULLET_SPEED =0x1aa0 + 0x04cc;             //m_flProjectileSpeed
        const long BULLET_GRAVITY =0x1aa0 + 0x04d4;            //m_flProjectileScale
        //prop survival
        const long OFFSET_ViewModels = 0x02f0;  // m_hViewModels
        const long OFFSET_MODELNAME = 0x0030;   // m_ModelName //m_ModelName+
        const long m_scriptNameIndex = 0x06c8; //int+
        const long m_grade = 0x0490; //int+
        const long m_pressUsePrompt=0x0758;//string+
        const long OFFSET_ITEM_GLOW = 0x1668;    //m_customScriptInt
        const long lastCrosshairTargetTime = 0x1aa0 + 0x3 + 0x8;   // (OFFSET_VISIBLE_TIME + 0x08) // CPlayer!lastCrosshairTargetTime 0x1aa8
}
