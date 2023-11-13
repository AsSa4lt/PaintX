# Find required packages
find_package(Boost COMPONENTS system REQUIRED)
# Add executable
add_executable(${CLIENT_EXE} client.cpp)
# Include dirs
target_include_directories(${CLIENT_EXE} PRIVATE .)
# Link libraries
target_link_libraries(${CLIENT_EXE} PRIVATE Boost::system)
