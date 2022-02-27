# CPPND: Capstone Game: Blasteroids

This is my Capstone Project for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).  It is an asteroids clone build using SDL2, and was extended from starter code provided by the course, which was inspired by the snake game in [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="blasteroids.gif"/>

  In this Capstone Project, we could choose our own C++ application or extend a Snake game example, following principles we've learned throughout the Nanodegree Program. The project should demonstrate our ability to independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_gfx >= 1.0.4+dfsg-3
  * to install on linux:  sudo apt install libsdl2-gfx-dev
  * If you are building your own cmake/make instead of using the one provided, you will also need to do the following:
    * Add a cmake file called FindSDL2_gfx.cmake to your cmake directory, the one that is included in this repo was found at [https://github.com/aminosbh/sdl2-cmake-modules/blob/master/FindSDL2_gfx.cmake](https://github.com/aminosbh/sdl2-cmake-modules/blob/master/FindSDL2_gfx.cmake)
    * In CMakeLists.txt, add a new `find_package(SDL2_gfx REQUIRED)`
    * Also in CMakeLists.txt add `${SDL2_GFX_LIBRARIES}` to your target_link_libraries
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Blasteroids`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
