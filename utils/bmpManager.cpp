#include <GUI_BMPfile.h>
#include <bmpManager.h>

#include <array>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
constexpr uint16_t BMP_SIGNATURE = 'M' << 8 | 'B';

BmpImage BmpManager::LoadBMP(const filesystem::path& path) {
   if (!exists(path)) {
      cout << "Can't open the file!" << endl;
      throw std::runtime_error("File does not exist");
   }

   ifstream fileStream(path.string(), std::ios::binary);

   BMP_FILE_HEADER bmpFileHeader;
   BMP_INFO_HEADER bmpInfoHeader;

   fileStream.read(reinterpret_cast<char*>(&bmpFileHeader), sizeof(BMP_FILE_HEADER));
   fileStream.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(BMP_INFO_HEADER));

   if (bmpFileHeader.bType != BMP_SIGNATURE)
      throw std::runtime_error("Image is not a BMP file");
   if (bmpInfoHeader.biBitCount != 1)
      throw std::runtime_error("Image was not black and white");

   unsigned long long colourTableBuffer;
   fileStream.read(reinterpret_cast<char*>(&colourTableBuffer), 8);

   if (colourTableBuffer != COLOUR_TABLE) {
      std::cout << "WARNING: Wrong colour table format detected" << std::endl;
   }

   // Skip any bytes inbetween the headers and the data
   fileStream.seekg(bmpFileHeader.bOffset, std::ios::beg);

   uint32_t imageWidthInBytes = bmpInfoHeader.biWidth % 8 == 0
                              ? bmpInfoHeader.biWidth / 8
                              : bmpInfoHeader.biWidth / 8 + 1;
   auto imageBytesToRead = imageWidthInBytes * bmpInfoHeader.biHeight;

   // Read the bmp file bytes
   auto bmpData = BitVector<uint8_t>(imageBytesToRead, 0xFF);
   fileStream.read(reinterpret_cast<char*>(bmpData.data()), imageBytesToRead);
   fileStream.close();

   return BmpImage{bmpFileHeader, bmpInfoHeader, bmpData};
}

int BmpManager::SaveBMP(const filesystem::path& location, BmpImage& bmpImage) {
   ofstream fileStream(location.string(), std::ios::binary);

   if (!fileStream.is_open()) {
      throw std::runtime_error("Can't open the file!");
   }

   fileStream.write(reinterpret_cast<char*>(&bmpImage.bmpFileHeader), sizeof(BMP_FILE_HEADER));
   fileStream.write(reinterpret_cast<char*>(&bmpImage.bmpInfoHeader), sizeof(BMP_INFO_HEADER));
   fileStream.write(reinterpret_cast<char*>(&bmpImage.colourTable), sizeof(COLOUR_TABLE));

   fileStream.write(reinterpret_cast<char*>(bmpImage.data.data()), bmpImage.data.size());
   fileStream.close();

   return 0;
}

BmpImage BmpManager::CreateBMP(const PIXEL_ARRAY& pixels) {
   constexpr auto bmpFileHeader = BMP_FILE_HEADER{
      .bType = BMP_SIGNATURE, // little-endian 0x4D42
      .bSize = 54 + 8 + SCREEN_ARRAY_WIDTH * SCREEN_ARRAY_HEIGHT,
      .bReserved1 = 0,
      .bReserved2 = 0,
      .bOffset = 54 + 8
   };
   constexpr auto bmpInfoHeader = BMP_INFO_HEADER{
      .biInfoSize = 40,
      .biWidth = SCREEN_ARRAY_WIDTH * 8,
      .biHeight = SCREEN_ARRAY_HEIGHT,
      .biPlanes = 1,
      .biBitCount = 1,
      .biCompression = 0,
      // NOTE: Can be 0 for uncompressed
      .bimpImageSize = 0,
      .biXPelsPerMeter = 0,
      .biYPelsPerMeter = 0,
      .biClrUsed = 2,
      .biClrImportant = 0,
   };

   auto bmpData = BitVector<UBYTE>(SCREEN_ARRAY_WIDTH * SCREEN_ARRAY_HEIGHT);

   for (auto y = 0; y < SCREEN_ARRAY_HEIGHT; y++) {
      for (auto x = 0; x < SCREEN_ARRAY_WIDTH; x++) {
         bmpData.push_back(pixels.at(y).at(x));
      }
   }

   return BmpImage{bmpFileHeader, bmpInfoHeader, bmpData, COLOUR_TABLE};
}
