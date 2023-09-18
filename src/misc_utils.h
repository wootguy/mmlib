#pragma once
#include <extdll.h>
#include <meta_api.h>
#include <string>
#include <map>
#include "private_api.h"
#include "ThreadSafeQueue.h"
#include <thread>

extern std::thread::id g_main_thread_id;
extern ThreadSafeQueue<std::string> g_thread_prints;
extern ThreadSafeQueue<std::string> g_thread_logs;

// thread safe console printing
// remember to call handleThreadPrints() every frame in multi-threaded plugins
#define println(fmt,...) { \
	if (std::this_thread::get_id() == g_main_thread_id) { \
		ALERT(at_console, (char*)(std::string(fmt) + "\n").c_str(), ##__VA_ARGS__ ); \
	} \
	else { \
		g_thread_prints.enqueue(UTIL_VarArgs((char*)string(fmt).c_str(), ##__VA_ARGS__ )); \
	} \
}

#define logln(fmt,...) { \
	if (std::this_thread::get_id() == g_main_thread_id) { \
		ALERT(at_logged, (char*)(std::string(fmt) + "\n").c_str(), ##__VA_ARGS__ ); \
	} \
	else { \
		g_thread_logs.enqueue(UTIL_VarArgs((char*)string(fmt).c_str(), ##__VA_ARGS__ )); \
	} \
}

// p in printp meaning "part of line" I guess, instead of "ln" for complete line (newline)
#define printp(fmt,...) { \
	if (std::this_thread::get_id() == g_main_thread_id) { \
		ALERT(at_console, (char*)(std::string(fmt)).c_str(), ##__VA_ARGS__ ); \
	} \
	else { \
		g_thread_prints.enqueue(UTIL_VarArgs((char*)string(fmt).c_str(), ##__VA_ARGS__ )); \
	} \
}

#define logp(fmt,...) { \
	if (std::this_thread::get_id() == g_main_thread_id) { \
		ALERT(at_logged, (char*)(std::string(fmt)).c_str(), ##__VA_ARGS__ ); \
	} \
	else { \
		g_thread_logs.enqueue(UTIL_VarArgs((char*)string(fmt).c_str(), ##__VA_ARGS__ )); \
	} \
}

// prevent conflicts with auto-included headers
#define Min(a, b) (((a) < (b)) ? (a) : (b))
#define Max(a, b) (((a) > (b)) ? (a) : (b))

std::string replaceString(std::string subject, std::string search, std::string replace);

std::vector<std::string> splitString(std::string str, const char* delimitters);

edict_t* getPlayerByUniqueId(std::string id);

// unique ID = Steam ID or name if on LAN
std::string getPlayerUniqueId(edict_t* plr);

// User IDs change every time a user connects to the server
edict_t* getPlayerByUserId(int id);

edict_t* getPlayerByName(edict_t* caller, std::string name, bool printError=true);

bool isValidPlayer(edict_t* plr);

std::string trimSpaces(std::string s);

std::string toLowerCase(std::string str);

std::string toUpperCase(std::string str);

std::string vecToString(Vector vec);

void ClientPrintAll(int msg_dest, const char* msg_name, const char* param1 = NULL, const char* param2 = NULL, const char* param3 = NULL, const char* param4 = NULL);

void ClientPrint(edict_t* client, int msg_dest, const char* msg_name, const char* param1 = NULL, const char* param2 = NULL, const char* param3 = NULL, const char* param4 = NULL);

void clientCommand(edict_t* plr, std::string cmd, int destType = MSG_ONE);

// call this every frame if printing from multiple threads
void handleThreadPrints();

void HudMessageAll(const hudtextparms_t& textparms, const char* pMessage, int dest = -1);

void HudMessage(edict_t* pEntity, const hudtextparms_t& textparms, const char* pMessage, int dest = -1);

char* UTIL_VarArgs(char* format, ...);

CBaseEntity* CreateEntity(const char* cname, std::map<std::string, std::string> keyvalues= std::map<std::string, std::string>(), bool spawn = true);

void GetSequenceInfo(void* pmodel, entvars_t* pev, float* pflFrameRate, float* pflGroundSpeed);

int GetSequenceFlags(void* pmodel, entvars_t* pev);

float SetController(void* pmodel, entvars_t* pev, int iController, float flValue);

float clampf(float val, float min, float max);

int clamp(int val, int min, int max);

CBaseEntity* FindEntityForward(CBaseEntity* ent, float maxDist);

// true if ent returned by FindEntity* engine funcs is valid
bool isValidFindEnt(edict_t* ent);

void RemoveEntity(edict_t* ent);

// send a message the angelscript chat bridge plugin
void RelaySay(std::string message);

bool fileExists(std::string path);

float normalizeRangef(const float value, const float start, const float end);

void kickPlayer(edict_t* ent, const char* reason="");