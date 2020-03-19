cmake_minimum_required(VERSION 3.7)
project(libObjectsReader)

#Parametre
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

#Project
set(SRCS
    "objetsOFF.cpp"
)

set (HEADERS
    "objetsOFF.hpp"
)

add_library(objectsReader ${SRCS} ${HEADERS})
target_compile_options(objectsReader PUBLIC "-Wall")

#Lib formes
#target_include_directories(DrawableFormes PUBLIC "../" BEFORE)
