set(NAME 28_01)

project(${NAME})

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")

set(CMAKE_CXX_STANDARD 20)

add_executable(${NAME}_CW CW.cpp)
add_executable(${NAME}_second second.cpp)
