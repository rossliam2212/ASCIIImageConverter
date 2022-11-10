#include "ImageToAscii.h"

int main(int argc, char** argv) {

//    for (int i = 0; i < argc; i++)
//        std::cout << "argv[" << i << "]: " << argv[i] << "\n";

    Image i{argv[1]};

    if (argc >= 4) {
        ImageToAscii converter{i, argv[2], std::stoi(argv[3])};
        converter.convert();
    } else {
        ImageToAscii converter{i, argv[2]};
        converter.convert();
    }
    return 0;
}
