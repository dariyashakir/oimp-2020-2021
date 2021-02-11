set(NAME 01_14)

project(${NAME})

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -Werror -Wextra")

set(CMAKE_CXX_STANDARD 20)

add_executable(${NAME}_first first.cpp)
add_executable(${NAME}_second second.cpp)
add_executable(${NAME}_game game.cpp)
