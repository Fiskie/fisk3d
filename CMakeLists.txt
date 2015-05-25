cmake_minimum_required(VERSION 3.2)
project(fisk3d)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "-std=c++0x")

# Look up SDL2 and add the include directory to our include path
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_TTF REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp)

add_executable(SDL2_App ${SOURCE_FILES} src/Timer.cpp src/Structs.cpp src/WorldObject.cpp src/Event.cpp src/Game.cpp src/DebugGame.cpp src/FatalGameException.cpp src/FatalGameException.h src/Player.cpp src/Player.h src/Brush.cpp src/Brush.h src/Map.cpp src/Map.h)
target_link_libraries(SDL2_App ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})