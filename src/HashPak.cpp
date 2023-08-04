#include "HashPak.h"
#include <fstream>
#include "misc_utils.h"
#include <sstream>
#include <iomanip>
#include "mmlib.h"

#undef read
#undef write
#undef close

using namespace std;

// File layout:
//   hpk_header_t
//   lumps[]
//   lump_count (4 bytes)
//   hpk_lumpinfo_t[]

// Lump layout:
//   wad_header_t
//   mip_info
//   mip[0] data
//   mip[1] data
//   mip[2] data
//   mip[3] data
//   palette size (2 bytes)
//   palette data (3 bytes per index)
//   wad_lumpinfo_t (4-byte aligned, so there may be 2 empty bytes after the palette)

HashPak::HashPak(string fname) {
	this->fname = fname;
}

HashPak::~HashPak() {
    for (int i = 0; i < lumps.size(); i++) {
        delete[] lumps[i].data;
    }
}

void HashPak::readLump(unsigned char* wad_buffer)
{
    wad_header_t* wad_header = (wad_header_t*)wad_buffer;

    if (strncmp(wad_header->identification, "WAD3", 4))
        return;

    int num_wad_lumps = wad_header->numlumps;
    int infotableofs = wad_header->infotableofs;

    for (int index = 0; index < num_wad_lumps; index++)
    {
        int offset = infotableofs + (index * sizeof(wad_lumpinfo_t));
        wad_lumpinfo_t* wad_lump = (wad_lumpinfo_t*)(wad_buffer + offset);

        mip_info_t* mip_info = (mip_info_t*)(wad_buffer + wad_lump->filepos);
        byte* first_mip = (unsigned char*)mip_info + mip_info->offsets[0];

        int mip1_size = mip_info->width * mip_info->height;
        int mip2_size = (mip_info->width * mip_info->height) / 4;
        int mip3_size = (mip_info->width * mip_info->height) / 16;
        int mip4_size = (mip_info->width * mip_info->height) / 64;
        int totalMipSz = mip1_size + mip2_size + mip3_size + mip4_size;

        short palette_size = *(short*)((byte*)mip_info + sizeof(mip_info_t) + totalMipSz);
        byte* mip_palette = (byte*)mip_info + sizeof(mip_info_t) + totalMipSz + 2;

        //println("%s %dx%d (%d palette)", mip_info->name, mip_info->width, mip_info->height, palette_size);

        // check if monochrome or color image...
        int color = 0;

        for (int i = 0; i < 255; i++)
        {
            if ((mip_palette[i * 3] != mip_palette[i * 3 + 1]) ||
                (mip_palette[i * 3 + 1] != mip_palette[i * 3 + 2]))
            {
                color = 1;  // it's not a monochrome image
                break;
            }
        }

        COLOR3 palette[256];

        if (color) {
            for (int i = 0; i < 255; i++) {
                palette[i].r = mip_palette[i * 3];
                palette[i].g = mip_palette[i * 3 + 1];
                palette[i].b = mip_palette[i * 3 + 2];
            }
        } else {
            int color_red = mip_palette[255 * 3];
            int color_green = mip_palette[255 * 3 + 1];
            int color_blue = mip_palette[255 * 3 + 2];

            for (int i = 0; i < 255; i++) {
                palette[i].r = mip_palette[i * 3] * color_red / 256;
                palette[i].g = mip_palette[i * 3 + 1] * color_green / 256;
                palette[i].b = mip_palette[i * 3 + 2] * color_blue / 256;
            }

            palette[255].r = 255 * color_red / 256;
            palette[255].g = 255 * color_green / 256;
            palette[255].b = 255 * color_blue / 256;
        }
    }
}

string md5Hex(byte md5sum[16]) {
    std::ostringstream oss;
    for (int i = 0; i < 16; i++)
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(md5sum[i]);
    return oss.str();
}

