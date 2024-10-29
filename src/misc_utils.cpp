#include "misc_utils.h"
#include "meta_init.h"
#include "studio.h"
#include "Scheduler.h"
#include "meta_helper.h"
#include "meta_utils.h"
#include <algorithm>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
#define stat _stat
#else
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#endif

#ifdef HLCOOP_BUILD
#include "cbase.h"
typedef EHANDLE EHandle;
#endif

using namespace std;

thread::id g_main_thread_id = std::this_thread::get_id();
ThreadSafeQueue<string> g_thread_prints;
ThreadSafeQueue<string> g_thread_logs;

string getFileExtension(string fpath) {
	int dot = fpath.find_last_of(".");
	if (dot != -1 && dot < fpath.size()-1) {
		return fpath.substr(dot + 1);
	}

	return "";
}

string getPlayerUniqueId(edict_t* plr) {
	if (plr == NULL) {
		return "STEAM_ID_NULL";
	}

	string steamId = (*g_engfuncs.pfnGetPlayerAuthId)(plr);

	if (steamId == "STEAM_ID_LAN" || steamId == "BOT") {
		steamId = STRING(plr->v.netname);
	}

	return steamId;
}

uint64_t getPlayerCommunityId(edict_t* plr) {
	string id = getPlayerUniqueId(plr);

	if (id == "STEAM_ID_NULL" || id == "STEAM_ID_LAN" || id == "BOT") {
		return 0;
	}

	return steamid_to_steamid64(id);
}

