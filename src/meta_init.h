#pragma once

// functions to making porting from angelscript to metamod easier
#include <extdll.h>
#include <meta_api.h>

// engine hook table
extern enginefuncs_t g_engine_hooks;
extern enginefuncs_t g_engine_hooks_post;

// game dll hook table
extern DLL_FUNCTIONS g_dll_hooks;
extern DLL_FUNCTIONS g_dll_hooks_post;

extern NEW_DLL_FUNCTIONS g_newdll_hooks;

extern int g_mod_api; // will be set to the mod ID that an API was loaded for

enum MOD_APIS {
	MOD_API_NONE = 0, // no mod apis were loaded
	MOD_API_HLCOOP = 1 // g_hlcoop_funcs was initialized
};

void PluginInit();

void PluginExit();
