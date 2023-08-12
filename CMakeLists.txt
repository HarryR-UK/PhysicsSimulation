cmake_minimum_required(VERSION 3.15)
project(PhysicsSimulation)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Add the source files to the project
file(GLOB SOURCES src/*.cpp)

# Find the SFML package
find_package(SFML 2.5 COMPONENTS window graphics system audio network REQUIRED)

# Add the include directories
include_directories(${SFML_INCLUDE_DIR})

# Create the executable
add_executable(prog ${SOURCES})

# Link the required SFML libraries
target_link_libraries(prog PRIVATE
    sfml-window
    sfml-graphics
    sfml-system
    sfml-audio
    sfml-network
)
