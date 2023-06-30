#include "UserInfo.h"

using namespace std;


UserInfo::UserInfo() {}

UserInfo::UserInfo(edict_t* plr) {
	setInfo(plr);
}

void UserInfo::setInfo(edict_t* plr) {
	char* info = g_engfuncs.pfnGetInfoKeyBuffer(plr);
	
	cl_lw = INFOKEY_VALUE(info, "cl_lw");
	cl_lc = INFOKEY_VALUE(info, "cl_lc");
	bottomcolor = INFOKEY_VALUE(info, "bottomcolor");
	cl_dlmax = INFOKEY_VALUE(info, "cl_dlmax");
	cl_updaterate = INFOKEY_VALUE(info, "cl_updaterate");
	topcolor = INFOKEY_VALUE(info, "topcolor");
	name = INFOKEY_VALUE(info, "name");
	sid = INFOKEY_VALUE(info, "*sid");
	rate = INFOKEY_VALUE(info, "rate");
	cl_hidextra = INFOKEY_VALUE(info, "cl_hidextra");
	cl_hideadmin = INFOKEY_VALUE(info, "cl_hideadmin");
	hud_weaponautoswitch = INFOKEY_VALUE(info, "hud_weaponautoswitch");
	model = INFOKEY_VALUE(info, "model");

	index = ENTINDEX(plr) - 1;
}

string UserInfo::infoString() {
	return "\\cl_lw\\" + cl_lw
		+ "\\cl_lc\\" + cl_lc
		+ "\\bottomcolor\\" + bottomcolor
		+ "\\cl_dlmax\\" + cl_dlmax
		+ "\\cl_updaterate\\" + cl_updaterate
		+ "\\topcolor\\" + topcolor
		+ "\\name\\" + name
		+ "\\*sid\\" + sid
		+ "\\rate\\" + rate
		+ "\\cl_hidextra\\" + cl_hidextra
		+ "\\cl_hideadmin\\" + cl_hideadmin
		+ "\\hud_weaponautoswitch\\" + hud_weaponautoswitch
		+ "\\model\\" + model;
}

// send info only to one player
void UserInfo::send(edict_t* target) {
	// SVC_UPDATEUSERINFO
	MESSAGE_BEGIN(MSG_ONE, SVC_UPDATEUSERINFO, NULL, target);
	WRITE_BYTE(index); // player index (0 based)
	WRITE_LONG(0); // client user id (???)
	WRITE_STRING(infoString().c_str());

	// CD Key hash (???)
	for (int i = 0; i < 16; i++) {
		WRITE_BYTE(0x00);
	}
	MESSAGE_END();
}

// send info to everyone
void UserInfo::broadcast() {
	// SVC_UPDATEUSERINFO
	MESSAGE_BEGIN(MSG_ALL, SVC_UPDATEUSERINFO, NULL, (edict_t*)NULL);
	WRITE_BYTE(index); // player index (0 based)
	WRITE_LONG(0); // client user id (???)
	WRITE_STRING(infoString().c_str());

	// CD Key hash (???)
	for (int i = 0; i < 16; i++) {
		WRITE_BYTE(0x00);
	}
	MESSAGE_END();
}