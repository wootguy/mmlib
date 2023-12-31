// This code was automatically generated by the ApiGenerator plugin
// Value names that conflict with the HLSDK are commented out

// Activity
#define ACT_RESET 0 // Set m_Activity to this invalid value to force a reset to m_IdealActivity
#define ACT_IDLE 1
#define ACT_GUARD 2
#define ACT_WALK 3
#define ACT_RUN 4
#define ACT_FLY 5 // Fly (and flap if appropriate)
#define ACT_SWIM 6
#define ACT_HOP 7 // vertical jump
#define ACT_LEAP 8 // long forward jump
#define ACT_FALL 9
#define ACT_LAND 10
#define ACT_STRAFE_LEFT 11
#define ACT_STRAFE_RIGHT 12
#define ACT_ROLL_LEFT 13 // tuck and roll, left
#define ACT_ROLL_RIGHT 14 // tuck and roll, right
#define ACT_TURN_LEFT 15 // turn quickly left (stationary)
#define ACT_TURN_RIGHT 16 // turn quickly right (stationary)
#define ACT_CROUCH 17 // the act of crouching down from a standing position
#define ACT_CROUCHIDLE 18 // holding body in crouched position (loops)
#define ACT_STAND 19 // the act of standing from a crouched position
#define ACT_USE 20
#define ACT_SIGNAL1 21
#define ACT_SIGNAL2 22
#define ACT_SIGNAL3 23
#define ACT_TWITCH 24
#define ACT_COWER 25
#define ACT_SMALL_FLINCH 26
#define ACT_BIG_FLINCH 27
#define ACT_RANGE_ATTACK1 28
#define ACT_RANGE_ATTACK2 29
#define ACT_MELEE_ATTACK1 30
#define ACT_MELEE_ATTACK2 31
#define ACT_RELOAD 32
#define ACT_ARM 33 // pull out gun, for instance
#define ACT_DISARM 34 // reholster gun
#define ACT_EAT 35 // monster chowing on a large food item (loop)
#define ACT_DIESIMPLE 36
#define ACT_DIEBACKWARD 37
#define ACT_DIEFORWARD 38
#define ACT_DIEVIOLENT 39
#define ACT_BARNACLE_HIT 40 // barnacle tongue hits a monster
#define ACT_BARNACLE_PULL 41 // barnacle is lifting the monster ( loop )
#define ACT_BARNACLE_CHOMP 42 // barnacle latches on to the monster
#define ACT_BARNACLE_CHEW 43 // barnacle is holding the monster in its mouth ( loop )
#define ACT_SLEEP 44
#define ACT_INSPECT_FLOOR 45 // for active idles, look at something on or near the floor
#define ACT_INSPECT_WALL 46 // for active idles, look at something directly ahead of you ( doesn't HAVE to be a wall or on a wall )
#define ACT_IDLE_ANGRY 47 // alternate idle animation in which the monster is clearly agitated. (loop)
#define ACT_WALK_HURT 48 // limp  (loop)
#define ACT_RUN_HURT 49 // limp  (loop)
#define ACT_HOVER 50 // Idle while in flight
#define ACT_GLIDE 51 // Fly (don't flap)
#define ACT_FLY_LEFT 52 // Turn left in flight
#define ACT_FLY_RIGHT 53 // Turn right in flight
#define ACT_DETECT_SCENT 54 // this means the monster smells a scent carried by the air
#define ACT_SNIFF 55 // this is the act of actually sniffing an item in front of the monster
#define ACT_BITE 56 // some large monsters can eat small things in one bite. This plays one time, EAT loops.
#define ACT_THREAT_DISPLAY 57 // without attacking, monster demonstrates that it is angry. (Yell, stick out chest, etc )
#define ACT_FEAR_DISPLAY 58 // monster just saw something that it is afraid of
#define ACT_EXCITED 59 // for some reason, monster is excited. Sees something he really likes to eat, or whatever.
#define ACT_SPECIAL_ATTACK1 60 // very monster specific special attacks.
#define ACT_SPECIAL_ATTACK2 61
#define ACT_COMBAT_IDLE 62 // agitated idle.
#define ACT_WALK_SCARED 63
#define ACT_RUN_SCARED 64
#define ACT_VICTORY_DANCE 65 // killed a player, do a victory dance.
#define ACT_DIE_HEADSHOT 66 // die, hit in head.
#define ACT_DIE_CHESTSHOT 67 // die, hit in chest
#define ACT_DIE_GUTSHOT 68 // die, hit in gut
#define ACT_DIE_BACKSHOT 69 // die, hit in back
#define ACT_FLINCH_HEAD 70
#define ACT_FLINCH_CHEST 71
#define ACT_FLINCH_STOMACH 72
#define ACT_FLINCH_LEFTARM 73
#define ACT_FLINCH_RIGHTARM 74
#define ACT_FLINCH_LEFTLEG 75
#define ACT_FLINCH_RIGHTLEG 76

