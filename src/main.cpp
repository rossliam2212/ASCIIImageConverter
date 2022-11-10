#include "ImageToAscii.h"

int main(int argc, char** argv) {

    Image i{argv[1]};

    if (argc >= 3) {
        ImageToAscii converter{i, std::stoi(argv[2])};
        converter.convert();
    } else {
        ImageToAscii converter{i};
        converter.convert();
    }
    return 0;
}
