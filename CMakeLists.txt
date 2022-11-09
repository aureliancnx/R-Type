cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Library/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR} AND NOT WIN32)
    message(FATAL_ERROR
            "You can not use CMake to build from the root of it's source tree!\n"
            "Remove the CMakeCache.txt file from this directory, then create a separate directory\n"
            "(either below this directory or elsewhere), and then re-run CMake from there.")
endif(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR} AND NOT WIN32)

project(RType LANGUAGES CXX VERSION 1.0.1)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_STANDARD 20)

include(Dependencies)

file(GLOB_RECURSE SOURCES GameMain.cpp Assets/Components/*.cpp Packages/*.cpp Library/backward/backward.cpp)

add_executable(RType ${SOURCES} ${HEADERS})

include(DependenciesLink)

# Library
include(Library/library.cmake)

# Includes
include_directories(.)
include_directories(Library/backward)
include_directories(Assets/Components)

# Packages
include(Packages/packages.cmake)

# Build Flags
include(BuildFlags)

# Package app
include(Package)