cmake_minimum_required(VERSION 3.15)
project(dpll CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(dpll
    src/main.cpp
    src/parser.cpp
    src/formula.cpp
    src/solver.cpp
    src/heuristic.cpp
)