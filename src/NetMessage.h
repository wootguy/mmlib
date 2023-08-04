#pragma once
#include <string>
#include <vector>
#include <extdll.h>

enum message_arg_types {
	MARG_NONE,
	MARG_ANGLE,
	MARG_BYTE,
	MARG_CHAR,
	MARG_COORD,
	MARG_ENT,
	MARG_LONG,
	MARG_SHORT,
	MARG_STRING
};

struct MessageArg {
	int argType = MARG_NONE;
	int ival = 0;
	float fval = 0;
	std::string sval = "";

	MessageArg(int argType, int ival);
	MessageArg(int argType, float ival);
	MessageArg(int argType, std::string sval);
	void writeToCurrentMessage();
	const char* getString();
};

struct NetMessage {
	std::vector<MessageArg> args;
	int msg_type = -1;
	int msg_dest;
	float pOrigin[3];
	bool hasOrigin;
	edict_t* ed;

	NetMessage() {}
	void send(int msg_dest, edict_t* ed);
	void send();
	void clear();
	void print();
};