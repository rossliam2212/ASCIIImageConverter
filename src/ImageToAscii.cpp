//
// Created by Liam Ross on 29/09/2022.
//

#include "ImageToAscii.h"

ImageToAscii::ImageToAscii(Image& image, const std::string& outputLocation, int pixelsPerCharacter)
    : image{image},
      outputLocation{outputLocation},
      pixelsPerCharacter{pixelsPerCharacter},
      newFileName{} { }

void ImageToAscii::convert() {
    getNewFileName();


    // - Convert each pixel to an ASCII character
    // - Have a vector that holds vectors of chars
    // - Each vector of chars represents a row

    // Check the pixel per character entered
    // - Loop through all the pixels in the originalImage and get the BGR value
    // - Input the color value into an algorithm than returns a character
    //   depending on the BGR value

    if (pixelsPerCharacter == 1)
        convertOnePPC();
    else if (pixelsPerCharacter == 4)
        convertFourPPC();
    else {
        std::cerr << "An error has occurred!" << std::endl;
        return;
    }
}

void ImageToAscii::convertOnePPC() {
    for (auto i = 0; i < image.getRows(); i++) {
        std::vector<char> row;
        for (auto j = 0; j < image.getColumns(); j++) {
            // Getting the color intensity
            cv::Vec3b cl = image.getGreyScaleImage().at<cv::Vec3b>(i, j);
            auto c = convertColorToChar(cl);
            row.emplace_back(c);
        }
        row.shrink_to_fit();
        asciiRepresentation.emplace_back(row);
    }
    asciiRepresentation.shrink_to_fit();

    if (outputToFile()) {
        std::cout << "\nImages converted Successfully!\n";
    }
}

void ImageToAscii::convertFourPPC() {
    std::vector<std::array<cv::Vec3b, 4>> pixelBlocks;

    for (auto i = 0; i < image.getRows(); i+=2) {
        for (auto j = 0; j < image.getColumns(); j+=2) {

            std::array<cv::Vec3b, 4> pixels;

            for (auto k = 0; k < 4; k++) {
                cv::Vec3b cl;

                switch (k) {
                    case 0: {
                        cl = image.getGreyScaleImage().at<cv::Vec3b>(i, j);
//                        std::cout << image.getGreyScaleImage().at<cv::Vec3b>(j, i) << " ";
                        break;
                    }
                    case 1: {
                        cl = image.getGreyScaleImage().at<cv::Vec3b>(i + 1, j);
//                        std::cout << image.getGreyScaleImage().at<cv::Vec3b>(j + 1, i) << "\n";
                        break;
                    }
                    case 2: {
                        cl = image.getGreyScaleImage().at<cv::Vec3b>(i, j + 1);
//                        std::cout << image.getGreyScaleImage().at<cv::Vec3b>(j, i + 1) << " ";
                        break;
                    }
                    case 3: {
                        cl = image.getGreyScaleImage().at<cv::Vec3b>(i + 1, j + 1);
//                        std::cout << image.getGreyScaleImage().at<cv::Vec3b>(j + 1, i + 1) << "\n\n";
                        break;
                    }
                    default:
                        break;
                }
                pixels[k] = cl;
            }
            pixelBlocks.emplace_back(pixels);
        }
    }


    std::vector<char> row;
    int counter{};
    for (auto& block : pixelBlocks) {
        counter++;
        auto c = convertColorToChar(block);
        row.emplace_back(c);

        if (counter == image.getColumns()/2 ) {
            counter = 0;
            row.shrink_to_fit();
            asciiRepresentation.emplace_back(row);
            row.clear();
        }
    }
    asciiRepresentation.shrink_to_fit();
    if (outputToFile()) {
        std::cout << "\nImages converted Successfully!\n\n";
    }
}

char ImageToAscii::convertColorToChar(const cv::Vec3b& pixel) {
    float colorFloat = pixel[0];
    if (colorFloat >= 200) {
        colorFloat += 35;

        if (colorFloat > 255)
            colorFloat = 255;
    }
    else if (colorFloat <= 120) {
        colorFloat -= 40;

        if (colorFloat < 0)
            colorFloat = 0;
    }

    int colorVal = floor(colorFloat / 25);

//    std::cout << "\nColorFloat: " << colorFloat << std::endl;
//    std::cout << "ColorVal: " << colorVal << std::endl;

    return characters[colorVal];
}

char ImageToAscii::convertColorToChar(std::array<cv::Vec3b, 4>& pixels) {
    float colorFloatTotal{};
    int colorVal;

    for (const auto& pixel : pixels) {
        float colorFloat = pixel[0];

        if (colorFloat >= 200) {
            colorFloat += 35;

            if (colorFloat > 255)
                colorFloat = 255;
        }
        else if (colorFloat <= 120) {
            colorFloat -= 40;

            if (colorFloat < 0)
                colorFloat = 0;
        }

        colorFloatTotal += colorFloat;
    }
    colorVal = floor((colorFloatTotal / 4) / 25);
//    colorVal = floor(colorFloatTotal / 25);

//    std::cout << "\nColorFloatTotal: " << colorFloatTotal << std::endl;
//    std::cout << "ColorVal: " << colorVal << std::endl;

    return characters[colorVal];
}

void ImageToAscii::getNewFileName() {
    std::cout << "What would you like to name the output file?\n>";
    std::cin >> newFileName;
}

bool ImageToAscii::outputToFile() {
//    std::string prefix{"../convertedImages/"};
//    std::string extension{".txt"};
    std::string outputFileName{outputLocation + newFileName + ".txt"};

    std::ofstream outputFile{outputFileName};

    if (!outputFile) {
        std::cerr << "Error creating file!" << std::endl;
        return false;
    }

    for (const auto& row : asciiRepresentation) {
        for (const auto& c : row) {
            outputFile << c << " ";
        }
        outputFile << "\n";
    }

    outputFile.close();
    return true;
}