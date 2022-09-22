# KapEngine
add_subdirectory(Library/KapEngine)
target_link_libraries(RType KapEngine)
include(Library/KapEngine/CMake/engine_include.cmake)

# KapMirror
add_subdirectory(Library/KapMirror)
target_link_libraries(RType KapMirror)
include_directories(Library/KapMirror)