bool HashPak::readData() {
    for (int i = 0; i < lumps.size(); i++) {
        delete[] lumps[i].data;
    }
    lumps.clear();

    ifstream fin(fname, ifstream::in | ios::binary);
    if (!fin.good()) {
        println("Failed to open: %s", fname.c_str());
        return false;
    }

    fin.read((char*)&hpk_header, sizeof(hpk_header_t));

    if (!fin) {
        println("Failed to read HashPak header");
        return false;
    }

    int num_lumps = 0;
    fin.seekg(hpk_header.infotableofs);
    fin.read((char*)&num_lumps, sizeof(int));

    if (!fin) {
        println("Failed to read HashPak lump count\n");
        return false;
    }

    hpk_lumpinfo_t* lump_infos = new hpk_lumpinfo_t[num_lumps];
    fin.read((char*)lump_infos, sizeof(hpk_lumpinfo_t)*num_lumps);

    if (!fin) {
        println("Failed to read HashPak lumps\n");
        delete[] lump_infos;
        return false;
    }

    for (int i = 0; i < num_lumps; i++)
    {
        hpk_lumpinfo_t& info = lump_infos[i];
        fin.seekg(info.filepos);

        byte* lumpData = new byte[info.hpk_lump_size];
        fin.read((char*)lumpData, info.hpk_lump_size);

        if (!fin || !lumpData || info.hpk_lump_size < 4) {
            println("Failed to read HashPak lump %d", i);
            delete[] lumpData;
            continue;
        }

        wad_header_t* wad_header = (wad_header_t*)lumpData;
        if (strncmp(wad_header->identification, "WAD3", 4)) {
            println("Skipping lump %d due to bad header: \"%s\"", i, string(wad_header->identification, 4).c_str());
            delete[] lumpData;
            continue;
        }

        readLump(lumpData);

        HpkLump lump;
        lump.header = lump_infos[i];
        lump.data = lumpData;
        lump.md5 = md5Hex(lump_infos[i].md5_sum);

        lump.wadinfo = (wad_header_t*)lump.data;
        lump.lumpinfo = (wad_lumpinfo_t*)(lump.data + lump.wadinfo->infotableofs);
        lump.mipinfo = (mip_info_t*)(lump.data + lump.lumpinfo->filepos);

        lumps.push_back(lump);
    }

    delete[] lump_infos;
    fin.close();
}

