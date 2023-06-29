// This plugin gives metamod access to private Sven APIs and hooks
// communication is done using server commands

CConCommand precacheSoundCmd( "PrecacheSound", "Precache a sound from metamod", @precacheSound );
CConCommand precacheModelCmd( "PrecacheModel", "Precache a model from metamod", @precacheModel );
CConCommand registerHookCmd( "RegisterHook", "relay an angelscript hook to metamod using the given command name", @registerHook );
CConCommand CustomKeyReadCmd( "CustomKeyRead", "reads a custom keyvalue into a pev variable", @CustomKeyRead );
CConCommand EntTakeDamageCmd( "EntTakeDamage", "apply damage to an entity", @EntTakeDamage );
CConCommand EntKillCmd( "EntKill", "apply damage to an entity", @EntKill );
CConCommand EntReviveCmd( "EntRevive", "apply damage to an entity", @EntRevive );
CConCommand EntUseCmd( "Use", "use an entity", @EntUse );

void print(string text) { g_Game.AlertMessage( at_console, text); }
void println(string text) { print(text + "\n"); }

array<string> g_takedamage_hooks;
array<string> g_survivalmode_hooks;

void PluginInit() {
	g_Module.ScriptInfo.SetAuthor( "w00tguy" );
	g_Module.ScriptInfo.SetContactInfo( "https://github.com/wootguy" );
	
	g_Hooks.RegisterHook( Hooks::Player::PlayerTakeDamage, @PlayerTakeDamage );
	
	g_Scheduler.SetInterval("perf_loop", 0.1f, -1);
	g_Scheduler.SetInterval("survival_update", 1.0f, -1);
	g_perfPlayers.resize(32);
}

void MapInit() {
	g_totalCalls = 0;
	g_lastCalls = 0;
	g_perfPlayers.resize(0);
	g_perfPlayers.resize(32);
}

bool lastSurvivalEnabled = false;
bool lastSurvivalActive = false;

// sync survival mode state with metamod
void survival_update() {
	if (g_SurvivalMode.IsEnabled() != lastSurvivalEnabled || g_SurvivalMode.IsActive() != lastSurvivalActive) {
		string args = (g_SurvivalMode.IsEnabled() ? " 1 " : " 0 ") + (g_SurvivalMode.IsActive() ? "1" : "0");
		for (uint i = 0; i < g_survivalmode_hooks.size(); i++) {
			g_EngineFuncs.ServerCommand(g_survivalmode_hooks[i] + args + "\n");
			g_totalCalls++;
		}
		g_EngineFuncs.ServerExecute();
	}
	
	lastSurvivalEnabled = g_SurvivalMode.IsEnabled();
	lastSurvivalActive = g_SurvivalMode.IsActive();
}

HookReturnCode PlayerTakeDamage(DamageInfo@ info) {	
	if (g_takedamage_hooks.size() > 0) {
		int victim = info.pVictim !is null ? info.pVictim.entindex() : 0;
		int inflcitor = info.pInflictor !is null ? info.pInflictor.entindex() : 0;
		int attacker = info.pAttacker !is null ? info.pAttacker.entindex() : 0;
		float damage = info.flDamage;
		int damageType = info.bitsDamageType;
		string args = " " + victim + " " + inflcitor + " " + attacker + " " + damage + " " + damageType;
	
		for (uint i = 0; i < g_takedamage_hooks.size(); i++) {
			g_EngineFuncs.ServerCommand(g_takedamage_hooks[i] + args + "\n");
			g_totalCalls++;
		}
		g_EngineFuncs.ServerExecute();
	}
	
	return HOOK_CONTINUE;
}

enum custom_key_types {
	KEY_TYPE_INTEGER,
	KEY_TYPE_FLOAT,
	KEY_TYPE_STRING,
	KEY_TYPE_VECTOR,
}

void EntRevive(const CCommand@ args) {
	g_totalCalls++;
	CBaseMonster@ ent = cast<CBaseMonster@>(g_EntityFuncs.Instance(atoi(args[1])));
	
	ent.Revive();
}

