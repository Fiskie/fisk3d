cmake_minimum_required(VERSION 3.2)
project(fisk3d)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "-std=c++14")

# Look up SDL2 and add the include directory to our include path
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_TTF REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp)

add_executable(SDL2_App ${SOURCE_FILES} src/Timer.cpp src/Structs.cpp src/World/WorldObject.cpp src/Event.cpp src/Game.cpp src/FatalGameException.cpp src/FatalGameException.h src/World/Player.cpp src/World/Player.h src/World/Brush.cpp src/World/Brush.h src/Map.cpp src/Map.h src/Cameras/Camera.cpp src/Cameras/Camera.h src/Cameras/TopDownCamera.cpp src/Cameras/TopDownCamera.h src/World/Entity.cpp)
target_link_libraries(SDL2_App ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})