cmake_minimum_required(VERSION 3.20)
project(lab_06)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SERVER_EXE "server" CACHE STRING "Name of the server executable.")
set(CLIENT_EXE "client" CACHE STRING "Name of the client executable.")
# Include also other directories recursively
add_subdirectory(server)
add_subdirectory(client)