// EdictFlags
// #define FL_FLY 1 // Changes the SV_Movestep() behavior to not need to be on ground
// #define FL_SWIM 2 // Changes the SV_Movestep() behavior to not need to be on ground (but stay in water)
// #define FL_CONVEYOR 4 // If set, entities standing on this entity are moved as if this were a conveyor
// #define FL_CLIENT 8 // If set, this is a player
// #define FL_INWATER 16 // If set, this entity is in water. Only applies to players
// #define FL_MONSTER 32 // If set, this is a monster
// #define FL_GODMODE 64 // If set, this entity is invincible. Only applies to players
// #define FL_NOTARGET 128 // If set, this entity will not be targeted by monster AI
// #define FL_SKIPLOCALHOST 256 // Don't send entity to local host, it's predicting this entity itself
// #define FL_ONGROUND 512 // At rest / on the ground
// #define FL_PARTIALGROUND 1024 // not all corners are valid
// #define FL_WATERJUMP 2048 // player jumping out of water
// #define FL_FROZEN 4096 // Player is frozen for 3rd person camera
// #define FL_FAKECLIENT 8192 // JAC: fake client, simulated server side; don't send network messages to them
// #define FL_DUCKING 16384 // Player flag -- Player is fully crouched
// #define FL_FLOAT 32768 // Apply floating force to this entity when in water
// #define FL_GRAPHED 65536 // worldgraph has this ent listed as something that blocks a connection
// #define FL_IMMUNE_WATER 131072 // If set, players don't take drown damage
// #define FL_IMMUNE_SLIME 262144 // If set, players don't take damage from slime
// #define FL_IMMUNE_LAVA 524288 // If set, players don't take damage from lava
// #define FL_PROXY 1048576 // This is a spectator proxy
// #define FL_ALWAYSTHINK 2097152 // Brush model flag -- call think every frame regardless of nextthink - ltime (for constantly changing velocity/path)
// #define FL_BASEVELOCITY 4194304 // Base velocity has been applied this frame (used to convert base velocity into momentum)
// #define FL_MONSTERCLIP 8388608 // Only collide in with monsters who have FL_MONSTERCLIP set
// #define FL_ONTRAIN 16777216 // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
// #define FL_WORLDBRUSH 33554432 // Not moveable/removeable brush entity (really part of the world, but represented as an entity for transparency or something)
// #define FL_SPECTATOR 67108864 // This client is a spectator, don't run touch functions, etc.
#define FL_NOWEAPONS 134217728 // This client is being denied weapon usage
// #define FL_CUSTOMENTITY 536870912 // This is a custom entity
// #define FL_KILLME 1073741824 // This entity is marked for death -- This allows the engine to kill ents at the appropriate time
// #define FL_DORMANT 2147483648 // Entity is dormant, no updates to client

// EFFECTS
// #define EF_BRIGHTFIELD 1 // swirling cloud of particles
// #define EF_MUZZLEFLASH 2 // single frame ELIGHT on entity attachment 0
// #define EF_BRIGHTLIGHT 4 // DLIGHT centered at entity origin
// #define EF_DIMLIGHT 8 // player flashlight
// #define EF_INVLIGHT 16 // get lighting from ceiling
// #define EF_NOINTERP 32 // don't interpolate the next frame
// #define EF_LIGHT 64 // rocket flare glow sprite
// #define EF_NODRAW 128 // don't draw entity
#define EF_NODECALS 2048 // don't draw decals on this entity
#define EF_NOANIMTEXTURES 256 // Don't animate brush entities
#define EF_FRAMEANIMTEXTURES 512 // Use the value in pev-&gt;frame to set the texture on a brush entity

// FixAngleMode
#define FAM_NOTHING 0 // Do nothing
#define FAM_FORCEVIEWANGLES 1 // Force player view angles to entvars_t::angles
#define FAM_ADDAVELOCITY 2 // Add avelocity to player view angles

