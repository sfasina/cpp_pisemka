cmake_minimum_required(VERSION 4.3)
project(zadani6_lode)

set(CMAKE_CXX_STANDARD 20)

add_executable(zadani6_lode main.cpp
        Position.h
        Ocean.cpp
        Ocean.h
        Battle.cpp
        Battle.h
)

# program se spousti z build slozky, proto tam zkopirujeme rozmisteni lodi
configure_file(lode.txt ${CMAKE_CURRENT_BINARY_DIR}/lode.txt COPYONLY)
