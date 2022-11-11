# Find packages using VCPKG

# RayLib version
set(raylib_VERSION 4.0.0)
find_package(raylib REQUIRED)
message(STATUS "RayLib version: ${raylib_VERSION}")

set(ZLIB_USE_STATIC_LIBS ON)
find_package(ZLIB REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS iostreams)
