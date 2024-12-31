#include <iostream>
#include "myBmpManager.h"
#include "GUI_BMPfile.h"
#include <filesystem>
#include <fstream>
#include <vector>

#include "myGUI.h"

using namespace std;

std::unique_ptr<BmpImage> ReadBMP(filesystem::path path) {
    if (!exists(path)) {
        cout << "Can't open the file!" << endl;
        throw std::runtime_error("File does not exist");
    }

    ifstream fileStream(path.string(), std::ios::binary);

    BMP_FILE_HEADER bmpFileHeader; //Define a bmp file header structure
    BMP_INFO_HEADER bmpInfoHeader; //Define a bmp info header structure

    fileStream.read(reinterpret_cast<char *>(&bmpFileHeader), sizeof(BMP_FILE_HEADER));
    fileStream.read(reinterpret_cast<char *>(&bmpInfoHeader), sizeof(BMP_INFO_HEADER));

    if (bmpInfoHeader.biBitCount != 1) {
        throw std::runtime_error("Image was not black and white");
    }

    unsigned long long colourTableBuffer;
    fileStream.read(reinterpret_cast<istream::char_type *>(&colourTableBuffer), 8);

    if (memcmp(&colourTableBuffer, &COLOUR_TABLE, 8) != 0) {
        cout << std::hex << COLOUR_TABLE << endl;
        cout << std::hex << colourTableBuffer << endl;
        throw std::runtime_error("Colour table is not correct");
    }

    // Skip any bytes inbetween the headers and the data
    fileStream.seekg(bmpFileHeader.bOffset, std::ios::beg);

    int imageWidthInBytes = (bmpInfoHeader.biWidth % 8 == 0)
                                ? (bmpInfoHeader.biWidth / 8)
                                : (bmpInfoHeader.biWidth / 8 + 1);
    auto imageBytesToRead = imageWidthInBytes * bmpInfoHeader.biHeight;

    // Read the bmp file bytes
    auto bmpDataVector = vector<char>(imageBytesToRead, 0xFF);
    fileStream.read(bmpDataVector.data(), imageBytesToRead);
    fileStream.close();

    return make_unique<BmpImage>(BmpImage{
        bmpFileHeader,
        bmpInfoHeader,
        bmpDataVector
    });
}

int WriteBMP(const filesystem::path &location, BmpImage &bmpImage) {
    ofstream fileStream(location.string(), std::ios::binary);

    if (!fileStream.is_open()) {
        throw std::runtime_error("Can't open the file!");
    }

    fileStream.write(reinterpret_cast<char *>(&bmpImage.bmpFileHeader), sizeof(BMP_FILE_HEADER));
    fileStream.write(reinterpret_cast<char *>(&bmpImage.bmpInfoHeader), sizeof(BMP_INFO_HEADER));
    fileStream.write(reinterpret_cast<char *>(&bmpImage.colourTable), sizeof(COLOUR_TABLE));

    fileStream.write(bmpImage.data.data(), bmpImage.data.size());
    fileStream.close();

    return 0;
}

BmpImage CreateBMP(const PIXEL_ARRAY &pixels) {
    const auto bmpFileHeader = BMP_FILE_HEADER{
        .bType = 'B'<<8 | 'M',
        .bSize = 54 + 8 + SCREEN_ARRAY_WIDTH * SCREEN_ARRAY_HEIGHT,
        .bReserved1 = 0,
        .bReserved2 = 0,
        .bOffset = 54 + 8
    };
    const auto bmpInfoHeader = BMP_INFO_HEADER{
        .biInfoSize = 40,
        .biWidth = (SCREEN_ARRAY_WIDTH) * 8,
        .biHeight = static_cast<uint32_t>(pixels.size()),
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

    return BmpImage{
        bmpFileHeader,
        bmpInfoHeader,
        vector<char>(&pixels[0][0], &pixels[0][0] + SCREEN_ARRAY_WIDTH * SCREEN_ARRAY_HEIGHT),
    };
}