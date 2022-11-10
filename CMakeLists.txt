cmake_minimum_required(VERSION 3.23)
project(ASCIIArtGenerator)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenCV)

set(SOURCE_FILES src/main.cpp src/ImageToAscii.cpp src/ImageToAscii.h src/Image.cpp src/Image.h)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(ASCIIArtGenerator ${SOURCE_FILES})
target_link_libraries(ASCIIArtGenerator ${OpenCV_LIBS})
