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

# use valgrind programm
option(VALGRIND "Use -g on project compile" OFF)

# RayLib version
set(raylib_VERSION 4.0.0)
find_package(raylib REQUIRED)
message(STATUS "RayLib version: ${raylib_VERSION}")

set(ZLIB_USE_STATIC_LIBS ON)
find_package(ZLIB REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS iostreams)

file(GLOB_RECURSE SOURCES GameMain.cpp Assets/Components/*.cpp Packages/*.cpp)

add_executable(RType ${SOURCES} ${HEADERS})

# Library
include(Library/library.cmake)

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(RType raylib)
target_link_libraries(RType Boost::iostreams)

target_link_libraries(RType ZLIB::ZLIB)
#if (WIN32)
#    target_link_libraries(RType zlib)
#else()
#    target_link_libraries(RType z) # This is not a joke
#endif()

# Includes
include_directories(.)
include_directories(Assets/Components)

# Packages
include(Packages/packages.cmake)

if (VALGRIND)
    target_compile_options(RType PRIVATE -g)
endif()
IF (NOT WIN32)
    target_compile_options(RType PRIVATE -O3)
ENDIF()
target_compile_options(RType PRIVATE -pthread)

set(CPACK_INSTALL_PREFIX /)
set(CPACK_SET_DESTDIR true)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)

set(CPACK_DEBIAN_PACKAGE_NAME "RType")
set(CPACK_DEBIAN_PACKAGE_CONTACT "idk@gmail.com")
set(CPACK_DEBIAN_PACKAGE_VERSION "1.0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "RType")

if(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "TGZ;DEB;RPM")
endif()
include(CPack)