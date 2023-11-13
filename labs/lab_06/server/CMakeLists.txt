# Find required packages
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
# Add executable
add_executable(${SERVER_EXE} server.cpp)
# Include dirs
target_include_directories(${SERVER_EXE} PRIVATE .)
# Link libraries
target_link_libraries(${SERVER_EXE} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(${SERVER_EXE} PRIVATE Boost::system)