void EntKill(const CCommand@ args) {
	g_totalCalls++;
	CBaseEntity@ ent = g_EntityFuncs.Instance(atoi(args[1]));
	CBaseEntity@ attacker = g_EntityFuncs.Instance(atoi(args[2]));
	USE_TYPE gibMode = USE_TYPE(atoi(args[3]));
	
	ent.Killed(attacker.pev, gibMode);
}

void EntUse(const CCommand@ args) {
	g_totalCalls++;
	CBaseEntity@ ent = g_EntityFuncs.Instance(atoi(args[1]));
	CBaseEntity@ activator = g_EntityFuncs.Instance(atoi(args[2]));
	CBaseEntity@ caller = g_EntityFuncs.Instance(atoi(args[3]));
	USE_TYPE useType = USE_TYPE(atoi(args[4]));
	
	ent.Use(activator, caller, useType);
}

void EntTakeDamage(const CCommand@ args) {
	g_totalCalls++;
	CBaseEntity@ ent = g_EntityFuncs.Instance(atoi(args[1]));
	CBaseEntity@ inflictor = g_EntityFuncs.Instance(atoi(args[2]));
	CBaseEntity@ attacker = g_EntityFuncs.Instance(atoi(args[3]));
	float damage = atof(args[4]);
	int damageType = atoi(args[5]);
	
	ent.TakeDamage(inflictor.pev, attacker.pev, damage, damageType);
}

void CustomKeyRead(const CCommand@ args) {
	g_totalCalls++;
	CBaseEntity@ ent = g_EntityFuncs.Instance(atoi(args[1]));
	
	if (ent is null) {
		println("[MetaHelper] Attempt to read custom keyvalue from invalid ent " + args[1]);
		return;
	}

	CustomKeyvalues@ customKeys = ent.GetCustomKeyvalues();
	CustomKeyvalue key = customKeys.GetKeyvalue(args[2]);
	if (key.Exists()) {
		int argType = atoi(args[3]);
		
		switch(argType) {
			case KEY_TYPE_INTEGER:
			//println("[MetaHelper] Read " + args[2] + " to iuser4");
			ent.pev.iuser4 = key.GetInteger();
			break;
			case KEY_TYPE_FLOAT:
			//println("[MetaHelper] Read " + args[2] + " to fuser4");
			ent.pev.fuser4 = key.GetFloat();
			break;
			case KEY_TYPE_STRING:
			//println("[MetaHelper] Read " + args[2] + " to noise3");
			ent.pev.noise3 = key.GetString();
			break;
			case KEY_TYPE_VECTOR:
			//println("[MetaHelper] Read " + args[2] + " to vuser4");
			ent.pev.vuser4 = key.GetVector();
			break;
			default:
			println("[MetaHelper] Invalid custom keyvalue type " + argType);
			break;
		}
	} else {
		println("[MetaHelper] Invalid custom keyvalue '" + args[2] + "'");
	}
}

void precacheModel(const CCommand@ args) {
	g_totalCalls++;
	g_Game.PrecacheModel(args[1]);
}

void precacheSound(const CCommand@ args) {
	g_totalCalls++;
	g_SoundSystem.PrecacheSound(args[1]);
	g_Game.PrecacheGeneric("sound/" + args[1]);
}

void registerHook(const CCommand@ args) {
	g_totalCalls++;
	if (args[1] == "TakeDamage") {
		if (g_takedamage_hooks.find(args[2]) == -1) {
			g_takedamage_hooks.insertLast(args[2]);
			println("[MetaHelper] Register " + args[1] + " hook: " + args[2]);
		}
	} else if (args[1] == "SurvivalMode") {
		if (g_survivalmode_hooks.find(args[2]) == -1) {
			g_survivalmode_hooks.insertLast(args[2]);
			println("[MetaHelper] Register " + args[1] + " hook: " + args[2]);
		}
	} else {
		println("[MetaHelper] Unknown hook type: '" + args[1] + "'");
	}
}


