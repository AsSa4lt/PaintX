cmake_minimum_required(VERSION 3.21)

set(CMAKE_TOOLCHAIN_FILE "" CACHE STRING "Main application executable.")

project(
    app
    VERSION 0.1
    DESCRIPTION "An application to draw simple images"
    LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(APP_EXE "app" CACHE STRING "Main application executable.")

# Adds SFML library
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# Adds TGUI library
find_package(TGUI 0.9 REQUIRED)

add_subdirectory(src)

