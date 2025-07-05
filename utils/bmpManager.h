#ifndef MYBMPMANAGER_H
#define MYBMPMANAGER_H

#include <GUI_BMPfile.h>

#include <filesystem>
#include <iostream>
#include <vector>

#include "BitVector.h"
#include "EPD_7in5_V2.h"

// color_table = bytearray([
//    0, 0, 0, 0,      # Black (B, G, R, 0)
//    255, 255, 255, 0  # White (B, G, R, 0)
// ]) (remember it's little endian here - but it flips)
constexpr unsigned long long COLOUR_TABLE = 0x00FFFFFF00000000;

// Each bit is a pixel.
constexpr int SCREEN_ARRAY_WIDTH = EPD_7IN5_V2_WIDTH / 8;
constexpr int SCREEN_ARRAY_HEIGHT = EPD_7IN5_V2_HEIGHT;
using PIXEL_ARRAY = std::array<std::array<UBYTE, SCREEN_ARRAY_WIDTH>, SCREEN_ARRAY_HEIGHT>;

typedef struct {
   BMP_FILE_HEADER bmpFileHeader;
   BMP_INFO_HEADER bmpInfoHeader;
   BitVector<uint8_t> data;
   unsigned long long colourTable = COLOUR_TABLE;
} BmpImage;

namespace BmpManager {
   BmpImage LoadBMP(const std::filesystem::path& path);

   int SaveBMP(const std::filesystem::path& location, BmpImage& bmpImage);

   BmpImage CreateBMP(const PIXEL_ARRAY& pixels);

   inline void PrintBMP(const std::unique_ptr<BmpImage>& bmpImage) {
      BMP_FILE_HEADER bmpFileHeader = bmpImage->bmpFileHeader;
      BMP_INFO_HEADER bmpInfoHeader = bmpImage->bmpInfoHeader;

      std::cout << "bType " << bmpFileHeader.bType << std::endl;
      std::cout << "bSize " << bmpFileHeader.bSize << std::endl;
      std::cout << "bReserved1 " << bmpFileHeader.bReserved1 << std::endl;
      std::cout << "bReserved2 " << bmpFileHeader.bReserved2 << std::endl;
      std::cout << "bOffset " << bmpFileHeader.bOffset << std::endl;

      std::cout << "biInfoSize: " << bmpInfoHeader.biInfoSize << std::endl;
      std::cout << "biWidth: " << bmpInfoHeader.biWidth << std::endl;
      std::cout << "biHeight: " << bmpInfoHeader.biHeight << std::endl;
      std::cout << "biPlanes: " << bmpInfoHeader.biPlanes << std::endl;
      std::cout << "biBitCount: " << bmpInfoHeader.biBitCount << std::endl;
      std::cout << "biCompression: " << bmpInfoHeader.biCompression << std::endl;
      std::cout << "bimpImageSize: " << bmpInfoHeader.bimpImageSize << std::endl;
      std::cout << "biXPelsPerMeter: " << bmpInfoHeader.biXPelsPerMeter << std::endl;
      std::cout << "biYPelsPerMeter: " << bmpInfoHeader.biYPelsPerMeter << std::endl;
      std::cout << "biClrUsed: " << bmpInfoHeader.biClrUsed << std::endl;
      std::cout << "biClrImportant: " << bmpInfoHeader.biClrImportant << std::endl;

      for (const unsigned char ch : bmpImage->data) {
         std::cout << std::hex << ch;
      }
      std::cout << std::endl;
   }
}
#endif  // MYBMPMANAGER_H
