cmake_minimum_required(VERSION 3.15)
project(TestingDemo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# A library lets multiple test binaries link the same compiled math code
# without recompiling it per binary.
add_library(mathlib STATIC src/math.cpp)

# PUBLIC: test targets that link mathlib get -Isrc automatically.
target_include_directories(mathlib PUBLIC src)

# PUBLIC: test targets inherit C++17 without their own compile_features calls.
target_compile_features(mathlib PUBLIC cxx_std_17)

# IMPORTANT: must be called in the ROOT CMakeLists.txt, not in a subdirectory,
# otherwise ctest run from the build root won't find any tests.
enable_testing()

# Must come AFTER enable_testing() and AFTER mathlib is defined.
add_subdirectory(tests)
