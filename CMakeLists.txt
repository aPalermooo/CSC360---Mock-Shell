cmake_minimum_required(VERSION 3.28)
project(shell)

set(CMAKE_CXX_STANDARD 14)

add_executable(shell
        shell.cpp
        history.cpp)
