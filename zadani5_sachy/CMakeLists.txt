cmake_minimum_required(VERSION 4.3)
project(zadani5_sachy)

set(CMAKE_CXX_STANDARD 20)

add_executable(zadani5_sachy main.cpp
        Position.h
        Board.cpp
        Board.h
        PieceTable.cpp
        PieceTable.h
        Rules.cpp
        Rules.h
)

# program se spousti z build slozky, proto tam zkopirujeme data
configure_file(sachovnice.txt ${CMAKE_CURRENT_BINARY_DIR}/sachovnice.txt COPYONLY)
configure_file(figurky.txt ${CMAKE_CURRENT_BINARY_DIR}/figurky.txt COPYONLY)
