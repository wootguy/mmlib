#include "NetMessage.h"
#include "misc_utils.h"

using namespace std;

#define SVC_BAD 0
#define SVC_NOP 1
#define SVC_DISCONNECT 2
#define SVC_EVENT 3
#define SVC_VERSION 4
#define SVC_SETVIEW 5
#define SVC_SOUND 6
#define SVC_TIME 7
#define SVC_PRINT 8
#define SVC_STUFFTEXT 9
#define SVC_SETANGLE 10
#define SVC_SERVERINFO 11
#define SVC_LIGHTSTYLE 12
#define SVC_UPDATEUSERINFO 13
#define SVC_DELTADESCRIPTION 14
#define SVC_CLIENTDATA 15
#define SVC_STOPSOUND 16
#define SVC_PINGS 17
#define SVC_PARTICLE 18
#define SVC_DAMAGE 19
#define SVC_SPAWNSTATIC 20
#define SVC_EVENT_RELIABLE 21
#define SVC_SPAWNBASELINE 22
#define SVC_TEMPENTITY 23
#define SVC_SETPAUSE 24
#define SVC_SIGNONNUM 25
#define SVC_CENTERPRINT 26
#define SVC_KILLEDMONSTER 27
#define SVC_FOUNDSECRET 28
#define SVC_SPAWNSTATICSOUND 29
#define SVC_INTERMISSION 30
#define SVC_FINALE 31
#define SVC_CDTRACK 32
#define SVC_RESTORE 33
#define SVC_CUTSCENE 34
#define SVC_WEAPONANIM 35
#define SVC_DECALNAME 36
#define SVC_ROOMTYPE 37
#define SVC_ADDANGLE 38
#define SVC_NEWUSERMSG 39
#define SVC_PACKETENTITIES 40
#define SVC_DELTAPACKETENTITIES 41
#define SVC_CHOKE 42
#define SVC_RESOURCELIST 43
#define SVC_NEWMOVEVARS 44
#define SVC_RESOURCEREQUEST 45
#define SVC_CUSTOMIZATION 46
#define SVC_CROSSHAIRANGLE 47
#define SVC_SOUNDFADE 48
#define SVC_FILETXFERFAILED 49
#define SVC_HLTV 50
#define SVC_DIRECTOR 51
#define SVC_VOICEINIT 52
#define SVC_VOICEDATA 53
#define SVC_SENDEXTRAINFO 54
#define SVC_TIMESCALE 55
#define SVC_RESOURCELOCATION 56
#define SVC_SENDCVARVALUE 57
#define SVC_SENDCVARVALUE2 58

MessageArg::MessageArg(int argType, int ival) {
	this->argType = argType;
	this->ival = ival;
}

MessageArg::MessageArg(int argType, float fval) {
	this->argType = argType;
	this->fval = fval;
}

MessageArg::MessageArg(int argType, string sval) {
	this->argType = argType;
	this->sval = sval;
}

void MessageArg::writeToCurrentMessage() {
	switch (argType) {
	case MARG_NONE:
		break;
	case MARG_ANGLE:
		WRITE_ANGLE(fval);
		break;
	case MARG_BYTE:
		WRITE_BYTE(ival);
		break;
	case MARG_CHAR:
		WRITE_CHAR(ival);
		break;
	case MARG_COORD:
		WRITE_COORD(fval);
		break;
	case MARG_ENT:
		WRITE_ENTITY(ival);
		break;
	case MARG_LONG:
		WRITE_LONG(ival);
		break;
	case MARG_SHORT:
		WRITE_SHORT(ival);
		break;
	case MARG_STRING:
		WRITE_STRING(sval.c_str());
		break;
	default:
		break;
	}
}

