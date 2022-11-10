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

    std::vector<std::vector<char>> asciiRepresentation;

    std::array<char, 11> characters {'@', '#', 'S', '%', '?', '*', '+', ';', ':', ',', '.'};

public:
    explicit ImageToAscii(Image& image, int pixelsPerCharacter = 1);
    void convert();

private:
    void convertFourPPC();
    void convertOnePPC();
    char convertColorToChar(const cv::Vec3b& pixel);
    char convertColorToChar(std::array<cv::Vec3b, 4> &pixels);
    void getNewFileName();

    bool outputToFile();

    void print();
    void print(const std::vector<std::vector<cv::Vec3b>>& vec);
    void print(const std::vector<std::array<cv::Vec3b, 4>>& vec);
};


#endif //ASCIIARTGENERATOR_IMAGETOASCII_H