// CLASS
#define CLASS_FORCE_NONE -1 // Forces class override to none
#define CLASS_NONE 0 // No classification
#define CLASS_MACHINE 1 // Is machine
#define CLASS_PLAYER 2 // Is player
#define CLASS_HUMAN_PASSIVE 3 // Is passive human
#define CLASS_HUMAN_MILITARY 4 // Is military human
#define CLASS_ALIEN_MILITARY 5 // Is military alien
#define CLASS_ALIEN_PASSIVE 6 // Is passive alien
#define CLASS_ALIEN_MONSTER 7 // Is monster alien
#define CLASS_ALIEN_PREY 8 // Is prey alien
#define CLASS_ALIEN_PREDATOR 9 // Is predator alien
#define CLASS_INSECT 10 // Is insect
#define CLASS_PLAYER_ALLY 11 // is player ally
#define CLASS_PLAYER_BIOWEAPON 12 // Is player bioweapon
#define CLASS_ALIEN_BIOWEAPON 13 // Is alien bioweapon
#define CLASS_XRACE_PITDRONE 14 // Is X-Race pitdrone
#define CLASS_XRACE_SHOCK 15 // Is X-Race shock trooper (also Voltigores)
#define CLASS_TEAM1 16 // Is on Team 1
#define CLASS_TEAM2 17 // Is on Team 2
#define CLASS_TEAM3 18 // Is on Team 3
#define CLASS_TEAM4 19 // Is on Team 4
#define CLASS_BARNACLE 99 // Is Barnacle

// DMG
#define DMG_GENERIC 0 // Generic damage.
#define DMG_CRUSH 1 // Crush damage. By falling or moving object.
#define DMG_BULLET 2 // Bullet. Shot.
#define DMG_SLASH 4 // Slash. Cut, clawed, stabbed.
#define DMG_BURN 8 // Burn. Heat burned.
#define DMG_FREEZE 16 // Freeze. Frozen.
#define DMG_FALL 32 // Fall. Fell too far.
#define DMG_BLAST 64 // Blast. Explosive blast damage.
#define DMG_CLUB 128 // Club. Crowbar, punch, headbutt.
#define DMG_SHOCK 256 // Shock. Electric shock.
#define DMG_SONIC 512 // Sonic. Sound pulse shockwave.
#define DMG_ENERGYBEAM 1024 // Energy beam. Laser or other high energy beam.
#define DMG_NEVERGIB 4096 // Never gib. With this bit OR'd in, no damage type will be able to gib victims upon death.
#define DMG_ALWAYSGIB 8192 // Always gib. With this bit OR'd in, any damage type can be made to gib victims upon death.
#define DMG_LAUNCH 67108864 // Launch. Launch into air.
#define DMG_DROWN 16384 // Drown. Drowning.
#define DMG_TIMEBASED 16760832 // Mash for time-based damage.
#define DMG_PARALYZE 32768 // Paralyze. Slows affected creature down.
#define DMG_NERVEGAS 65536 // Nerve gas. Nerve toxins, very bad.
#define DMG_POISON 131072 // Poison. Blood poisoning.
#define DMG_RADIATION 262144 // Radiation. Radiation exposure.
#define DMG_DROWNRECOVER 524288 // Drown recover. Drowning recovery.
#define DMG_ACID 1048576 // Acid. Toxic chemicals or acid burns.
#define DMG_SLOWBURN 2097152 // Slow burn. In an oven.
#define DMG_SLOWFREEZE 4194304 // Slow freeze. In a subzero freezer.
#define DMG_MORTAR 8388608 // Mortar. Hit by air raid (done to distinguish grenade from mortar)
#define DMG_SNIPER 16777216 // Sniper. Hit by a Sniper.
#define DMG_MEDKITHEAL 33554432 // Medkit heal. Medkit healing.
#define DMG_SHOCK_GLOW 134217728 // Shock glow. Flag for shock glow effect.
#define DMG_GIB_CORPSE 993 // Gib corpse. These are the damage types that are allowed to gib corpses.
#define DMG_SHOWNHUD 7815448 // Shown on HUD. These are the damage types that have clien hud art.

// GIB
#define GIB_NORMAL 0 // gib if entity was overkilled
#define GIB_NEVER 1 // never gib, no matter how much death damage is done ( freezing, etc )
#define GIB_ALWAYS 2 // always gib ( Houndeye Shock, Barnacle Bite )
#define GIB_NOPENALTY 3 // No penalty applied to players that died

