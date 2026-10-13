//
// Created by fasin on 13.10.2026.
//

#include "Worm.h"

Worm::Worm() {
    row = 0;;
    col = 0;
}

int Worm::getRow() const {
    return row;
}

int Worm::getCol() const {
    return col;
}

Position Worm::getNextPosition(Direction direction) const {
    Position next;
    next.row = row;
    next.col = col;

    if (direction == Direction::North) {
        next.row = row - 1;
    } else if (direction == Direction::South) {
        next.row = row + 1;
    } else if (direction == Direction::East) {
        next.col = col + 1;
    } else if (direction == Direction::West) {
        next.col = col - 1;
    }
    return next;
}

void Worm::setPosition(int newRow, int newCol) {
    row = newRow;
    col = newCol;
}