int HashPak::addDecal(int w, int h, byte* data, byte* palette) {
    int mip1_size = w * h;
    int mip2_size = mip1_size / 4;
    int mip3_size = mip1_size / 16;
    int mip4_size = mip1_size / 64;
    int totalMipSz = mip1_size + mip2_size + mip3_size + mip4_size;

    int totalHeaderSz = sizeof(wad_header_t) + sizeof(mip_info_t) + sizeof(wad_lumpinfo_t);
    int totalPaletteSz = (256*sizeof(COLOR3)) + 2;

    int totalLumpSz = totalMipSz + totalHeaderSz + totalPaletteSz;

    byte* dat = new byte[totalLumpSz];
    
    wad_header_t* wad_header = (wad_header_t*)dat;
    wad_header->identification[0] = 'W';
    wad_header->identification[1] = 'A';
    wad_header->identification[2] = 'D';
    wad_header->identification[3] = '3';
    wad_header->numlumps = 1;
    wad_header->infotableofs = totalLumpSz - sizeof(wad_lumpinfo_t);
    
    mip_info_t* mip_info = (mip_info_t*)(dat + sizeof(wad_header_t));
    mip_info->width = w;
    mip_info->height = h;
    strncpy(mip_info->name, "{LOGO", 16);
    mip_info->offsets[0] = sizeof(mip_info_t);
    mip_info->offsets[1] = mip_info->offsets[0] + mip1_size;
    mip_info->offsets[2] = mip_info->offsets[1] + mip2_size;
    mip_info->offsets[3] = mip_info->offsets[2] + mip3_size;

    byte* mip1_data = (byte*)mip_info + mip_info->offsets[0];
    byte* mip2_data = (byte*)mip_info + mip_info->offsets[1];
    byte* mip3_data = (byte*)mip_info + mip_info->offsets[2];
    byte* mip4_data = (byte*)mip_info + mip_info->offsets[3];
    memcpy(mip1_data, data, mip1_size);
    
    // TODO: are mip maps used?
    memset(mip2_data, 0, mip2_size);
    memset(mip3_data, 0, mip3_size);
    memset(mip4_data, 0, mip4_size);

    short* palette_sz = (short*)((byte*)mip_info + sizeof(mip_info_t) + totalMipSz);
    *palette_sz = 256;

    byte* mip_palette = (byte*)mip_info + sizeof(mip_info_t) + totalMipSz + 2;
    memcpy(mip_palette, palette, 256 * sizeof(COLOR3));

    wad_lumpinfo_t* lump_info = (wad_lumpinfo_t*)(dat + totalLumpSz - sizeof(wad_lumpinfo_t));
    lump_info->compression = 0;
    lump_info->size = totalMipSz + totalPaletteSz + sizeof(mip_info_t);
    lump_info->filepos = sizeof(wad_header_t);
    strncpy(lump_info->name, "{LOGO", 16);
    lump_info->pad1 = 0;
    lump_info->pad2 = 0;
    lump_info->disksize = lump_info->size;
    lump_info->type = 67; // ???

    HpkLump lump;
    lump.data = dat;
    lump.header.hpk_lump_size = totalLumpSz;
    lump.header.hpk_section_size = totalLumpSz;
    lump.header.checksum_type = 4; // or 4?
    strncpy(lump.header.filename, "tempdecal.wad", 64);

    byte md5[16];
    MD5Context_t md5Context;
    memset(&md5Context, 0, sizeof(MD5Context_t));
    MD5Init(&md5Context);
    MD5Update(&md5Context, dat, totalLumpSz);
    MD5Final(md5, &md5Context);
    memcpy(lump.header.md5_sum, md5, 16);
    lump.md5 = md5Hex(lump.header.md5_sum);

    // uhhh
    lump.header.timestamp[0] = 0;
    lump.header.timestamp[1] = 0;
    lump.header.unknown1 = 0;
    lump.header.unknown2 = 0;

    for (int i = 0; i < lumps.size(); i++) {
        if (lumps[i].md5 == lump.md5) {
            delete[] dat;
            println("Duplicate addDecal skipped (MD5 exists)");
            return i;
        }
    }

    lump.wadinfo = (wad_header_t*)lump.data;
    lump.lumpinfo = (wad_lumpinfo_t*)(lump.data + lump.wadinfo->infotableofs);
    lump.mipinfo = (mip_info_t*)(lump.data + lump.lumpinfo->filepos);

    lumps.push_back(lump);

    return lumps.size() - 1;
}

// load an 8-bit paletted BMP file
bool loadBMP(const string& filename, vector<uint8_t>& imageBytes, vector<uint8_t>& paletteData, int& width, int& height) {
    ifstream file(filename, std::ios::binary);
    if (!file) {
        println("Error: Unable to open file: %s", filename.c_str());
        return false;
    }

    BMPHeader header;
    file.read((char*)&header, sizeof(BMPHeader));

    // Basic BMP file format validation
    if (header.signature[0] != 'B' || header.signature[1] != 'M') {
        println("Error: Invalid BMP file format.");
        return false;
    }
    if (header.bitsPerPixel != 8) {
        println("Error: Only 8-bit BMP files supported.");
        return false;
    }
    if (header.numColorsUsed > 256) {
        println("Error: Too many colors in the palette.");
        return false;
    }

    // Read palette data
    const size_t paletteSize = header.numColorsUsed * sizeof(uint32_t);
    vector<uint8_t> tempPalData;
    tempPalData.resize(paletteSize);
    file.read(reinterpret_cast<char*>(tempPalData.data()), paletteSize);

    paletteData.resize(header.numColorsUsed*3);
    for (int i = 0; i < header.numColorsUsed; i++) {
        paletteData[i * 3 + 0] = tempPalData[i * 4 + 2];
        paletteData[i * 3 + 1] = tempPalData[i * 4 + 1];
        paletteData[i * 3 + 2] = tempPalData[i * 4 + 0];
    }

    // Read image data
    const size_t imageSize = header.width * header.height;
    imageBytes.resize(imageSize);
    file.read(reinterpret_cast<char*>(imageBytes.data()), imageSize);

    file.close();

    width = header.width;
    height = header.height;

    // vertically flip image
    int rowSize = width;
    int numRows = height / 2;

    for (int row = 0; row < numRows; ++row) {
        int oppositeRow = height - row - 1;

        // Swap the entire rows
        for (int col = 0; col < width; ++col) {
            unsigned char temp = imageBytes[row * rowSize + col];
            imageBytes[row * rowSize + col] = imageBytes[oppositeRow * rowSize + col];
            imageBytes[oppositeRow * rowSize + col] = temp;
        }
    }

    return true;
}

