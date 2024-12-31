#ifndef MYBMPMANAGER_H
#define MYBMPMANAGER_H

#include <bitset>
#include <filesystem>
#include <GUI_BMPfile.h>
#include <vector>
#include <iostream>
#include "myBmpManager.h"
#include "myGUI.h"

using namespace std;

// color_table = bytearray([
//    0, 0, 0, 0,      # Black (B, G, R, 0)
//    255, 255, 255, 0  # White (B, G, R, 0)
// ]) (remember it's little endian here - but it flips)
constexpr unsigned long long COLOUR_TABLE = 0x00FFFFFF00000000;

struct BmpImage {
    BMP_FILE_HEADER bmpFileHeader;
    BMP_INFO_HEADER bmpInfoHeader;
    vector<char> data;
    unsigned long long colourTable = COLOUR_TABLE;
};


std::unique_ptr<BmpImage> ReadBMP(filesystem::path path);

int SaveBMP(const filesystem::path &location, BmpImage &bmpImage);

BmpImage CreateBMP(const PIXEL_ARRAY &pixels);

inline void PrintBMP(const unique_ptr<BmpImage> &bmpImage) {
    BMP_FILE_HEADER bmpFileHeader = bmpImage->bmpFileHeader;
    BMP_INFO_HEADER bmpInfoHeader = bmpImage->bmpInfoHeader;

    cout << "bType " << bmpFileHeader.bType << endl;
    cout << "bSize " << bmpFileHeader.bSize << endl;
    cout << "bReserved1 " << bmpFileHeader.bReserved1 << endl;
    cout << "bReserved2 " << bmpFileHeader.bReserved2 << endl;
    cout << "bOffset " << bmpFileHeader.bOffset << endl;

    cout << "biInfoSize: " << bmpInfoHeader.biInfoSize << endl;
    cout << "biWidth: " << bmpInfoHeader.biWidth << endl;
    cout << "biHeight: " << bmpInfoHeader.biHeight << endl;
    cout << "biPlanes: " << bmpInfoHeader.biPlanes << endl;
    cout << "biBitCount: " << bmpInfoHeader.biBitCount << endl;
    cout << "biCompression: " << bmpInfoHeader.biCompression << endl;
    cout << "bimpImageSize: " << bmpInfoHeader.bimpImageSize << endl;
    cout << "biXPelsPerMeter: " << bmpInfoHeader.biXPelsPerMeter << endl;
    cout << "biYPelsPerMeter: " << bmpInfoHeader.biYPelsPerMeter << endl;
    cout << "biClrUsed: " << bmpInfoHeader.biClrUsed << endl;
    cout << "biClrImportant: " << bmpInfoHeader.biClrImportant << endl;

    for (const char ch: bmpImage->data) {
        cout << std::hex << ch;
    }
    cout << endl;
}


#endif //MYBMPMANAGER_H