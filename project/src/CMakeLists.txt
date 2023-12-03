cmake_minimum_required(VERSION 3.24)
project(PaintX)

set(CMAKE_CXX_STANDARD 17)

# Source files
set(SOURCE_FILES
        main.cpp
        main.cpp
        UI/Window.cpp
        UI/Window.h
        # Add other source files here as your project grows
)

# Executable
add_executable(PaintX ${SOURCE_FILES})

# Include directories for SFML and TGUI
include_directories(/usr/local/include)

# Find SFML and link it
find_package(SFML COMPONENTS system graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(PaintX sfml-system sfml-window sfml-graphics)

# Find TGUI and link it
find_package(TGUI REQUIRED)
include_directories(${TGUI_INCLUDE_DIRS})
target_link_libraries(PaintX tgui)
