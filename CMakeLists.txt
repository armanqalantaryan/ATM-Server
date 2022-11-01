cmake_minimum_required(VERSION 3.23)
project(ATM-Server)

set(CMAKE_CXX_STANDARD 11)

add_executable(ATM-Server main.cpp ServerSocket/ServerSocket.cpp)
include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(ATM-Server sqlite3)