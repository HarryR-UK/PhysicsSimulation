
cmake_minimum_required(VERSION 3.14)
project(PhysicsSimulation2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
#
set(SOURCE_FILES include/Global.h src/main.cpp src/Game.cpp include/Game.h src/Time.cpp include/Time.h )
add_executable(PhysicsSimulation2 ${SOURCE_FILES})
include_directories(/usr/local/include)

# 
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(PhysicsSimulation2 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
