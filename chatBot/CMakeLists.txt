cmake_minimum_required(VERSION 4.3)
project(chatBot)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(chatBot
        ChatBot.cpp
        ChatBot.hpp
        Dictionary.cpp
        Dictionary.hpp
        main.cpp
        Dictionary.cpp)


configure_file(${CMAKE_SOURCE_DIR}/chat.txt ${CMAKE_BINARY_DIR}/chat.txt COPYONLY)