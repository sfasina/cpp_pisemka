//
// Created by fasin on 13.10.2026.
//

#include "Maze.h"
#include <iostream>

Maze::Maze() {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            maze.at(row).at(col) = '-';
        }
    }
}

bool Maze::isInside(int row, int col) const {
    if (row < 0 || row >= SIZE) {
        return false;
    }
    if (col < 0 || col >= SIZE) {
        return false;
    }
    return true;
}

void Maze::print(int wormRow, int wormCol) const {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (row == wormRow && col == wormCol) {
                std::cout << '@';
            } else {
                std::cout << maze.at(row).at(col);
            }
        }
        std::cout << std::endl;
    }
}
