cmake_minimum_required(VERSION 3.23)
project(Code)

set(CMAKE_CXX_STANDARD 20)

add_executable(Code src/main.cpp src/Human.cpp src/Organism.cpp src/Zombie.cpp src/City.cpp)