const char* MessageArg::getString() {
	switch (argType) {
	case MARG_ANGLE:  return UTIL_VarArgs("WRITE_ANGLE(%ff);", fval);
	case MARG_BYTE:   return UTIL_VarArgs("WRITE_BYTE(%d);", ival);
	case MARG_CHAR:   return UTIL_VarArgs("WRITE_CHAR(%d);", ival);
	case MARG_COORD:  return UTIL_VarArgs("WRITE_COORD(%ff);", fval);
	case MARG_ENT:    return UTIL_VarArgs("WRITE_ENTITY(%d);", ival);
	case MARG_LONG:   return UTIL_VarArgs("WRITE_LONG(%d);", ival);
	case MARG_SHORT:  return UTIL_VarArgs("WRITE_SHORT(%d);", ival);
	case MARG_STRING: return UTIL_VarArgs("WRITE_STRING(\"%s\");", sval.c_str());
	default:
		return "NONE";
	}
}

void NetMessage::send(int msg_dest, edict_t* new_ed) {
	if (msg_type == -1) {
		println("[Radio] Can't send unintialized net message");
		return;
	}

	const float* origin = hasOrigin ? pOrigin : NULL;

	MESSAGE_BEGIN(msg_dest, msg_type, origin, new_ed);

	for (int i = 0; i < args.size(); i++) {
		args[i].writeToCurrentMessage();
	}

	MESSAGE_END();
}

void NetMessage::send() {
	send(msg_dest, ed);
}

void NetMessage::clear() {
	args.clear();
	msg_type = -1;
}

const char* msgDestStr(int msg_dest) {
	const char* sdst = "";
	switch (msg_dest) {
	case MSG_BROADCAST:
		sdst = "MSG_BROADCAST";
		break;
	case MSG_ONE:
		sdst = "MSG_ONE";
		break;
	case MSG_ALL:
		sdst = "MSG_ALL";
		break;
	case MSG_INIT:
		sdst = "MSG_INIT";
		break;
	case MSG_PVS:
		sdst = "MSG_PVS";
		break;
	case MSG_PAS:
		sdst = "MSG_PAS";
		break;
	case MSG_PVS_R:
		sdst = "MSG_PVS_R";
		break;
	case MSG_PAS_R:
		sdst = "MSG_PAS_R";
		break;
	case MSG_ONE_UNRELIABLE:
		sdst = "MSG_ONE_UNRELIABLE";
		break;
	case MSG_SPEC:
		sdst = "MSG_SPEC";
		break;
	default:
		sdst = UTIL_VarArgs("%d (unkown)", msg_dest);
		break;
	}

	return sdst;
}

