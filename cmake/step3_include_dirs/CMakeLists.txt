cmake_minimum_required(VERSION 3.15)
project(StringTools C)

# Sources are relative to CMAKE_CURRENT_SOURCE_DIR (this file's directory).
add_executable(strtools
    src/main.c
    src/string_utils.c
)

# Adds include/ to the compiler's header search path.
# Visibility keyword controls propagation to consumers:
#   PRIVATE   — only this target (use for implementation headers)
#   PUBLIC    — this target + consumers (use for API headers)
#   INTERFACE — consumers only (use for header-only libraries)
target_include_directories(strtools PRIVATE include)
