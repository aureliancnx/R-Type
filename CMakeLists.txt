cmake_minimum_required(VERSION 3.16)

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR} AND NOT WIN32)
	message(FATAL_ERROR
	"You can not use CMake to build from the root of it's source tree!\n"
	"Remove the CMakeCache.txt file from this directory, then create a separate directory\n"
	"(either below this directory or elsewhere), and then re-run CMake from there.")
endif(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR} AND NOT WIN32)

project(RType LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_STANDARD 17)

option(IS_SERVER "Generate R-Type server" OFF)

# Library
add_subdirectory(Library/KapEngine)
add_subdirectory(Library/KapMirror)
add_subdirectory(Library/KapRaylib)

if(${IS_SERVER})
	file(GLOB_RECURSE SOURCES ServerMain.cpp Assets/Components/*.cpp)
else()
	file(GLOB_RECURSE SOURCES ClientMain.cpp Assets/Components/*.cpp)

	# # RayLib version
	# set(raylib_VERSION 4.0.0)
	# find_package(raylib REQUIRED)
endif()

add_executable(RType ${SOURCES} ${HEADERS})

target_link_libraries(RType KapEngine)
target_link_libraries(RType KapMirror)
# target_link_libraries(RType KapRaylib)

# if(!${IS_SERVER})
# 	target_link_libraries(RType raylib)
# endif()

include_directories(.)
include_directories(Assets/Components)
# include_directories(Library/KapRaylib/KapRaylib)

# KapMirror include
include_directories(Library/KapMirror)

# KapEngine include
include(Library/KapEngine/CMake/engine_include.cmake)
