#pragma once
#include <string>
#include <extdll.h>
#include <edict.h>

struct RGBA {
	uint8_t r, g, b, a;

	RGBA() : r(0), g(0), b(0), a(255) {}
	RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
	RGBA(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b), a(255) {}
};

struct HUDSpriteParams {
	uint8_t channel;
	int flags;
	std::string spritename;
	uint8_t left;
	uint8_t top;
	uint16_t width;
	uint16_t height;
	float x;
	float y;
	RGBA color1;
	RGBA color2;
	uint8_t frame;
	uint8_t numframes;
	float framerate;
	float fadeinTime;
	float fadeoutTime;
	float holdTime;
	float fxTime;
	uint8_t effect;
};

void HudCustomSprite(edict_t* targetPlr, const HUDSpriteParams& params);