#include "meta_helper.h"
#include "misc_utils.h"

using namespace std;

// keep in sync with the angelscript plugin
enum custom_key_types {
	KEY_TYPE_INTEGER,
	KEY_TYPE_FLOAT,
	KEY_TYPE_STRING,
	KEY_TYPE_VECTOR,
};

void hook_angelscript(string hook, string cmdname, void (*callback)()) {
	REG_SVR_COMMAND((char*)cmdname.c_str(), callback);
	g_engfuncs.pfnServerCommand((char*)("as_command .RegisterHook \"" + hook + "\" \"" + cmdname + "\";").c_str());
	g_engfuncs.pfnServerExecute();
}

int readCustomKeyvalueInteger(edict_t* ent, string keyName) {
	int oldVal = ent->v.iuser4;

	g_engfuncs.pfnServerCommand((char*)("as_command .CustomKeyRead " + to_string(ENTINDEX(ent)) + " " + keyName + " 0;").c_str());
	g_engfuncs.pfnServerExecute();
	int retVal = ent->v.iuser4;

	ent->v.iuser4 = oldVal;

	return retVal;
}

float readCustomKeyvalueFloat(edict_t* ent, string keyName) {
	float oldVal = ent->v.fuser4;

	g_engfuncs.pfnServerCommand((char*)("as_command .CustomKeyRead " + to_string(ENTINDEX(ent)) + " " + keyName + " 1;").c_str());
	g_engfuncs.pfnServerExecute();
	float retVal = ent->v.fuser4;

	ent->v.iuser4 = oldVal;

	return retVal;
}

string readCustomKeyvalueString(edict_t* ent, string keyName) {
	string_t oldVal = ent->v.noise3;

	g_engfuncs.pfnServerCommand((char*)("as_command .CustomKeyRead " + to_string(ENTINDEX(ent)) + " " + keyName + " 2;").c_str());
	g_engfuncs.pfnServerExecute();
	string retVal = STRING(ent->v.noise3);

	ent->v.noise3 = oldVal;

	return retVal;
}

Vector readCustomKeyvalueVector(edict_t* ent, string keyName) {
	Vector oldVal = ent->v.vuser4;

	g_engfuncs.pfnServerCommand((char*)("as_command .CustomKeyRead " + to_string(ENTINDEX(ent)) + " " + keyName + " 3;").c_str());
	g_engfuncs.pfnServerExecute();
	Vector retVal = ent->v.vuser4;

	ent->v.vuser4 = oldVal;

	return retVal;
}

void writeCustomKeyvalue(edict_t* ent, string keyName, int value) {
	string args = to_string(ENTINDEX(ent)) + " " + to_string(KEY_TYPE_INTEGER) + " " + keyName + " " + to_string(value);

	g_engfuncs.pfnServerCommand((char*)("as_command .CustomKeyWrite " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void writeCustomKeyvalue(edict_t* ent, string keyName, float value) {
	string args = to_string(ENTINDEX(ent)) + " " + to_string(KEY_TYPE_FLOAT) + " " + keyName + " " + to_string(value);

	g_engfuncs.pfnServerCommand((char*)("as_command .CustomKeyWrite " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void writeCustomKeyvalue(edict_t* ent, string keyName, string value) {
	string args = to_string(ENTINDEX(ent)) + " " + to_string(KEY_TYPE_STRING) + " " + keyName + " " + value;

	g_engfuncs.pfnServerCommand((char*)("as_command .CustomKeyWrite " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void writeCustomKeyvalue(edict_t* ent, string keyName, Vector value) {
	string args = to_string(ENTINDEX(ent)) + " " + to_string(KEY_TYPE_VECTOR) + " " + keyName + " \"" + vecToString(value) + "\"";

	g_engfuncs.pfnServerCommand((char*)("as_command .CustomKeyWrite " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

bool customKeyvalueExists(edict_t* ent, string keyName) {
	string args = to_string(ENTINDEX(ent)) + " " + keyName;

	int oldVal = ent->v.iuser4;
	g_engfuncs.pfnServerCommand((char*)("as_command .CustomKeyExists " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
	int retVal = ent->v.iuser4;

	ent->v.iuser4 = oldVal;

	return retVal != 0;
}

void TakeDamage(edict_t* victim, edict_t* inflictor, edict_t* attacker, float damage, int damageType) {
	string s_victim = to_string(ENTINDEX(victim));
	string s_inflictor = to_string(ENTINDEX(inflictor));
	string s_attacker = to_string(ENTINDEX(attacker));
	string s_damage = to_string(damage);
	string s_damageType = to_string(damageType);
	string args = s_victim + " " + s_inflictor + " " + s_attacker + " " + s_damage + " " + s_damageType;
	
	g_engfuncs.pfnServerCommand((char*)("as_command .EntTakeDamage " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void Killed(edict_t* victim, edict_t* attacker, int gibMode) {
	string s_victim = to_string(ENTINDEX(victim));
	string s_attacker = to_string(ENTINDEX(attacker));
	string s_gibMode = to_string(gibMode);
	string args = s_victim + " " + s_attacker + " " + s_gibMode;

	g_engfuncs.pfnServerCommand((char*)("as_command .EntKill " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void Revive(edict_t* target) {
	g_engfuncs.pfnServerCommand((char*)("as_command .EntRevive " + to_string(ENTINDEX(target)) + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void Use(edict_t* target, edict_t* activator, edict_t* caller, int useType) {
	string s_target = to_string(ENTINDEX(target));
	string s_activator = to_string(ENTINDEX(activator));
	string s_caller = to_string(ENTINDEX(caller));
	string s_useType = to_string(useType);
	string args = s_target + " " + s_activator + " " + s_caller + " " + s_useType;

	g_engfuncs.pfnServerCommand((char*)("as_command .Use " + args + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void PrecacheSound(string snd) {
	g_engfuncs.pfnServerCommand((char*)("as_command .PrecacheSound " + snd + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void PrecacheModel(string mdl) {
	g_engfuncs.pfnServerCommand((char*)("as_command .PrecacheModel " + mdl + ";").c_str());
	g_engfuncs.pfnServerExecute();
}

void PrecacheGeneric(string mdl) {
	g_engfuncs.pfnServerCommand((char*)("as_command .PrecacheGeneric " + mdl + ";").c_str());
	g_engfuncs.pfnServerExecute();
}