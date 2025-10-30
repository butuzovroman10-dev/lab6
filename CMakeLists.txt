cmake_minimum_required(VERSION 3.12)
project(Lab6_Jordan_Gauss VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Основная программа
add_executable(jordan_gauss_solver
    src/main.cpp
    src/JordanGaussSolver.cpp
)

target_include_directories(jordan_gauss_solver PRIVATE include)