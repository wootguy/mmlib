#pragma once
#include <extdll.h>
#include <string>
#include <vector>
#include <map>

#define SND_IDK 16384 // this is set by ambient_music but idk what it does
#define SND_OFFSET 32768

#define CHAN_MUSIC 7
#define MAX_SOUND_CHANNELS (CHAN_MUSIC + 1)

struct StartSoundMsg {
	std::string sample = "";
	int soundIdx = 0;
	int channel = 0;
	float volume = 1.0f;
	float attenuation = 1.0f;
	int pitch = 100;
	float offset = 0;
	int entindex = -1;
	Vector origin = Vector(0, 0, 0);
	int flags = 0;

	StartSoundMsg() {}
	void send(int msg_dest=MSG_BROADCAST, edict_t* target=NULL);
};

// call loadSoundCacheFile before playing any sounds
void PlaySound(edict_t* entity, int channel, const std::string& sample, float volume, float attenuation, int flags = 0, int pitch = PITCH_NORM, int target_ent_unreliable = 0, bool setOrigin = false, const Vector& vecOrigin = Vector(0, 0, 0));

// maps a file path to a sound index, for use with the StartSound network message
extern std::map<std::string, int> g_SoundCache;
extern std::vector<std::string> g_SoundCacheFiles; // vector index = sound index

// call in MapInit_post
void loadSoundCacheFile(int attempts = 5);
