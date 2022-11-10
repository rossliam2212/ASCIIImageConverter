//
// Created by Liam Ross on 04/10/2022.
//

#ifndef ASCIIARTGENERATOR_IMAGE_H
#define ASCIIARTGENERATOR_IMAGE_H

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

class Image {
    friend std::ostream& operator<<(std::ostream& os, const Image& image);

private:
    std::string filePath;
    cv::Mat originalImage;
    cv::Mat greyScaleImage;


public:
    explicit Image(std::string& filePath);
    explicit Image(std::string&& filePath);
    void convertToGreyScale();
    void viewOriginal();
    void viewGreyScale();

    cv::Mat getGreyScaleImage() const;
    int getColumns() const;
    int getRows() const;
    int getNumberOfPixels() const;

    void printRowsAndCols();
};


#endif //ASCIIARTGENERATOR_IMAGE_H