//
// Performance troubleshooting
//

int g_totalCalls = 0;
int g_lastCalls = 0;
array<bool> g_perfPlayers;
array<float> fpsHistory;

CClientCommand _metahelpperf("mhperf", "show metahelper performance stats", @perf);

void perf(const CCommand@ pArgs) {
    CBasePlayer@ pPlayer = g_ConCommandSystem.GetCurrentPlayer();
	g_perfPlayers[pPlayer.entindex()-1] = !g_perfPlayers[pPlayer.entindex()-1];
}

void HudMessageUnreliable(CBasePlayer@ plr, const HUDTextParams& in txtPrms, const string& in text) {
  if (plr is null)
    return;

  NetworkMessage m(MSG_ONE_UNRELIABLE, NetworkMessages::SVC_TEMPENTITY, plr.edict());
    m.WriteByte(TE_TEXTMESSAGE);
    m.WriteByte(txtPrms.channel & 0xFF);

    m.WriteShort(FixedSigned16(txtPrms.x, 1<<13));
    m.WriteShort(FixedSigned16(txtPrms.y, 1<<13));
    m.WriteByte(txtPrms.effect);

    m.WriteByte(txtPrms.r1);
    m.WriteByte(txtPrms.g1);
    m.WriteByte(txtPrms.b1);
    m.WriteByte(txtPrms.a1);

    m.WriteByte(txtPrms.r2);
    m.WriteByte(txtPrms.g2);
    m.WriteByte(txtPrms.b2);
    m.WriteByte(txtPrms.a2);

    m.WriteShort(FixedUnsigned16(txtPrms.fadeinTime, 1<<8));
    m.WriteShort(FixedUnsigned16(txtPrms.fadeoutTime, 1<<8));
    m.WriteShort(FixedUnsigned16(txtPrms.holdTime, 1<<8));

    if (txtPrms.effect == 2) 
      m.WriteShort(FixedUnsigned16(txtPrms.fxTime, 1<<8));

    m.WriteString(text);
  m.End();
}

uint16 FixedUnsigned16( float value, float scale ) {
   float scaled = value * scale;
   int output = int( scaled );
   
   if ( output < 0 )
      output = 0;
   if ( output > 0xFFFF )
      output = 0xFFFF;

   return uint16( output );
}

int16 FixedSigned16( float value, float scale ) {
   float scaled = value * scale;
   int output = int( scaled );

   if ( output > 32767 )
      output = 32767;
   if ( output < -32768 )
      output = -32768;

   return int16( output );
}

void perf_loop() {
	int gain = g_totalCalls - g_lastCalls;
	int fps = int(gain*10.0f + 0.5f);
	g_lastCalls = g_totalCalls;

	HUDTextParams txtPrms;

	txtPrms.r1 = 255;
	txtPrms.g1 = 255;
	txtPrms.b1 = 255;
	txtPrms.a1 = 1;

	txtPrms.x = -1.0f;
	txtPrms.y = 0.9f;
	txtPrms.effect = 0;
	txtPrms.fadeinTime = 0.0f;
	txtPrms.fadeoutTime = 0.0f;
	txtPrms.holdTime = 1.0f;
	txtPrms.channel = 2;
	
	fpsHistory.insertLast(fps);
	
	if (fpsHistory.size() > 5) {
		fpsHistory.removeAt(0);
	}
	
	float fpsAvg = 0;
	for (uint i = 0; i < fpsHistory.size(); i++) {
		fpsAvg += fpsHistory[i];
	}
	fpsAvg = fpsAvg / float(fpsHistory.size());
	
	fps = int(fpsAvg + 0.5f);

	for (int i = 0; i < 32; i++) {
		if (g_perfPlayers[i]) {
			CBasePlayer@ plr = g_PlayerFuncs.FindPlayerByIndex(i+1);
			HudMessageUnreliable(plr, txtPrms, "CPS: " + string(fps) + "    TOTAL: " + g_totalCalls + "\n");
		}
	}
}