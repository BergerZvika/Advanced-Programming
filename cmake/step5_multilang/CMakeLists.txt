cmake_minimum_required(VERSION 3.15)

# Both C and C++ compilers are detected.
project(MultiLang C CXX)

# Requests C11; fails at configure time if the compiler can't provide it.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Requests C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable GNU extensions: -std=c++17 instead of -std=gnu++17.
# Keeps the code portable across GCC, Clang, and MSVC.
set(CMAKE_CXX_EXTENSIONS OFF)

# CMake dispatches each file to the right compiler by extension:
#   .cpp → CXX compiler;  .c → C compiler
add_executable(multilang
    main.cpp          # compiled as C++
    cmath_bridge.c    # compiled as C
    cpp_analysis.cpp  # compiled as C++
)

# CMAKE_CURRENT_SOURCE_DIR: this file's directory (unlike CMAKE_SOURCE_DIR,
# which always points to the top-level root and never changes).
target_include_directories(multilang PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(multilang PRIVATE m)
