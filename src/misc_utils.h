#pragma once
#include <extdll.h>
#include <meta_api.h>
#include <string>
#include <map>
#include "private_api.h"

#define MSG_ChatMsg 74
#define MSG_TextMsg 75

#define println(fmt,...) {ALERT(at_console, (char*)(std::string(fmt) + "\n").c_str(), ##__VA_ARGS__); }

// prevent conflicts with auto-included headers
#define Min(a,b)            (((a) < (b)) ? (a) : (b))
#define Max(a,b)           (((a) > (b)) ? (a) : (b))

std::string replaceString(std::string subject, std::string search, std::string replace);

edict_t* getPlayerByUniqueId(std::string id);

std::string getPlayerUniqueId(edict_t* plr);

bool isValidPlayer(edict_t* plr);

std::string trimSpaces(std::string s);

std::string toLowerCase(std::string str);

std::string vecToString(Vector vec);

void ClientPrintAll(int msg_dest, const char* msg_name, const char* param1 = NULL, const char* param2 = NULL, const char* param3 = NULL, const char* param4 = NULL);

void ClientPrint(edict_t* client, int msg_dest, const char* msg_name, const char* param1 = NULL, const char* param2 = NULL, const char* param3 = NULL, const char* param4 = NULL);

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