const char* msgTypeStr(int msg_type) {
	const char* sdst = "";

	switch (msg_type) {
	case SVC_BAD:
		sdst = "SVC_BAD";
		break;
	case SVC_NOP:
		sdst = "SVC_NOP";
		break;
	case SVC_DISCONNECT:
		sdst = "SVC_DISCONNECT";
		break;
	case SVC_EVENT:
		sdst = "SVC_EVENT";
		break;
	case SVC_VERSION:
		sdst = "SVC_VERSION";
		break;
	case SVC_SETVIEW:
		sdst = "SVC_SETVIEW";
		break;
	case SVC_SOUND:
		sdst = "SVC_SOUND";
		break;
	case SVC_TIME:
		sdst = "SVC_TIME";
		break;
	case SVC_PRINT:
		sdst = "SVC_PRINT";
		break;
	case SVC_STUFFTEXT:
		sdst = "SVC_STUFFTEXT";
		break;
	case SVC_SETANGLE:
		sdst = "SVC_SETANGLE";
		break;
	case SVC_SERVERINFO:
		sdst = "SVC_SERVERINFO";
		break;
	case SVC_LIGHTSTYLE:
		sdst = "SVC_LIGHTSTYLE";
		break;
	case SVC_UPDATEUSERINFO:
		sdst = "SVC_UPDATEUSERINFO";
		break;
	case SVC_DELTADESCRIPTION:
		sdst = "SVC_DELTADESCRIPTION";
		break;
	case SVC_CLIENTDATA:
		sdst = "SVC_CLIENTDATA";
		break;
	case SVC_STOPSOUND:
		sdst = "SVC_STOPSOUND";
		break;
	case SVC_PINGS:
		sdst = "SVC_PINGS";
		break;
	case SVC_PARTICLE:
		sdst = "SVC_PARTICLE";
		break;
	case SVC_DAMAGE:
		sdst = "SVC_DAMAGE";
		break;
	case SVC_SPAWNSTATIC:
		sdst = "SVC_SPAWNSTATIC";
		break;
	case SVC_EVENT_RELIABLE:
		sdst = "SVC_EVENT_RELIABLE";
		break;
	case SVC_SPAWNBASELINE:
		sdst = "SVC_SPAWNBASELINE";
		break;
	case SVC_TEMPENTITY:
		sdst = "SVC_TEMPENTITY";
		break;
	case SVC_SETPAUSE:
		sdst = "SVC_SETPAUSE";
		break;
	case SVC_SIGNONNUM:
		sdst = "SVC_SIGNONNUM";
		break;
	case SVC_CENTERPRINT:
		sdst = "SVC_CENTERPRINT";
		break;
	case SVC_KILLEDMONSTER:
		sdst = "SVC_KILLEDMONSTER";
		break;
	case SVC_FOUNDSECRET:
		sdst = "SVC_FOUNDSECRET";
		break;
	case SVC_SPAWNSTATICSOUND:
		sdst = "SVC_SPAWNSTATICSOUND";
		break;
	case SVC_INTERMISSION:
		sdst = "SVC_INTERMISSION";
		break;
	case SVC_FINALE:
		sdst = "SVC_FINALE";
		break;
	case SVC_CDTRACK:
		sdst = "SVC_CDTRACK";
		break;
	case SVC_RESTORE:
		sdst = "SVC_RESTORE";
		break;
	case SVC_CUTSCENE:
		sdst = "SVC_CUTSCENE";
		break;
	case SVC_WEAPONANIM:
		sdst = "SVC_WEAPONANIM";
		break;
	case SVC_DECALNAME:
		sdst = "SVC_DECALNAME";
		break;
	case SVC_ROOMTYPE:
		sdst = "SVC_ROOMTYPE";
		break;
	case SVC_ADDANGLE:
		sdst = "SVC_ADDANGLE";
		break;
	case SVC_NEWUSERMSG:
		sdst = "SVC_NEWUSERMSG";
		break;
	case SVC_PACKETENTITIES:
		sdst = "SVC_PACKETENTITIES";
		break;
	case SVC_DELTAPACKETENTITIES:
		sdst = "SVC_DELTAPACKETENTITIES";
		break;
	case SVC_CHOKE:
		sdst = "SVC_CHOKE";
		break;
	case SVC_RESOURCELIST:
		sdst = "SVC_RESOURCELIST";
		break;
	case SVC_NEWMOVEVARS:
		sdst = "SVC_NEWMOVEVARS";
		break;
	case SVC_RESOURCEREQUEST:
		sdst = "SVC_RESOURCEREQUEST";
		break;
	case SVC_CUSTOMIZATION:
		sdst = "SVC_CUSTOMIZATION";
		break;
	case SVC_CROSSHAIRANGLE:
		sdst = "SVC_CROSSHAIRANGLE";
		break;
	case SVC_SOUNDFADE:
		sdst = "SVC_SOUNDFADE";
		break;
	case SVC_FILETXFERFAILED:
		sdst = "SVC_FILETXFERFAILED";
		break;
	case SVC_HLTV:
		sdst = "SVC_HLTV";
		break;
	case SVC_DIRECTOR:
		sdst = "SVC_DIRECTOR";
		break;
	case SVC_VOICEINIT:
		sdst = "SVC_VOICEINIT";
		break;
	case SVC_VOICEDATA:
		sdst = "SVC_VOICEDATA";
		break;
	case SVC_SENDEXTRAINFO:
		sdst = "SVC_SENDEXTRAINFO";
		break;
	case SVC_TIMESCALE:
		sdst = "SVC_TIMESCALE";
		break;
	case SVC_RESOURCELOCATION:
		sdst = "SVC_RESOURCELOCATION";
		break;
	case SVC_SENDCVARVALUE:
		sdst = "SVC_SENDCVARVALUE";
		break;
	case SVC_SENDCVARVALUE2:
		sdst = "SVC_SENDCVARVALUE2";
		break;
	case MSG_SelAmmo:
		sdst = "MSG_SelAmmo";
		break;
	case MSG_CurWeapon:
		sdst = "MSG_CurWeapon";
		break;
	case MSG_Geiger:
		sdst = "MSG_Geiger";
		break;
	case MSG_Flashlight:
		sdst = "MSG_Flashlight";
		break;
	case MSG_FlashBat:
		sdst = "MSG_FlashBat";
		break;
	case MSG_Health:
		sdst = "MSG_Health";
		break;
	case MSG_Damage:
		sdst = "MSG_Damage";
		break;
	case MSG_Battery:
		sdst = "MSG_Battery";
		break;
	case MSG_Train:
		sdst = "MSG_Train";
		break;
	case MSG_HudText:
		sdst = "MSG_HudText";
		break;
	case MSG_SayText:
		sdst = "MSG_SayText";
		break;
	case MSG_TextMsg:
		sdst = "MSG_TextMsg";
		break;
	case MSG_WeaponList:
		sdst = "MSG_WeaponList";
		break;
	case MSG_CustWeapon:
		sdst = "MSG_CustWeapon";
		break;
	case MSG_ResetHUD:
		sdst = "MSG_ResetHUD";
		break;
	case MSG_InitHUD:
		sdst = "MSG_InitHUD";
		break;
	case MSG_CdAudio:
		sdst = "MSG_CdAudio";
		break;
	case MSG_GameTitle:
		sdst = "MSG_GameTitle";
		break;
	case MSG_DeathMsg:
		sdst = "MSG_DeathMsg";
		break;
	case MSG_ScoreInfo:
		sdst = "MSG_ScoreInfo";
		break;
	case MSG_TeamInfo:
		sdst = "MSG_TeamInfo";
		break;
	case MSG_TeamScore:
		sdst = "MSG_TeamScore";
		break;
	case MSG_GameMode:
		sdst = "MSG_GameMode";
		break;
	case MSG_MOTD:
		sdst = "MSG_MOTD";
		break;
	case MSG_AmmoPickup:
		sdst = "MSG_AmmoPickup";
		break;
	case MSG_WeapPickup:
		sdst = "MSG_WeapPickup";
		break;
	case MSG_ItemPickup:
		sdst = "MSG_ItemPickup";
		break;
	case MSG_HideHUD:
		sdst = "MSG_HideHUD";
		break;
	case MSG_SetFOV:
		sdst = "MSG_SetFOV";
		break;
	case MSG_ShowMenu:
		sdst = "MSG_ShowMenu";
		break;
	case MSG_ScreenShake:
		sdst = "MSG_ScreenShake";
		break;
	case MSG_ScreenFade:
		sdst = "MSG_ScreenFade";
		break;
	case MSG_AmmoX:
		sdst = "MSG_AmmoX";
		break;
	case MSG_Gib:
		sdst = "MSG_Gib";
		break;
	case MSG_Spectator:
		sdst = "MSG_Spectator";
		break;
	case MSG_TE_CUSTOM:
		sdst = "MSG_TE_CUSTOM";
		break;
	case MSG_Speaksent:
		sdst = "MSG_Speaksent";
		break;
	case MSG_TimeEnd:
		sdst = "MSG_TimeEnd";
		break;
	case MSG_MapList:
		sdst = "MSG_MapList";
		break;
	case MSG_CbElec:
		sdst = "MSG_CbElec";
		break;
	case MSG_EndVote:
		sdst = "MSG_EndVote";
		break;
	case MSG_VoteMenu:
		sdst = "MSG_VoteMenu";
		break;
	case MSG_NextMap:
		sdst = "MSG_NextMap";
		break;
	case MSG_StartSound:
		sdst = "MSG_StartSound";
		break;
	case MSG_SoundList:
		sdst = "MSG_SoundList";
		break;
	case MSG_ToxicCloud:
		sdst = "MSG_ToxicCloud";
		break;
	case MSG_ShkFlash:
		sdst = "MSG_ShkFlash";
		break;
	case MSG_CreateBlood:
		sdst = "MSG_CreateBlood";
		break;
	case MSG_GargSplash:
		sdst = "MSG_GargSplash";
		break;
	case MSG_SporeTrail:
		sdst = "MSG_SporeTrail";
		break;
	case MSG_TracerDecal:
		sdst = "MSG_TracerDecal";
		break;
	case MSG_SRDetonate:
		sdst = "MSG_SRDetonate";
		break;
	case MSG_SRPrimed:
		sdst = "MSG_SRPrimed";
		break;
	case MSG_SRPrimedOff:
		sdst = "MSG_SRPrimedOff";
		break;
	case MSG_RampSprite:
		sdst = "MSG_RampSprite";
		break;
	case MSG_ShieldRic:
		sdst = "MSG_ShieldRic";
		break;
	case MSG_Playlist:
		sdst = "MSG_Playlist";
		break;
	case MSG_VGUIMenu:
		sdst = "MSG_VGUIMenu";
		break;
	case MSG_ServerName:
		sdst = "MSG_ServerName";
		break;
	case MSG_TeamNames:
		sdst = "MSG_TeamNames";
		break;
	case MSG_ServerVer:
		sdst = "MSG_ServerVer";
		break;
	case MSG_ServerBuild:
		sdst = "MSG_ServerBuild";
		break;
	case MSG_WeatherFX:
		sdst = "MSG_WeatherFX";
		break;
	case MSG_CameraMouse:
		sdst = "MSG_CameraMouse";
		break;
	case MSG_Fog:
		sdst = "MSG_Fog";
		break;
	case MSG_PrtlUpdt:
		sdst = "MSG_PrtlUpdt";
		break;
	case MSG_ASScriptName:
		sdst = "MSG_ASScriptName";
		break;
	case MSG_PrintKB:
		sdst = "MSG_PrintKB";
		break;
	case MSG_InvAdd:
		sdst = "MSG_InvAdd";
		break;
	case MSG_InvRemove:
		sdst = "MSG_InvRemove";
		break;
	case MSG_Concuss:
		sdst = "MSG_Concuss";
		break;
	case MSG_ViewMode:
		sdst = "MSG_ViewMode";
		break;
	case MSG_Flamethwr:
		sdst = "MSG_Flamethwr";
		break;
	case MSG_ClassicMode:
		sdst = "MSG_ClassicMode";
		break;
	case MSG_WeaponSpr:
		sdst = "MSG_WeaponSpr";
		break;
	case MSG_ToggleElem:
		sdst = "MSG_ToggleElem";
		break;
	case MSG_CustSpr:
		sdst = "MSG_CustSpr";
		break;
	case MSG_NumDisplay:
		sdst = "MSG_NumDisplay";
		break;
	case MSG_UpdateNum:
		sdst = "MSG_UpdateNum";
		break;
	case MSG_TimeDisplay:
		sdst = "MSG_TimeDisplay";
		break;
	case MSG_UpdateTime:
		sdst = "MSG_UpdateTime";
		break;
	case MSG_VModelPos:
		sdst = "MSG_VModelPos";
		break;
	default:
		sdst = UTIL_VarArgs("%d (unkown)", msg_type);
		break;
	}

	return sdst;
}

void NetMessage::print() {
	bool hasOrigin = pOrigin[0] != 0 || pOrigin[1] != 0 || pOrigin[2] != 0;
	const char* origin = hasOrigin ? UTIL_VarArgs("Vector(%f %f %f)", pOrigin[0], pOrigin[1], pOrigin[2]) : "NULL";
	const char* sed = ed ? STRING(ed->v.netname) : "NULL";

	println("MESSAGE_BEGIN(%s, %s, %s, %s);", msgDestStr(msg_dest), msgTypeStr(msg_type), origin, sed);
	for (int i = 0; i < args.size(); i++) {
		println("    %s", args[i].getString());
	}
	println("MESSAGE_END();");
}