// USE_TYPE
#define USE_OFF 0 // Turns off an entity
#define USE_ON 1 // Turns on an entity
#define USE_SET 2 // Sets the state of an entity (use float parameter in Use)
#define USE_TOGGLE 3 // Toggles the state of an entity
#define USE_KILL 4 // Kills an entity

// Bullet
#define BULLET_NONE 0
#define BULLET_PLAYER_9MM 1 // Glock
#define BULLET_PLAYER_MP5 2 // mp5
#define BULLET_PLAYER_SAW 3
#define BULLET_PLAYER_SNIPER 4
#define BULLET_PLAYER_357 5 // Python
#define BULLET_PLAYER_EAGLE 6 // Desert eagle
#define BULLET_PLAYER_BUCKSHOT 7 // Shotgun
#define BULLET_PLAYER_CROWBAR 8
#define BULLET_PLAYER_CUSTOMDAMAGE 9 // normal bullet with custom damage
#define BULLET_MONSTER_9MM 10
#define BULLET_MONSTER_MP5 11
#define BULLET_MONSTER_SAW 12
#define BULLET_MONSTER_12MM 13
#define BULLET_MONSTER_EAGLE 14
#define BULLET_MONSTER_SNIPER 15
#define BULLET_MONSTER_BUCKSHOT 16 // Monster shotgun
#define DECAL_SCORCH_MARK 17

// AddPlayerItemResult
#define APIR_NotAdded 0 // Player could not pick up this item
#define APIR_DuplicateAdd 2 // Player was able to add it as duplicate
#define APIR_Added 3 // Player picked up this item

// HITGROUP
#define HITGROUP_GENERIC 0
#define HITGROUP_HEAD 1
#define HITGROUP_CHEST 2
#define HITGROUP_STOMACH 3
#define HITGROUP_LEFTARM 4
#define HITGROUP_RIGHTARM 5
#define HITGROUP_LEFTLEG 6
#define HITGROUP_RIGHTLEG 7

// PFLAG
#define PFLAG_ONLADDER 1
#define PFLAG_ONSWING 1
#define PFLAG_ONTRAIN 2
#define PFLAG_ONBARNACLE 4
#define PFLAG_DUCKING 8 // In the process of ducking, but totally squatted yet
#define PFLAG_USING 16 // Using a continuous entity
#define PFLAG_OBSERVER 32 // player is locked in stationary cam mode. Spectators can move, observers can't.
#define PFLAG_GRAPPLE 64 // Toggle grapple use
#define PFLAG_CAMERA 128 // Looking through a trigger_camera

// ObserverMode
#define OBS_ENTERING -1 // Player in the process of entering observer mode
#define OBS_NONE 0 // Player not in observer mode
#define OBS_CHASE_LOCKED 3 // Chase locked
#define OBS_CHASE_FREE 1 // Free movement
#define OBS_ROAMING 2 // Roaming

// Train
#define TRAIN_ACTIVE 128
#define TRAIN_NEW 192
#define TRAIN_OFF 0
#define TRAIN_NEUTRAL 1
#define TRAIN_SLOW 2
#define TRAIN_MEDIUM 3
#define TRAIN_FAST 4
#define TRAIN_BACK 5

// PLAYER_ANIM
#define PLAYER_IDLE 0
#define PLAYER_WALK 1
#define PLAYER_JUMP 2
#define PLAYER_SUPERJUMP 3
#define PLAYER_DIE 4
#define PLAYER_ATTACK1 5
#define PLAYER_RELOAD 6
#define PLAYER_DEPLOY 7
#define PLAYER_BARNACLE_HIT 8
#define PLAYER_BARNACLE_PULL 9
#define PLAYER_BARNACLE_CHOMP 10
#define PLAYER_BARNACLE_CHEW 11

// PlayerViewMode
#define ViewMode_FirstPerson 0
#define ViewMode_ThirdPerson 1

// ButtonCode
#define BUTTON_NOTHING 0 // Do nothing
#define BUTTON_ACTIVATE 1 // Activate the button
#define BUTTON_RETURN 2 // Return the button to its default state

