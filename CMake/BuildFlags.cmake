# Use valgrind for debug purposes
option(VALGRIND "Use -g on project compile" OFF)

if (VALGRIND)
    target_compile_options(RType PRIVATE -g)
endif()

# Optimize flag
IF (NOT WIN32)
    target_compile_options(RType PRIVATE -O3)
ENDIF()

# MacOS dirty patch for ambiguous reversed operator warning with Clang
if (APPLE)
    target_compile_options(RType PRIVATE -Wno-ambiguous-reversed-operator)
ENDIF()

target_compile_options(RType PRIVATE -pthread)