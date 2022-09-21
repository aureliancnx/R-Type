cmake_minimum_required(VERSION 3.16)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR} AND NOT WIN32)
	message(FATAL_ERROR
	"You can not use CMake to build from the root of it's source tree!\n"
	"Remove the CMakeCache.txt file from this directory, then create a separate directory\n"
	"(either below this directory or elsewhere), and then re-run CMake from there.")
endif(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR} AND NOT WIN32)

project(RType LANGUAGES CXX)

option(IS_SERVER "Generate R-Type server" OFF)

# Library
add_subdirectory(Library/KapEngine)
add_subdirectory(Library/KapMirror)

if(${IS_SERVER})
	file(GLOB_RECURSE SOURCES ServerMain.cpp Assets/Components/*.cpp)
else()
	file(GLOB_RECURSE SOURCES ClientMain.cpp Assets/Components/*.cpp)
endif()

add_executable(RType ${SOURCES} ${HEADERS})

target_link_libraries(RType KapEngine)
target_link_libraries(RType KapMirror)

include_directories(.)
include_directories(Assets/Components)

# KapMirror include
include_directories(Library/KapMirror)

# KapEngine include
include(Library/KapEngine/CMake/engine_include.cmake)
