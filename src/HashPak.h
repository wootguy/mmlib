#pragma once
#include <string>
#include <vector>
#include <stdint.h>

#define CMP_NONE  0
#define CMP_LZSS  1

#define TYP_NONE  0
#define TYP_LABEL 1
#define TYP_LUMPY 64    // 64 + grab command number

typedef struct
{
	char identification[4];   // should be HPAK
	int  num_hpk_tables;      // number of lump tables (???)
	int  infotableofs;        // absolute offset to HashPak lump table
} hpk_header_t;

typedef struct
{
	char filename[64];  // name of cached file
	int  unknown1;
	int  unknown2;
	int  hpk_section_size;  // size of the HashPak section for this lump (???)
	unsigned char checksum_type;  // type of checksum??? (always 0x06 ???)
	unsigned char md5_sum[16];    // MD5 checksum
	unsigned char unused[3];      // don't know what this is ???
	char unused1[32];        // don't know what this is (???)
	int  timestamp[2];      // time_t timestamp (???)
	int  filepos;           // file offset of HashPak lump
	int  hpk_lump_size;     // size of HashPak lump (???)
} hpk_lumpinfo_t;

typedef struct
{
	char  identification[4];   // should be WAD3
	int   numlumps;
	int   infotableofs;
} wad_header_t;

typedef struct
{
	int   filepos;          // file offset of mip
	int   disksize;         // mip size
	int   size;             // uncompressed
	char  type;             // 0x43 = WAD3 mip (Half-Life)
	char  compression;      // not used?
	char  pad1, pad2;       // not used?
	char  name[16];         // must be null terminated
} wad_lumpinfo_t;

typedef struct
{
	char name[16];
	unsigned int width, height;
	unsigned int offsets[4];
} mip_info_t;

struct COLOR3 {
	unsigned char r, g, b;
};

struct HpkLump {
	hpk_lumpinfo_t header;
	unsigned char* data;
	std::string md5; // md5 as a hex string

	// for convenience
	wad_header_t* wadinfo;
	wad_lumpinfo_t* lumpinfo;
	mip_info_t* mipinfo;
};

typedef struct edict_s edict_t;

#pragma pack(push, 1) // Ensure that there is no padding between struct members
struct BMPHeader {
	char signature[2];   // File signature, should be 'BM'
	uint32_t fileSize;   // Total file size
	uint16_t reserved1;  // Reserved, set to 0
	uint16_t reserved2;  // Reserved, set to 0
	uint32_t dataOffset; // Offset to the pixel data
	uint32_t headerSize; // Header size, should be 40
	int32_t width;       // Image width in pixels
	int32_t height;      // Image height in pixels
	uint16_t planes;     // Number of color planes, should be 1
	uint16_t bitsPerPixel; // Number of bits per pixel, should be 8 for 8-bit paletted BMP
	uint32_t compression; // Compression method, should be 0 (uncompressed)
	uint32_t imageSize;  // Image size (including padding)
	int32_t xPixelsPerMeter; // Pixels per meter, horizontal resolution
	int32_t yPixelsPerMeter; // Pixels per meter, vertical resolution
	uint32_t numColorsUsed;  // Number of colors used in the palette (should be 256 for 8-bit BMP)
	uint32_t numImportantColors; // Number of important colors, generally ignored
};
#pragma pack(pop)

#ifndef HLCOOP_BUILD
#define SVC_CUSTOMIZATION 46
#endif

class HashPak {
public:
	std::string fname;

	hpk_header_t hpk_header;
	std::vector<HpkLump> lumps;

	HashPak(std::string fname);
	~HashPak();

	bool readData();
	void writeFile(std::string outName);

	// adds a lump to the HashPak but does not update the file.
	// MipMaps are not generated.
	// w = width of the image
	// h = height of the image
	// data = image data (indexes into the palette), w*h in size
	// palette = 256 colors, 3 bytes (RGB) per index
	int addDecal(int w, int h, unsigned char* data, unsigned char* palette);

	// add an 8-bit paletted BMP to the pak
	// returns index of lump, or -1 on failure
	int addDecal(std::string bmpFile);

	// replace a player's spray
	// BUG: client's can only learn one spray for each image size. So, if you send two 64x64 sprays
	//      then only the first one will ever be seen.
	// plr = player to send data to
	// plrReplaceIdx = player idx spray to replace
	// decalIdx = lump index in this hashpak
	void sendDecal(edict_t* plr, int plrReplaceIdx, int decalIdx);

	void listDecals();

private:
	void readLump(unsigned char* wad_buffer);

};