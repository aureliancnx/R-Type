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

# RayLib version
set(raylib_VERSION 4.0.0)
find_package(raylib REQUIRED)
message(STATUS "RayLib version: ${raylib_VERSION}")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS iostreams)
message(STATUS "Boost version: ${Boost_VERSION}")

option(IS_SERVER "Generate R-Type server" OFF)

if(${IS_TEST_NETWORK})
	file(GLOB_RECURSE SOURCES TestNetworkMain.cpp Assets/Components/*.cpp Packages/*.cpp)
else()
	file(GLOB_RECURSE SOURCES ClientMain.cpp Assets/Components/*.cpp Packages/*.cpp)
endif()

add_executable(RType ${SOURCES} ${HEADERS})

# Library
include(Library/library.cmake)

target_link_libraries(RType raylib)

if(${Boost_FOUND})
	include_directories(${Boost_INCLUDE_DIRS})
	target_link_libraries(RType ${Boost_LIBRARIES})
endif()

# Includes
include_directories(.)
include_directories(Assets/Components)

# Packages
include(Packages/packages.cmake)
