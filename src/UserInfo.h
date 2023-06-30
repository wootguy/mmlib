#pragma once
#include "private_api.h"

#define SVC_UPDATEUSERINFO 13

// This is used to send player info to a single client instead of globally.
// This way you can swap someone else's player model without them also seeing the swapped model.
struct UserInfo {
	int index = 0; // entityindex() - 1

	std::string cl_lw;
	std::string cl_lc;
	std::string bottomcolor;
	std::string cl_dlmax;
	std::string cl_updaterate;
	std::string topcolor;
	std::string name;
	std::string sid;
	std::string rate;
	std::string cl_hidextra;
	std::string cl_hideadmin;
	std::string hud_weaponautoswitch;
	std::string model;

	UserInfo();

	UserInfo(edict_t* plr);

	void setInfo(edict_t* plr);

	std::string infoString();

	// send info only to one player
	void send(edict_t* target);

	// send info to everyone
	void broadcast();
};
