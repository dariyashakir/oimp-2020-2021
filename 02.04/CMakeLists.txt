set(NAME 02_04)

project(${NAME})

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -Wextra")

set(CMAKE_CXX_STANDARD 20)

add_executable(${NAME}_first first.cpp)
add_executable(${NAME}_second second.cpp)
add_executable(${NAME}_game game.cpp)
add_executable(3.D D.cpp)
add_executable(3.I I.cpp)
add_executable(3.K K.cpp)
add_executable(3.L L.cpp)
add_executable(3.N N.cpp)
add_executable(collision_detection collision_detection.cpp)
