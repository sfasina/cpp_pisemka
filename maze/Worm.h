//
// Created by fasin on 13.10.2026.
//

#ifndef MAZE_WORM_H
#define MAZE_WORM_H

#include "Direction.h"

struct Position {
    int row;
    int col;
};

class Worm {
public:
    Worm();

    int getRow() const;
    int getCol() const;
    Position getNextPosition(Direction direction) const;
    void setPosition(int row, int col);

private:
    int row;
    int col;
};


#endif //MAZE_WORM_H
