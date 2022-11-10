//
// Created by Liam Ross on 04/10/2022.
//

#include "Image.h"

Image::Image(std::string& filePath)
    : filePath{filePath},
      greyScaleImage{} {
    originalImage = cv::imread(filePath);
    convertToGreyScale();
}

Image::Image(std::string&& filePath)
    : filePath{filePath},
      greyScaleImage{} {
    originalImage = cv::imread(filePath);
    convertToGreyScale();
}

void Image::convertToGreyScale() {
    cv::cvtColor(originalImage, greyScaleImage, cv::COLOR_BGR2GRAY);
}

void Image::viewOriginal() {
    cv::imshow(filePath, originalImage);
    cv::waitKey(0);
}

void Image::viewGreyScale() {
    cv::imshow(filePath, greyScaleImage);
    cv::waitKey(0);
}

// Getters
cv::Mat Image::getGreyScaleImage() const { return greyScaleImage; }
int Image::getColumns() const { return originalImage.cols; }
int Image::getRows() const { return originalImage.rows; }
int Image::getNumberOfPixels() const { return originalImage.cols * originalImage.rows; }


void Image::printRowsAndCols() {
    std::cout << "Columns: " << greyScaleImage.cols << std::endl;
    std::cout << "Rows: " << greyScaleImage.rows << std::endl;

    for (auto i = 0; i < greyScaleImage.cols; i++) {
        for (auto j = 0; j < greyScaleImage.rows; j++) {
            std::cout << greyScaleImage.at<cv::Vec3b>(j, i) << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n\n";
}

std::ostream& operator<<(std::ostream& os, const Image& image) {
    os << "\nFilepath: " << image.filePath << "\n"
       << "Columns: " << image.originalImage.rows << "\n"
       << "Rows: " << image.originalImage.rows << "\n"
       << "Pixels: " << image.getNumberOfPixels() << "\n";
    return os;
}


