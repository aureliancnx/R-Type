# KapEngine
add_subdirectory(Library/KapEngine)
target_link_libraries(RType KapEngine)
include(Library/KapEngine/CMake/engine_include.cmake)

# LuaEngine
add_subdirectory(Library/LuaEngine)
target_link_libraries(RType lua::lib)
