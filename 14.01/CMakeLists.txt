project(14_01)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -Werror -Wextra")

set(CMAKE_CXX_STANDARD 20)

add_executable(14_01_first first.cpp)
add_executable(14_01_second second.cpp)
add_executable(game game.cpp)
