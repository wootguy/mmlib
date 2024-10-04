#pragma once

// metamod/misc utils
#include "meta_init.h"
#include "meta_utils.h"
#include "misc_utils.h"
#include "meta_helper.h"
#include "Scheduler.h"
#include "crc32.h"

// client/game effects
#include "TextMenu.h"
#include "temp_ents.h"

#ifdef HLCOOP_BUILD
#include "cbase.h"
#include "CBaseMonster.h"
#include "CBasePlayer.h"
#include "CBasePlayerWeapon.h"
#define CLASS_XRACE_PITDRONE CLASS_ALIEN_RACE_X_PITDRONE
#define CLASS_XRACE_SHOCK CLASS_ALIEN_RACE_X
#else
#include "HUDSprite.h"
#include "StartSound.h"
#include "UserInfo.h"
#endif

// networking
#include "net/Packet.h"
#include "net/IPV4.h"
#include "net/Socket.h"