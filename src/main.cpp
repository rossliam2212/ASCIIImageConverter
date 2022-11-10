#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "ImageToAscii.h"


int main(int argc, char** argv) {

//    std::cout << "argc = " << argc << "\n\n";
//
//    for (int i = 0; i < argc; ++i) {
//        std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
//    }


    Image i{"../images/erin.JPG"};
    std::cout << i << std::endl;
//    i.printRowsAndCols();

    ImageToAscii converter{i, 4};
    converter.convert();

    return 0;
}