int HashPak::addDecal(string bmpFile) {
    std::vector<uint8_t> imageBytes;
    std::vector<uint8_t> paletteData;
    int width, height;

    if (loadBMP(bmpFile, imageBytes, paletteData, width, height)) {
        return addDecal(width, height, &imageBytes[0], &paletteData[0]);
    }
    return -1;
}

void HashPak::sendDecal(edict_t* plr, int plrReplaceIdx, int decalIdx) {
    if (decalIdx < 0 || decalIdx >= lumps.size()) {
        println("Bad lump idx in sendDecal");
        return;
    }

    HpkLump& lump = lumps[decalIdx];

    MESSAGE_BEGIN(MSG_ONE_UNRELIABLE, SVC_CUSTOMIZATION, NULL, plr);
    WRITE_BYTE(plrReplaceIdx - 1); // player idx whos spray is being replaced
    WRITE_BYTE(t_decal); // resource type
    WRITE_STRING(("!MD5" + lump.md5).c_str()); // resource name
    WRITE_SHORT(decalIdx); // index (???)
    WRITE_LONG(lump.header.hpk_lump_size); // download size
    WRITE_BYTE(4); // flags
    for (int i = 0; i < 16; i++) {
        WRITE_BYTE(lump.header.md5_sum[i]);
    }
    MESSAGE_END();
}

void HashPak::listDecals() {
    for (int i = 0; i < lumps.size(); i++)
    {
        HpkLump& lump = lumps[i];

        std::ostringstream oss;
        for (int i = 0; i < 16; i++)
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(lump.header.md5_sum[i]);

        int extra = lump.header.unknown1 + lump.header.unknown2;

        println("ID: %d, Names: %s - %s - %s, Sz: %3dx%-3d (%d bytes), Type: %d, Extra: %d, MD5: %s",
            i, lump.header.filename, lump.lumpinfo->name, lump.mipinfo->name,
            lump.mipinfo->width, lump.mipinfo->height, lump.header.hpk_lump_size,
            lump.lumpinfo->type, extra, oss.str().c_str());
    }
}

void HashPak::writeFile(string outName) {
    ofstream fout(outName, ios::out | ios::binary | ios::trunc);

    int totalLumpsSz = 0;
    for (int i = 0; i < lumps.size(); i++) {
        totalLumpsSz += lumps[i].header.hpk_lump_size;
    }
    hpk_header.infotableofs = sizeof(hpk_header_t) + totalLumpsSz;

    fout.write((char*)&hpk_header, sizeof(hpk_header_t));

    for (int i = 0; i < lumps.size(); i++) {
        lumps[i].header.filepos = fout.tellp();
        fout.write((char*)lumps[i].data, lumps[i].header.hpk_lump_size);
    }

    int lump_count = lumps.size();
    fout.write((char*)&lump_count, sizeof(int));

    for (int i = 0; i < lumps.size(); i++) {
        fout.write((char*)&lumps[i].header, sizeof(hpk_lumpinfo_t));
    }

    fout.close();
}