string replaceString(string subject, string search, string replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

vector<string> splitString(string str, const char* delimitters)
{
	vector<string> split;
	size_t start = 0;
	size_t end = str.find_first_of(delimitters);

	while (end != std::string::npos)
	{
		split.push_back(str.substr(start, end - start));
		start = end + 1;
		end = str.find_first_of(delimitters, start);
	}

	split.push_back(str.substr(start));

	return split;
}

edict_t* getPlayerByUniqueId(string id) {
	for (int i = 1; i <= gpGlobals->maxClients; i++) {
		edict_t* ent = INDEXENT(i);

		if (!ent || (ent->v.flags & FL_CLIENT) == 0) {
			continue;
		}

		if (id == getPlayerUniqueId(ent)) {
			return ent;
		}
	}

	return NULL;
}

edict_t* getPlayerByUserId(int id) {
	for (int i = 1; i <= gpGlobals->maxClients; i++) {
		edict_t* ent = INDEXENT(i);

		if (!isValidPlayer(ent)) {
			continue;
		}

		if (id == (*g_engfuncs.pfnGetPlayerUserId)(ent)) {
			return ent;
		}
	}

	return NULL;
}

edict_t* getPlayerByName(edict_t* caller, string name, bool printError) {
	name = toLowerCase(name);
	int partialMatches = 0;
	edict_t* partialMatch;

	for (int i = 1; i <= gpGlobals->maxClients; i++) {
		edict_t* plr = INDEXENT(i);

		if (!isValidPlayer(plr)) {
			continue;
		}

		const string steamId = toLowerCase(getPlayerUniqueId(plr));

		string plrName = toLowerCase(STRING(plr->v.netname));
		if (plrName == name || steamId == name)
			return plr;
		else if (plrName.find(name) != -1)
		{
			partialMatch = plr;
			partialMatches++;
		}
	}

	if (partialMatches == 1) {
		return partialMatch;
	}
	else if (partialMatches > 1) {
		if (printError)
			ClientPrint(caller, HUD_PRINTTALK, UTIL_VarArgs("There are %d players that have \"%s\" in their name. Be more specific.", partialMatches, name.c_str()));
	}
	else if (printError) {
		ClientPrint(caller, HUD_PRINTTALK, UTIL_VarArgs("There is no player named \"%s\"", name.c_str()));
	}

	return NULL;
}

bool isValidPlayer(edict_t* plr) {
	return plr && (plr->v.flags & FL_CLIENT) != 0 && (plr->v.flags & FL_PROXY) == 0 && STRING(plr->v.netname)[0] != '\0';
}

string trimSpaces(string s) {
	int start = s.find_first_not_of(" \t\n\r");
	int end = s.find_last_not_of(" \t\n\r");
	return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

string toLowerCase(string str) {
	string out = str;

	for (int i = 0; str[i]; i++) {
		out[i] = tolower(str[i]);
	}

	return out;
}

string toUpperCase(string str) {
	string out = str;

	for (int i = 0; str[i]; i++) {
		out[i] = toupper(str[i]);
	}

	return out;
}

string vecToString(Vector vec) {
	return UTIL_VarArgs("%f, %f, %f", vec.x, vec.y, vec.z);
}

void ClientPrintAll(int msg_dest, const char* msg_name, const char* param1, const char* param2, const char* param3, const char* param4) {
	ClientPrint((edict_t*)NULL, msg_dest, msg_name, param1, param2, param3, param4);
}

void ClientPrint(edict_t* client, int msg_dest, const char* msg_name, const char* param1, const char* param2, const char* param3, const char* param4) {
	int dest = client ? MSG_ONE : MSG_ALL;
	
	MESSAGE_BEGIN(dest, MSG_TextMsg, NULL, client);
	WRITE_BYTE(msg_dest);
	WRITE_STRING(msg_name);

	if (param1)
		WRITE_STRING(param1);
	if (param2)
		WRITE_STRING(param2);
	if (param3)
		WRITE_STRING(param3);
	if (param4)
		WRITE_STRING(param4);

	MESSAGE_END();
}

void clientCommand(edict_t* plr, string cmd, int destType) {
	MESSAGE_BEGIN(destType, 9, NULL, plr);
	WRITE_STRING(UTIL_VarArgs(";%s;", cmd.c_str()));
	MESSAGE_END();
}

void handleThreadPrints() {
	string msg;
	for (int failsafe = 0; failsafe < 128; failsafe++) {
		if (g_thread_prints.dequeue(msg)) {
			println(msg.c_str());
		}
		else {
			break;
		}
	}

	for (int failsafe = 0; failsafe < 128; failsafe++) {
		if (g_thread_logs.dequeue(msg)) {
			logln(msg.c_str());
		}
		else {
			break;
		}
	}
}

unsigned short FixedUnsigned16(float value, float scale)
{
	int output;

	output = value * scale;
	if (output < 0)
		output = 0;
	if (output > 0xFFFF)
		output = 0xFFFF;

	return (unsigned short)output;
}

short FixedSigned16(float value, float scale)
{
	int output;

	output = value * scale;

	if (output > 32767)
		output = 32767;

	if (output < -32768)
		output = -32768;

	return (short)output;
}

// modified to not use CBaseEntity or loop through players to send individual messages
void HudMessage(edict_t* pEntity, const hudtextparms_t& textparms, const char* pMessage, int dest)
{
	if (dest == -1) {
		dest = pEntity ? MSG_ONE : MSG_ALL;
	}

	MESSAGE_BEGIN(dest, SVC_TEMPENTITY, NULL, pEntity);
	WRITE_BYTE(TE_TEXTMESSAGE);
	WRITE_BYTE(textparms.channel & 0xFF);

	WRITE_SHORT(FixedSigned16(textparms.x, 1 << 13));
	WRITE_SHORT(FixedSigned16(textparms.y, 1 << 13));
	WRITE_BYTE(textparms.effect);

	WRITE_BYTE(textparms.r1);
	WRITE_BYTE(textparms.g1);
	WRITE_BYTE(textparms.b1);
	WRITE_BYTE(textparms.a1);

	WRITE_BYTE(textparms.r2);
	WRITE_BYTE(textparms.g2);
	WRITE_BYTE(textparms.b2);
	WRITE_BYTE(textparms.a2);

	WRITE_SHORT(FixedUnsigned16(textparms.fadeinTime, 1 << 8));
	WRITE_SHORT(FixedUnsigned16(textparms.fadeoutTime, 1 << 8));
	WRITE_SHORT(FixedUnsigned16(textparms.holdTime, 1 << 8));

	if (textparms.effect == 2)
		WRITE_SHORT(FixedUnsigned16(textparms.fxTime, 1 << 8));

	if (strlen(pMessage) < 512)
	{
		WRITE_STRING(pMessage);
	}
	else
	{
		char tmp[512];
		strncpy(tmp, pMessage, 511);
		tmp[511] = 0;
		WRITE_STRING(tmp);
	}
	MESSAGE_END();
}

void HudMessageAll(const hudtextparms_t& textparms, const char* pMessage, int dest)
{
	HudMessage(NULL, textparms, pMessage, dest);
}

char* UTIL_VarArgs(char* format, ...)
{
	va_list		argptr;
	static char		string[1024];

	va_start(argptr, format);
	vsprintf(string, format, argptr);
	va_end(argptr);

	return string;
}

CBaseEntity* CreateEntity(const char* cname, map<string, string> keyvalues, bool spawn) {
	// using MAKE_STRING would crash the game when unloading this plugin (pointer to invalid memory).
	// That's true even if deleting the entities in PLuginExit
	edict_t* ent = g_engfuncs.pfnCreateNamedEntity(ALLOC_STRING(cname));

	if (!ent) {
		return NULL;
	}

	for (auto item : keyvalues) {
		KeyValueData dat;
		dat.fHandled = false;
		dat.szClassName = (char*)STRING(ent->v.classname);
		dat.szKeyName = (char*)item.first.c_str();
		dat.szValue = (char*)item.second.c_str();
		gpGamedllFuncs->dllapi_table->pfnKeyValue(ent, &dat);
	}

	if (spawn) {
		gpGamedllFuncs->dllapi_table->pfnSpawn(ent);
	}

	CBaseEntity* ok = (CBaseEntity*)GET_PRIVATE(ent);

	return ok;
}

void GetSequenceInfo(void* pmodel, entvars_t* pev, float* pflFrameRate, float* pflGroundSpeed)
{
	studiohdr_t* pstudiohdr;

	pstudiohdr = (studiohdr_t*)pmodel;
	if (!pstudiohdr)
		return;

	mstudioseqdesc_t* pseqdesc;

	if (pev->sequence >= pstudiohdr->numseq)
	{
		*pflFrameRate = 0.0;
		*pflGroundSpeed = 0.0;
		return;
	}

	pseqdesc = (mstudioseqdesc_t*)((byte*)pstudiohdr + pstudiohdr->seqindex) + (int)pev->sequence;

	if (pseqdesc->numframes > 1)
	{
		*pflFrameRate = 256 * pseqdesc->fps / (pseqdesc->numframes - 1);
		*pflGroundSpeed = sqrt(pseqdesc->linearmovement[0] * pseqdesc->linearmovement[0] + pseqdesc->linearmovement[1] * pseqdesc->linearmovement[1] + pseqdesc->linearmovement[2] * pseqdesc->linearmovement[2]);
		*pflGroundSpeed = *pflGroundSpeed * pseqdesc->fps / (pseqdesc->numframes - 1);
	}
	else
	{
		*pflFrameRate = 256.0;
		*pflGroundSpeed = 0.0;
	}
}

int GetSequenceFlags(void* pmodel, entvars_t* pev)
{
	studiohdr_t* pstudiohdr;

	pstudiohdr = (studiohdr_t*)pmodel;
	if (!pstudiohdr || pev->sequence >= pstudiohdr->numseq)
		return 0;

	mstudioseqdesc_t* pseqdesc;
	pseqdesc = (mstudioseqdesc_t*)((byte*)pstudiohdr + pstudiohdr->seqindex) + (int)pev->sequence;

	return pseqdesc->flags;
}

float SetController(void* pmodel, entvars_t* pev, int iController, float flValue)
{
	studiohdr_t* pstudiohdr;
	int i;

	pstudiohdr = (studiohdr_t*)pmodel;
	if (!pstudiohdr)
		return flValue;

	mstudiobonecontroller_t* pbonecontroller = (mstudiobonecontroller_t*)((byte*)pstudiohdr + pstudiohdr->bonecontrollerindex);

	// find first controller that matches the index
	for (i = 0; i < pstudiohdr->numbonecontrollers; i++, pbonecontroller++)
	{
		if (pbonecontroller->index == iController)
			break;
	}
	if (i >= pstudiohdr->numbonecontrollers)
		return flValue;

	// wrap 0..360 if it's a rotational controller

	if (pbonecontroller->type & (STUDIO_XR | STUDIO_YR | STUDIO_ZR))
	{
		// ugly hack, invert value if end < start
		if (pbonecontroller->end < pbonecontroller->start)
			flValue = -flValue;

		// does the controller not wrap?
		if (pbonecontroller->start + 359.0 >= pbonecontroller->end)
		{
			if (flValue > ((pbonecontroller->start + pbonecontroller->end) / 2.0) + 180)
				flValue = flValue - 360;
			if (flValue < ((pbonecontroller->start + pbonecontroller->end) / 2.0) - 180)
				flValue = flValue + 360;
		}
		else
		{
			if (flValue > 360)
				flValue = flValue - (int)(flValue / 360.0) * 360.0;
			else if (flValue < 0)
				flValue = flValue + (int)((flValue / -360.0) + 1) * 360.0;
		}
	}

	int setting = 255 * (flValue - pbonecontroller->start) / (pbonecontroller->end - pbonecontroller->start);

	if (setting < 0) setting = 0;
	if (setting > 255) setting = 255;
	pev->controller[iController] = setting;

	return setting * (1.0 / 255.0) * (pbonecontroller->end - pbonecontroller->start) + pbonecontroller->start;
}

float clampf(float val, float min, float max) {
	if (val > max) {
		return max;
	}
	else if (val < min) {
		return min;
	}
	return val;
}

int clamp(int val, int min, int max) {
	if (val > max) {
		return max;
	}
	else if (val < min) {
		return min;
	}
	return val;
}

CBaseEntity* FindEntityForward(CBaseEntity* ent, float maxDist) {
	if (!ent) {
		return NULL;
	}
	maxDist = Min(maxDist, 12048); // according to angelscript docs

	// TODO: check how monsters are handled (angles instead of v_angle?)

	MAKE_VECTORS(ent->pev->v_angle);
	Vector lookDir = gpGlobals->v_forward;

	Vector start = ent->pev->origin + ent->pev->view_ofs;
	Vector end = start + lookDir * maxDist;

	TraceResult tr;
	TRACE_LINE(start, end, dont_ignore_monsters, ent->edict(), &tr);

	return (CBaseEntity*)GET_PRIVATE(tr.pHit);
}

bool isValidFindEnt(edict_t* ent) {
	return ent && !ent->free && ENTINDEX(ent) != 0;
}

void RemoveEntityDelay(EHandle h_ent) {
#ifdef HLCOOP_BUILD
	if (h_ent) {
		REMOVE_ENTITY(h_ent.GetEdict());
	}
#else
	if (h_ent.IsValid()) {
		REMOVE_ENTITY(h_ent);
	}
#endif
	
}

void RemoveEntity(edict_t* ent) {
	if (ent) {
#ifdef HLCOOP_BUILD
		if (ent->v.flags & FL_CLIENT) {
			CBaseEntity* plr = CBaseEntity::Instance(ent);
			plr->Killed(&INDEXENT(0)->v, GIB_ALWAYS);
		}
		else {
			// removing entities in the current frame will mess up FindEntity* funcs
			EHANDLE h_ent;
			h_ent.Set(ent);
			g_Scheduler.SetTimeout(RemoveEntityDelay, 0.0f, h_ent);
		}
#else
		if (ent->v.flags & FL_CLIENT) {
			Killed(ent, INDEXENT(0), GIB_ALWAYS);
		}
		else {
			// removing entities in the current frame will mess up FindEntity* funcs
			g_Scheduler.SetTimeout(RemoveEntityDelay, 0.0f, EHandle(ent));
		}
#endif
	}
}

void RelaySay(string message) {
	message.erase(std::remove(message.begin(), message.end(), '\n'), message.end()); // stip any newlines, ChatBridge.as takes care
	replaceString(message, "\"", "'"); // replace quotes so cvar is set correctly

	logln(string("[RelaySay ") + Plugin_info.name + "]: " + message + "\n");

	g_engfuncs.pfnCVarSetString("relay_say_msg", message.c_str());
	g_engfuncs.pfnServerCommand(UTIL_VarArgs("as_command .relay_say %s\n", Plugin_info.name));
	g_engfuncs.pfnServerExecute();
}

bool fileExists(std::string path) {
	if (FILE* file = fopen(path.c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	return false;
}

// Normalizes any number to an arbitrary range 
// by assuming the range wraps around when going below min or above max
// https://stackoverflow.com/questions/1628386/normalise-orientation-between-0-and-360
float normalizeRangef(const float value, const float start, const float end)
{
	const float width = end - start;
	const float offsetValue = value - start;   // value relative to 0

	return (offsetValue - (floor(offsetValue / width) * width)) + start;
	// + start to reset back to start of original range
}

void kickPlayer(edict_t* ent, const char* reason) {
	if (!ent || (ent->v.flags & FL_CLIENT) == 0) {
		return;
	}
	int userid = g_engfuncs.pfnGetPlayerUserId(ent);
	g_engfuncs.pfnServerCommand(UTIL_VarArgs("kick #%d %s\n", userid, reason));
	g_engfuncs.pfnServerExecute();
}

uint64_t steamid_to_steamid64(const string& steamid) {
	if (steamid.size() <= 10) {
		return 0;
	}

	uint64_t X = atoi(steamid.substr(8, 1).c_str());
	uint64_t Y = atoi(steamid.substr(10).c_str());

	uint64_t steam64id = 76561197960265728;
	steam64id += Y * 2;
	if (X == 1) {
		steam64id += 1;
	}

	return steam64id;
}

string steamid64_to_steamid(uint64_t steam64) {
	steam64 -= 76561197960265728;

	if (steam64 & 1) {
		return "STEAM_0:1:" + to_string((steam64 - 1) / 2);
	}
	
	return "STEAM_0:0:" + to_string(steam64 / 2);
}

uint64_t getFileModifiedTime(std::string path) {
	struct stat result;
	if (stat(path.c_str(), &result) == 0) {
		return result.st_mtime;
	}

	return 0;
}

void winPath(string& path) {
	for (int i = 0, size = path.size(); i < size; i++)
	{
		if (path[i] == '/')
			path[i] = '\\';
	}
}

vector<string> getDirFiles(string path, string extension, string startswith, bool onlyOne)
{
	vector<string> results;

#if defined(WIN32) || defined(_WIN32)
	path = path + startswith + "*." + extension;
	winPath(path);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	//println("Target file is " + path);
	hFind = FindFirstFile(path.c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		//println("FindFirstFile failed " + str((int)GetLastError()) + " " + path);
		return results;
	}
	else
	{
		results.push_back(FindFileData.cFileName);

		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			results.push_back(FindFileData.cFileName);
			if (onlyOne)
				break;
		}

		FindClose(hFind);
	}
#else
	extension = toLowerCase(extension);
	startswith = toLowerCase(startswith);
	startswith.erase(std::remove(startswith.begin(), startswith.end(), '*'), startswith.end());
	DIR* dir = opendir(path.c_str());

	if (!dir)
		return results;

	while (true)
	{
		dirent* entry = readdir(dir);

		if (!entry)
			break;

		if (entry->d_type == DT_DIR)
			continue;

		string name = string(entry->d_name);
		string lowerName = toLowerCase(name);

		if (extension.size() > name.size() || startswith.size() > name.size())
			continue;

		if (extension == "*" || std::equal(extension.rbegin(), extension.rend(), lowerName.rbegin()))
		{
			if (startswith.size() == 0 || std::equal(startswith.begin(), startswith.end(), lowerName.begin()))
			{
				results.push_back(name);
				if (onlyOne)
					break;
			}
		}
	}

	closedir(dir);
#endif

	return results;
}