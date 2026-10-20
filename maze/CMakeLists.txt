cmake_minimum_required(VERSION 4.3)
project(maze)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(maze
        Direction.h
        Game.cpp
        Game.h
        main.cpp
        Maze.cpp
        Maze.h
        Worm.cpp
        Worm.h)
