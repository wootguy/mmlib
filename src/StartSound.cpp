#include "StartSound.h"
#include "meta_utils.h"
#include "misc_utils.h"
#include "Scheduler.h"

using namespace std;

const string g_soundcache_folder = "svencoop/maps/soundcache/";
std::map<std::string, int> g_SoundCache;
std::vector<std::string> g_SoundCacheFiles;
std::map<std::string, int> g_SentenceCache;
std::vector<std::string> g_SentenceCacheNames;

void StartSoundMsg::send(int msg_dest, edict_t* target) {
#ifndef HLCOOP_BUILD
	MESSAGE_BEGIN(msg_dest, MSG_StartSound, NULL, target);
	WRITE_SHORT(flags);

	if (flags & SND_ENT) {
		WRITE_SHORT(entindex);
	}
	if (flags & SND_VOLUME) {
		uint8_t vol = clamp(int(volume * 255), 0, 255);
		WRITE_BYTE(vol);
	}
	if (flags & SND_PITCH) {
		WRITE_BYTE(pitch);
	}
	if (flags & SND_ATTENUATION) {
		uint8_t attn = clamp(int(attenuation * 64), 0, 255);
		WRITE_BYTE(attn);
	}
	if (flags & SND_ORIGIN) {
		WRITE_COORD(origin.x);
		WRITE_COORD(origin.y);
		WRITE_COORD(origin.z);
	}
	if (flags & SND_OFFSET) {
		uint8_t* fbytes = (uint8_t*)&offset;
		WRITE_BYTE(fbytes[0]);
		WRITE_BYTE(fbytes[1]);
		WRITE_BYTE(fbytes[2]);
		WRITE_BYTE(fbytes[3]);
	}

	WRITE_BYTE(channel);
	WRITE_SHORT(soundIdx);

	MESSAGE_END();
#endif
}

void PlaySound(edict_t* entity, int channel, const std::string& sample, float volume, float attenuation, 
	int flags, int pitch, int target_ent_unreliable, bool setOrigin, const Vector& vecOrigin) {
	edict_t* target = target_ent_unreliable ? INDEXENT(target_ent_unreliable) : NULL;
	StartSoundMsg msg;

	if (sample.length() == 0) {
		return;
	}

	msg.channel = clamp(channel, 0, MAX_SOUND_CHANNELS);
	msg.sample = sample;
	msg.volume = volume;
	msg.attenuation = attenuation;
	msg.flags = flags;
	msg.pitch = pitch;
	msg.origin = vecOrigin;

	if (sample[0] == '!') {
		msg.flags |= SND_SENTENCE;
		msg.soundIdx = g_SentenceCache[toLowerCase(sample.substr(1))];
	}
	else {
		msg.soundIdx = g_SoundCache[toLowerCase(sample)];
	}

	if (entity) {
		msg.entindex = ENTINDEX(entity);
		msg.flags |= SND_ENT;
	}
	if (setOrigin) {
		// sven always writes an origin but that seems wasteful when a tracked entity is given
		msg.flags |= SND_ORIGIN;
	}
	if (pitch != PITCH_NORM) {
		msg.flags |= SND_PITCH;
	}
	if (volume != VOL_NORM) {
		msg.flags |= SND_VOLUME;
	}
	if (attenuation != ATTN_NORM) {
		msg.flags |= SND_ATTENUATION;
	}

	// set an origin on the sound if the emitting entity is not networked to clients.
	// this has the side effect of allowing overlapping sounds on the same channel
	// and the sound won't follow the entity's origin as it plays.
	// This seems to be what the sven version of PlaySound does (tested with gibme and observer mode).
	bool fakeAttachment = entity && entity->v.effects & EF_NODRAW;

	if (fakeAttachment && !setOrigin) {
		msg.flags &= ~SND_ENT;
		msg.flags |= SND_ORIGIN;
		msg.origin = entity->v.origin;
	}
	
	if (target) {
		msg.send(MSG_ONE_UNRELIABLE, target);
	}
	else {
		msg.send(MSG_ALL);
	}
}

enum PARSE_MODE {
	PARSE_NONE,
	PARSE_SOUNDS,
	PARSE_SENTENCES
};

void loadSoundCacheFile(int attempts) {
	g_SoundCache.clear();
	g_SoundCacheFiles.clear();
	g_SentenceCache.clear();
	g_SentenceCacheNames.clear();

	string soundcache_path = g_soundcache_folder + STRING(gpGlobals->mapname) + ".txt";
	FILE* file = fopen(soundcache_path.c_str(), "r");
	int soundIdx = 0;
	int sentenceIdx = 0;

	if (!file) {
		if (attempts > 0) {
			println("[SoundCache] Failed to open soundcache file (attempts left %d)", attempts);
			g_Scheduler.SetTimeout(loadSoundCacheFile, 5, attempts - 1);
		}
		else {
			logln(("[SoundCache] failed to open soundcache file: " + soundcache_path).c_str());
		}
		return;
	}

	string line;
	int parsemode = PARSE_NONE;
	while (cgetline(file, line)) {
		if (line.empty()) {
			continue;
		}

		if (line.find("SOUNDLIST {") == 0) {
			parsemode = PARSE_SOUNDS;
			continue;
		}
		if (line.find("SENTENCELIST {") == 0) {
			parsemode = PARSE_SENTENCES;
			continue;
		}
		if (line.find("}") == 0) {
			parsemode = PARSE_NONE;
		}

		string lowerLine = toLowerCase(line);

		if (parsemode == PARSE_SOUNDS) {
			g_SoundCache[lowerLine] = soundIdx;
			g_SoundCacheFiles.push_back(lowerLine);
			soundIdx++;
		}
		else if (parsemode == PARSE_SENTENCES) {
			string name = lowerLine.substr(0, lowerLine.find_first_of(" "));
			g_SentenceCache[name] = sentenceIdx;
			g_SentenceCacheNames.push_back(name);
			sentenceIdx++;
		}
	}

	fclose(file);

	println("[SoundCache] Parsed %d sounds", g_SoundCache.size());
}