# Add cpp files recursively to compilation
file(GLOB_RECURSE SOURCES
        GameMain.cpp
        Assets/Components/*.cpp # Components
        Packages/*.cpp # Package files
        Library/backward/backward.cpp # Backward
)

# Copy Assets and Maps to binary folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Maps DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add executable
add_executable(RType ${SOURCES} ${HEADERS})