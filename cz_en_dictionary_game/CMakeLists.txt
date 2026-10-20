cmake_minimum_required(VERSION 4.3)
project(cz_en_dictionary_game)

set(CMAKE_CXX_STANDARD 20)

add_executable(cz_en_dictionary_game main.cpp
        Game.cpp
        Game.h
        FileManager.cpp
        FileManager.h
)

# program se spousti z build slozky, proto tam zkopirujeme slovnik
configure_file(words.txt ${CMAKE_CURRENT_BINARY_DIR}/words.txt COPYONLY)
