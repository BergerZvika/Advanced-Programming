# 3.18+ required for "Development.Module" component of find_package(Python3).
# Older CMake only knows "Development" (which also requires libpython.so),
# but virtualenvs/conda often omit it. Development.Module needs only Python.h.
cmake_minimum_required(VERSION 3.18)
project(CppPythonDemo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Find Python ─────────────────────────────────────────────────────────────────

# COMPONENTS:
#   Interpreter        — finds python3 executable; sets Python3_EXECUTABLE
#   Development.Module — finds Python.h and module link stub; creates Python3::Module
find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)
message(STATUS "Python3 interpreter : ${Python3_EXECUTABLE}")
message(STATUS "Python3 version     : ${Python3_VERSION}")
message(STATUS "Python3 include dir : ${Python3_INCLUDE_DIRS}")

# ── Fetch pybind11 ──────────────────────────────────────────────────────────────

include(FetchContent)

# pybind11: header-only library that generates Python bindings from C++ templates.
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG        v2.13.6
    GIT_SHALLOW    TRUE
)

# After this, pybind11_add_module() is available as a CMake command.
FetchContent_MakeAvailable(pybind11)

# ── C++ core library ────────────────────────────────────────────────────────────

# STATIC keeps the extension module self-contained — no separate libvec3lib.so.
add_library(vec3lib STATIC src/vec3.cpp)

target_include_directories(vec3lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_compile_features(vec3lib PUBLIC cxx_std_17)

# Shared objects (.so) require all included object files to be compiled with -fPIC.
# Without this, linking a STATIC lib into a MODULE/SHARED produces a relocation error.
set_target_properties(vec3lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

# ── Python extension module ─────────────────────────────────────────────────────

# pybind11_add_module() wraps add_library(MODULE) and adds:
#   • ABI-correct output name (e.g. myvec3.cpython-310-x86_64-linux-gnu.so)
#   • -fvisibility=hidden (exports only PyInit_myvec3)
#   • symbol stripping in Release builds
pybind11_add_module(myvec3 src/bindings.cpp)

# Merges vec3lib's objects into myvec3.so (STATIC + PIC, no relocation errors).
target_link_libraries(myvec3 PRIVATE vec3lib)

# ── Helper target: run_demo ─────────────────────────────────────────────────────

# Phony target; invoke with: cmake --build build --target run_demo
# -E env: CMake's portable "run with env var" (like `env KEY=VAL cmd` on Unix).
# PYTHONPATH=${CMAKE_BINARY_DIR}: lets Python find myvec3.so in the build dir.
# DEPENDS myvec3: rebuilds the extension before running if it's out of date.
# VERBATIM: prevents CMake from shell-escaping the PYTHONPATH= argument.
add_custom_target(run_demo
    COMMAND ${CMAKE_COMMAND} -E env
            "PYTHONPATH=${CMAKE_BINARY_DIR}"
            ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/demo.py
    DEPENDS myvec3
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Python demo (uses C++ extension from build dir)"
    VERBATIM
)

message(STATUS "")
message(STATUS "=== Step 10: C++ + Python via pybind11 ===")
message(STATUS "  Build:    cmake --build build")
message(STATUS "  Run demo: cmake --build build --target run_demo")
message(STATUS "  Manual:   PYTHONPATH=build python3 demo.py")
message(STATUS "")
