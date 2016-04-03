cmake_minimum_required(VERSION 3.3)
project(Pong)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(SYSTEM SDL2-2.0.4/i686-w64-mingw32/include)
include_directories(include)
include_directories(lib/include)
include_directories(lib/include/display)
include_directories(lib/include/display/context)
include_directories(lib/include/error)
include_directories(lib/include/network)
include_directories(lib/include/network/socket)

file(GLOB_RECURSE INCLUDE inclue/*.hh lib/include/*.hh lib/include/*.hpp)

set(SOURCE_FILES
        lib/src/display/context/Input.cpp
        lib/src/display/context/SDLContext.cpp
        lib/src/display/context/SDLWindow.cpp
        lib/src/display/Image.cpp
        lib/src/display/SDLDisplay.cpp
        lib/src/error/FileError.cpp
        lib/src/error/GenericError.cpp
        lib/src/error/LogicError.cpp
        lib/src/error/SDLError.cpp
        lib/src/error/StdError.cpp
        src/main.cpp src/SpaceInvaders.cpp include/SpaceInvaders.hh src/Enemy.cpp include/Enemy.hh src/Column.cpp include/Column.hh src/Shooter.cpp include/Shooter.hh src/Laser.cpp include/Laser.hh)

link_directories(SDL2-2.0.4/i686-w64-mingw32/lib)
link_libraries(mingw32 SDL2main SDL2.dll)
add_executable(SpaceInvaders ${SOURCE_FILES} ${INCLUDE})
