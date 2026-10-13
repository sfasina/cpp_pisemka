//
// Created by fasin on 13.10.2026.
//

#ifndef MAZE_GAME_H
#define MAZE_GAME_H

#include "Direction.h"
#include "Maze.h"
#include "Worm.h"

class Game {
public:
    void run();

private:
    bool keyToDirection(char key, Direction& direction) const;
    void moveWorm(Direction direction);
    void clearScreen() const;

    Maze maze;
    Worm worm;
};


#endif //MAZE_GAME_H