// WeaponIds
#define WEAPON_NONE 0 // Weapon id used for invalid weapon ids.
#define WEAPON_CROWBAR 1
#define WEAPON_GLOCK 2
#define WEAPON_PYTHON 3
#define WEAPON_MP5 4
#define WEAPON_CHAINGUN 5
#define WEAPON_CROSSBOW 6
#define WEAPON_SHOTGUN 7
#define WEAPON_RPG 8
#define WEAPON_GAUSS 9
#define WEAPON_EGON 10
#define WEAPON_HORNETGUN 11
#define WEAPON_HANDGRENADE 12
#define WEAPON_TRIPMINE 13
#define WEAPON_SATCHEL 14
#define WEAPON_SNARK 15
#define WEAPON_UZI 17
#define WEAPON_MEDKIT 18
#define WEAPON_CROWBAR_ELECTRIC 19
#define WEAPON_PIPEWRENCH 20
#define WEAPON_MINIGUN 21
#define WEAPON_GRAPPLE 22
#define WEAPON_SNIPERRIFLE 23
#define WEAPON_M249 24
#define WEAPON_M16 25
#define WEAPON_SPORELAUNCHER 26
#define WEAPON_DESERT_EAGLE 27
#define WEAPON_SHOCKRIFLE 28
#define WEAPON_DISPLACER 29
// #define MAX_WEAPONS 256 // Maximum number of weapons that the game supports

// BeamType
#define BEAM_POINTS 0 // Beam is a beam between 2 points
#define BEAM_ENTPOINT 1 // Beam is a beam between point and entity
#define BEAM_ENTS 2 // Beam is a beam between entities
#define BEAM_HOSE 3 // I don't even know what this does

// BeamFlags
#define BEAM_FSINE 16 // Beam shape follows a sinus shape
#define BEAM_FSOLID 32 // Beam is a solid shape
#define BEAM_FSHADEIN 64 // Beam fades in at its start point
#define BEAM_FSHADEOUT 128 // Beam fades out at its end point

// CBeamSpawnflags
#define SF_BEAM_STARTON 1 // Whether the beam should start on
#define SF_BEAM_TOGGLE 2 // Whether the beam should be togglable by triggering it
#define SF_BEAM_RANDOM 4 // Whether beams are created to a randomly selected entity with the given target name
#define SF_BEAM_RING 8 // Whether this beam is a ring between 2 points
#define SF_BEAM_SPARKSTART 16 // Whether to allow creation of sparks at the beam's start point
#define SF_BEAM_SPARKEND 32 // Whether to allow creation of sparks at the beam's end point
#define SF_BEAM_DECALS 64 // Whether to create decals when the beam does damage to BSP models
#define SF_BEAM_SHADEIN 128 // Whether to fade the beam in at its start point
#define SF_BEAM_SHADEOUT 256 // Whether to fade the beam out at its end point
#define SF_BEAM_TEMPORARY 32768 // Whether the beam is a temporary entity

// TANKBULLET
#define TANK_BULLET_NONE 0 // No bullet. Nothing is fired when this is set
#define TANK_BULLET_9MM 1 // 9mm rounds
#define TANK_BULLET_MP5 2 // MP5 rounds
#define TANK_BULLET_12MM 3 // 12 mm rounds

// SoundFlag
#define SND_VOLUME 1 // Volume flag
#define SND_PITCH 2 // Pitch flag
#define SND_ATTENUATION 4 // Attenuation flag
#define SND_ORIGIN 8 // Origin flag
#define SND_ENT 16 // Entity flag
// #define SND_STOP 32 // Stop flag
// #define SND_CHANGE_VOL 64 // Change volume flag
// #define SND_CHANGE_PITCH 128 // Change pitch flag
#define SND_SENTENCE 256 // Sentence flag
#define SND_REFRESH 512 // Refresh flag
#define SND_FORCE_SINGLE 1024 // Force single flag
#define SND_FORCE_LOOP 2048 // Force loop flag
#define SND_LINEAR 4096 // Linear flag
#define SND_SKIP_ORIGIN_USE_ENT 8192 // Skip Origin and use entity flag

// SOUND_CHANNEL
// #define CHAN_AUTO 0 // Automatically selects a channel for use. You cannot stop sounds while using this channel with StopSound, or in conjunction with the SND_STOP flag.
// #define CHAN_WEAPON 1
// #define CHAN_VOICE 2
// #define CHAN_ITEM 3
// #define CHAN_BODY 4
// #define CHAN_STREAM 5 // allocate stream channel from the static or dynamic area
// #define CHAN_STATIC 6 // allocate channel from the static area
#define CHAN_MUSIC 7

