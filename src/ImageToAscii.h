//
// Created by Liam Ross on 29/09/2022.
//

#ifndef ASCIIARTGENERATOR_IMAGETOASCII_H
#define ASCIIARTGENERATOR_IMAGETOASCII_H

#include <vector>
#include <array>
#include <fstream>
#include "Image.h"

class ImageToAscii {
private:
    Image image;
    int pixelsPerCharacter;
    std::string newFileName;
    std::string outputLocation;

    std::vector<std::vector<char>> asciiRepresentation;

    //    .:-=+*#%@ - http://paulbourke.net/dataformats/asciiart/
    std::array<char, 11> characters {'@', '#', 'S', '%', '?', '*', '+', ';', ':', ',', '.'};

public:
    ImageToAscii(Image& image, const std::string& outPutLocation, int pixelsPerCharacter = 1);
    void convert();

private:
    void convertFourPPC(); // Four pixels per character
    void convertOnePPC(); // One pixel per character
    char convertColorToChar(const cv::Vec3b& pixel);
    char convertColorToChar(std::array<cv::Vec3b, 4> &pixels);
    void getNewFileName();

    bool outputToFile();
};


#endif //ASCIIARTGENERATOR_IMAGETOASCII_H
