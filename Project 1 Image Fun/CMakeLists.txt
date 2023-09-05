cmake_minimum_required(VERSION 3.0)

project(imagefun)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False) # no GNU language extensions

include_directories(.)

add_compile_options(-pedantic -Wall -Wextra)

add_executable(imagefun
        main.cpp
        editor.cpp
        editor.h
        tool.h
        manager.h
        utility.h
        picture.h
        framework/manager.cpp
        framework/picture.cpp
        framework/lodepng.cpp
        framework/lodepng.h
        framework/utility.cpp
        framework/steganography.h
        framework/steganography.cpp
        framework/mondrian.h
        framework/mondrian.cpp
        )
