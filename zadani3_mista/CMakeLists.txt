cmake_minimum_required(VERSION 4.3)
project(zadani3_mista)

set(CMAKE_CXX_STANDARD 20)

add_executable(zadani3_mista main.cpp
        Place.h
        PlaceFile.cpp
        PlaceFile.h
        Rectangle.cpp
        Rectangle.h
)

# program se spousti z build slozky, proto tam zkopirujeme vstupni soubor
configure_file(mista.txt ${CMAKE_CURRENT_BINARY_DIR}/mista.txt COPYONLY)
