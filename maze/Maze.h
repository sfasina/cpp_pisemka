//
// Created by fasin on 13.10.2026.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H
#include <array>

class Maze {
public:
    Maze();

    bool isInside(int row, int col) const;
    void print(int wormRow, int wormCol) const;
private:
    static const int SIZE = 5;
    std::array<std::array<char, SIZE>, SIZE> maze;
};


#endif //MAZE_MAZE_H