// AdminLevel_t
#define ADMIN_INIT -1 // Level on connect, tells functions not to use cached level
#define ADMIN_NO 0 // Not an administrator
#define ADMIN_YES 1 // Server administrator
#define ADMIN_OWNER 2 // Server owner (applies to a listenserver host player)

// FFADE
#define FFADE_IN 0 // Just here so we don't pass 0 into the function
#define FFADE_OUT 1 // Fade out (not in)
#define FFADE_MODULATE 2 // Modulate (don't blend)
#define FFADE_STAYOUT 4 // ignores the duration, stays faded out until new ScreenFade message received

// HUD_EFFECT
#define HUD_EFFECT_NONE 0 // No effect.
#define HUD_EFFECT_RAMP_UP 1 // Linear ramp up from color1 to color2.
#define HUD_EFFECT_RAMP_DOWN 2 // Linear ramp down from color2 to color1.
#define HUD_EFFECT_TRIANGLE 3 // Linear ramp up and ramp down from color1 through color2 back to color1.
#define HUD_EFFECT_COSINE_UP 4 // Cosine ramp up from color1 to color2.
#define HUD_EFFECT_COSINE_DOWN 5 // Cosine ramp down from color2 to color1.
#define HUD_EFFECT_COSINE 6 // Cosine ramp up and ramp down from color1 through color2 back to color1.
#define HUD_EFFECT_TOGGLE 7 // Toggle between color1 and color2.
#define HUD_EFFECT_SINE_PULSE 8 // Sine pulse from color1 through zero to color2.

// HUD_ELEM
#define HUD_ELEM_ABSOLUTE_X 1 // X position in pixels.
#define HUD_ELEM_ABSOLUTE_Y 2 // Y position in pixels.
#define HUD_ELEM_SCR_CENTER_X 4 // X position relative to the center of the screen.
#define HUD_ELEM_SCR_CENTER_Y 8 // Y position relative to the center of the screen.
#define HUD_ELEM_NO_BORDER 16 // Ignore the client-side HUD border (hud_bordersize).
#define HUD_ELEM_HIDDEN 32 // Create a hidden element.
#define HUD_ELEM_EFFECT_ONCE 64 // Play the effect only once.
#define HUD_ELEM_DEFAULT_ALPHA 128 // Use the default client-side HUD alpha (hud_defaultalpha).
#define HUD_ELEM_DYNAMIC_ALPHA 256 // Use the default client-side HUD alpha and flash the element when updated.

// HUD_SPR
#define HUD_SPR_OPAQUE 65536 // Draw opaque sprite.
#define HUD_SPR_MASKED 131072 // Draw masked sprite.
#define HUD_SPR_PLAY_ONCE 262144 // Play the animation only once.
#define HUD_SPR_HIDE_WHEN_STOPPED 524288 // Hide the sprite when the animation stops.

// HUD_NUM
#define HUD_NUM_RIGHT_ALIGN 65536 // Draw right aligned element.
#define HUD_NUM_SEPARATOR 131072 // Draw separator.
#define HUD_NUM_DONT_DRAW_ZERO 262144 // Hide the element if the value is zero.
#define HUD_NUM_LEADING_ZEROS 524288 // Draw leading zeros.
#define HUD_NUM_NEGATIVE_NUMBERS 1048576 // Allow negative values.
#define HUD_NUM_PLUS_SIGN 2097152 // Draw sign for positive values.

// HUD_TIME
#define HUD_TIME_RIGHT_ALIGN 65536 // Draw right aligned element.
#define HUD_TIME_HOURS 131072 // Draw hours.
#define HUD_TIME_MINUTES 262144 // Draw minutes.
#define HUD_TIME_SECONDS 524288 // Draw seconds.
#define HUD_TIME_MILLISECONDS 1048576 // Draw milliseconds.
#define HUD_TIME_ZERO_HOURS 2097152 // Draw hours even if the value is zero.
#define HUD_TIME_FREEZE 4194304 // Freeze the displayed value.
#define HUD_TIME_COUNT_DOWN 8388608 // Count down.

