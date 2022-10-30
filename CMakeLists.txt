cmake_minimum_required(VERSION 3.23)
project(ATM-Server)

set(CMAKE_CXX_STANDARD 11)

add_executable(ATM-Server main.cpp ServerSocket/ServerSocket.cpp)
