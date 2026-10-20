cmake_minimum_required(VERSION 4.3)
project(zadani4_obesenec)

set(CMAKE_CXX_STANDARD 20)

add_executable(zadani4_obesenec main.cpp
        WordFile.cpp
        WordFile.h
        Hangman.cpp
        Hangman.h
)

# program se spousti z build slozky, proto tam zkopirujeme slova
configure_file(slova.txt ${CMAKE_CURRENT_BINARY_DIR}/slova.txt COPYONLY)