// NetworkMessageType
// #define MSG_SVC_TEMPENTITY 23 // Creates temporary entities on the client side.
// #define MSG_SVC_INTERMISSION 30 // Enables intermission for clients.
#define MSG_SVC_STUFFTEXT 9 // Executes command on the client side.
#define MSG_SelAmmo 64 // User message
#define MSG_CurWeapon 65 // User message
#define MSG_Geiger 66 // User message
#define MSG_Flashlight 67 // User message
#define MSG_FlashBat 68 // User message
#define MSG_Health 69 // User message
#define MSG_Damage 70 // User message
#define MSG_Battery 71 // User message
#define MSG_Train 72 // User message
#define MSG_HudText 73 // User message
#define MSG_SayText 74 // User message
#define MSG_TextMsg 75 // User message
#define MSG_WeaponList 76 // User message
#define MSG_CustWeapon 77 // User message
#define MSG_ResetHUD 78 // User message
#define MSG_InitHUD 79 // User message
#define MSG_CdAudio 80 // User message
#define MSG_GameTitle 81 // User message
#define MSG_DeathMsg 82 // User message
#define MSG_ScoreInfo 83 // User message
#define MSG_TeamInfo 84 // User message
#define MSG_TeamScore 85 // User message
#define MSG_GameMode 86 // User message
#define MSG_MOTD 87 // User message
#define MSG_AmmoPickup 88 // User message
#define MSG_WeapPickup 89 // User message
#define MSG_ItemPickup 90 // User message
#define MSG_HideHUD 91 // User message
#define MSG_SetFOV 92 // User message
#define MSG_ShowMenu 93 // User message
#define MSG_ScreenShake 94 // User message
#define MSG_ScreenFade 95 // User message
#define MSG_AmmoX 96 // User message
#define MSG_Gib 97 // User message
#define MSG_Spectator 98 // User message
#define MSG_TE_CUSTOM 99 // User message
#define MSG_Speaksent 100 // User message
#define MSG_TimeEnd 101 // User message
#define MSG_MapList 102 // User message
#define MSG_CbElec 103 // User message
#define MSG_EndVote 104 // User message
#define MSG_VoteMenu 105 // User message
#define MSG_NextMap 106 // User message
#define MSG_StartSound 107 // User message
#define MSG_SoundList 108 // User message
#define MSG_ToxicCloud 109 // User message
#define MSG_ShkFlash 110 // User message
#define MSG_CreateBlood 111 // User message
#define MSG_GargSplash 112 // User message
#define MSG_SporeTrail 113 // User message
#define MSG_TracerDecal 114 // User message
#define MSG_SRDetonate 115 // User message
#define MSG_SRPrimed 116 // User message
#define MSG_SRPrimedOff 117 // User message
#define MSG_RampSprite 118 // User message
#define MSG_ShieldRic 119 // User message
#define MSG_Playlist 120 // User message
#define MSG_VGUIMenu 121 // User message
#define MSG_ServerName 122 // User message
#define MSG_TeamNames 123 // User message
#define MSG_ServerVer 124 // User message
#define MSG_ServerBuild 125 // User message
#define MSG_WeatherFX 126 // User message
#define MSG_CameraMouse 127 // User message
#define MSG_Fog 128 // User message
#define MSG_PrtlUpdt 129 // User message
#define MSG_ASScriptName 130 // User message
#define MSG_PrintKB 131 // User message
#define MSG_InvAdd 132 // User message
#define MSG_InvRemove 133 // User message
#define MSG_Concuss 134 // User message
#define MSG_ViewMode 135 // User message
#define MSG_Flamethwr 136 // User message
#define MSG_ClassicMode 137 // User message
#define MSG_WeaponSpr 138 // User message
#define MSG_ToggleElem 139 // User message
#define MSG_CustSpr 140 // User message
#define MSG_NumDisplay 141 // User message
#define MSG_UpdateNum 142 // User message
#define MSG_TimeDisplay 143 // User message
#define MSG_UpdateTime 144 // User message
#define MSG_VModelPos 145 // User message

// FCAP
#define FCAP_CUSTOMSAVE 1 // Custom save method
#define FCAP_ACROSS_TRANSITION 2 // Across transition
#define FCAP_MUST_SPAWN 4 // Must spawn
#define FCAP_DONT_SAVE -2147483648 // Don't save
#define FCAP_IMPULSE_USE 8 // Impulse use
#define FCAP_CONTINUOUS_USE 16 // Continuous use
#define FCAP_ONOFF_USE 32 // On/off use
#define FCAP_DIRECTIONAL_USE 64 // Directional use
#define FCAP_MASTER 128 // Is a master
#define FCAP_FORCE_TRANSITION 128 // Force transition
