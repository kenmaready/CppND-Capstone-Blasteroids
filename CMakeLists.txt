cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_definitions(-std=c++17)

# set(CMAKE_VERBOSE_MAKEFILE on)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Threads)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(Blasteroids src/main.cpp src/Polygon.cpp src/Asteroid.cpp src/Game.cpp src/Controller.cpp src/Renderer.cpp src/Ship.cpp src/Shot.cpp src/Explosion.cpp src/Announcement.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(Blasteroids ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_TTF_LIBRARY})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
