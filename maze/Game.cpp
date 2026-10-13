//
// Created by fasin on 13.10.2026.
//

#include "Game.h"
#include <iostream>
#include <cstdlib>

void Game::run() {
    clearScreen();
    maze.print(worm.getRow(), worm.getCol());

    char key = ' ';
    while (key != 'q') {
        std::cout << "Press WASD to move the worm" << std::endl;
        std::cin >> key;
        Direction direction = Direction::North;
        if (keyToDirection(key, direction)) {
            moveWorm(direction);
            clearScreen();
            maze.print(worm.getRow(), worm.getCol());
        }
    }
}

bool Game::keyToDirection(char key, Direction& direction) const {
    if (key == 'w') {
        direction = Direction::North;
        return true;
    }
    if (key == 's') {
        direction = Direction::South;
        return true;
    }
    if (key == 'd') {
        direction = Direction::East;
        return true;
    }
    if (key == 'a') {
        direction = Direction::West;
        return true;
    }
    return false;
}

void Game::moveWorm(Direction direction) {
    Position next = worm.getNextPosition(direction);
    if (maze.isInside(next.row, next.col)) {
        worm.setPosition(next.row, next.col);
    }
}

//metoda pro mazani screenu aby to slo i na macos
void Game::clearScreen() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
