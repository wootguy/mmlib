#include "mmlib.h"

// Description of plugin
plugin_info_t Plugin_info = {
    META_INTERFACE_VERSION,	// ifvers
    "mmlib_example",	// name
    "1.0",	// version
    __DATE__,	// date
    "YourName",	// author
    "YourGithubOrSomething.com",	// url
    "MMLIB_EX",	// logtag, all caps please
    PT_ANYTIME,	// (when) loadable
    PT_ANYPAUSE	// (when) unloadable
};


void ClientCommand(edict_t* pEntity) {
    CommandArgs args = CommandArgs();
    args.loadArgs();

    CBasePlayer* plr = (CBasePlayer*)GET_PRIVATE(pEntity);

    if (!args.isConsoleCmd) {
        const char* playerName = STRING(plr->pev->netname);
        const char* msg = UTIL_VarArgs(
            "[mmlib_example] %s just said something. They get 10 points for that.", playerName);
        ClientPrintAll(HUD_PRINTTALK, msg);
        plr->AddPoints(10, false);
    }

	RETURN_META(MRES_IGNORED);
}

void PluginInit() {
    println("Example plugin initialized!");

    // hook descriptions are here:
    // https://metamod-p.sourceforge.net/doc/html/Index.html

    g_dll_hooks.pfnClientCommand = ClientCommand;
}



void PluginExit() {
    println("Example plugin exited!")
}