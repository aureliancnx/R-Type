# KapEngine
# options for KapEngine compile
option(KAPENGINE_THREAD "" OFF)
option(KAPENGINE_BETA "" OFF)
option(KAPENGINE_DEBUG "" ON)
option(KAPENGINE_EDITOR "" OFF)
option(KAPENGINE_PROFILER "" OFF)
add_subdirectory(Library/KapEngine)
target_link_libraries(RType KapEngine)
include(Library/KapEngine/CMake/engine_include.cmake)

# LuaEngine
add_subdirectory(Library/LuaEngine)
target_link_libraries(RType lua::lib)
include_directories(Library/backward)
