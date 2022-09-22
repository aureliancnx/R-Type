cmake_minimum_required(VERSION 3.16)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR} AND NOT WIN32)
	message(FATAL_ERROR
	"You can not use CMake to build from the root of it's source tree!\n"
	"Remove the CMakeCache.txt file from this directory, then create a separate directory\n"
	"(either below this directory or elsewhere), and then re-run CMake from there.")
endif(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR} AND NOT WIN32)

project(KapRaylib LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)

# RayLib version
set(raylib_VERSION 4.0.0)
find_package(raylib REQUIRED)

# KapRaylib sources
file(GLOB_RECURSE SOURCES ${KapRaylib_SOURCE_DIR}/KapRaylib/*.cpp)

add_library(KapRaylib SHARED ${SOURCES} ${HEADERS})

include_directories(${KapRaylib_SOURCE_DIR}/KapRaylib)
include_directories(/home/chaika9/Epitech/R-Type/build/_deps/raylib-src/src)

# KapEngine include
include(../KapEngine/CMake/engine_include.cmake)
