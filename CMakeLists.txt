cmake_minimum_required(VERSION 3.21)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Minesweeper
        Game.cpp
        GraphicsIndex.cpp
        index.h
        LeaderBoard.cpp
        Menu.cpp
        Minesweeper.cpp)
