cmake_minimum_required(VERSION 3.7)
project(libShaders)

#Parametre
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

#Project
set(SRCS
    "fonctions.cpp"
	"glsl_fs.cpp"
	"glsl_vs.cpp"
)

set (HEADERS
    "fonctions.hpp"
	"glsl_fs.hpp"
	"glsl_vs.hpp"
)

add_library(shaders ${SRCS} ${HEADERS})
target_compile_options(shaders PUBLIC "-Wall")

#Lib formes
#target_include_directories(DrawableFormes PUBLIC "../" BEFORE)
