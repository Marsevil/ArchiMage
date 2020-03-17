cmake_minimum_required(VERSION 3.7)
project(libShaders)

#Parametre
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

#Project
set(SRCS
    "objetsOFF.cpp"
)

set (HEADERS
    "objetsOFF.h"
)

add_library(shaders ${SRCS} ${HEADERS})
target_compile_options(shaders PUBLIC "-Wall")

#Lib formes
#target_include_directories(DrawableFormes PUBLIC "../" BEFORE)
