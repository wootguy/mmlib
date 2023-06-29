#pragma once
#include <extdll.h>
#include <meta_api.h>
#include <string>
#include <vector>
#include <map>

#define MAX_PLAYERS 32

#define MSG_TextMsg 75

// get a player index as a bitfield index
#define PLAYER_BIT(edt) (1 << (ENTINDEX(edt) % 32))

#define println(fmt,...) {ALERT(at_console, (char*)(std::string(fmt) + "\n").c_str(), ##__VA_ARGS__);}
#define logln(fmt, ...) {ALERT(at_logged, (char*)(std::string(fmt) + "\n").c_str(), ##__VA_ARGS__);}

struct CommandArgs {
	std::vector<std::string> args;
	bool isConsoleCmd;
	
	// gets current globally defined args
	CommandArgs();

	void loadArgs();

	// returns empty string if idx is out of bounds
	std::string ArgV(int idx);

	// return number of args
	int ArgC();

	// return entire command string
	std::string getFullCommand();
};

std::string toLowerCase(std::string str);

cvar_t* RegisterCVar(char* name, char* strDefaultValue, int intDefaultValue, int flags);

void LoadAdminList(); // call on each map change, so AdminLevel can work
int AdminLevel(edict_t* player);
uint64_t getEpochMillis();
double TimeDifference(uint64_t start, uint64_t end);
bool cgetline(FILE* file, std::string& output);
