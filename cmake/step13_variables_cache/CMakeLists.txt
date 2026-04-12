cmake_minimum_required(VERSION 3.15)
project(VariablesDemo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Regular variables ─────────────────────────────────────────────────────────
# Visible in this file and in subdirectories. Variables do NOT flow upward.
set(MY_SOURCES main.cpp)
# set(APP_GREETING "Hello from CMake variables!")

# ── Cache variables ───────────────────────────────────────────────────────────
# Stored in CMakeCache.txt; survive between cmake runs.
# Override with: cmake -D<name>=<value>
# Types: STRING, BOOL, PATH, FILEPATH, INTERNAL (hidden in cmake-gui)
set(GREETING_REPEAT 5 CACHE STRING "How many times to print the greeting")
set(SHOW_ENV_INFO   ON CACHE BOOL   "Print environment information at runtime")

# ── option() is shorthand for BOOL cache variable ─────────────────────────────
# option(FOO "desc" ON)  ≡  set(FOO ON CACHE BOOL "desc")
option(ENABLE_FEATURE_X "Enable experimental feature X" OFF)

# ── Conditional logic ─────────────────────────────────────────────────────────
if(ENABLE_FEATURE_X)
    message(STATUS "Feature X is ENABLED — adding extra source")
    list(APPEND MY_SOURCES feature_x.cpp)
endif()

# ── String operations ─────────────────────────────────────────────────────────
# string() supports TOUPPER, TOLOWER, LENGTH, REPLACE, REGEX MATCH/REPLACE, etc.
string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)
string(LENGTH  "${APP_GREETING}" GREETING_LENGTH)

# ── Useful built-in variables ─────────────────────────────────────────────────
# CMAKE_SOURCE_DIR / CMAKE_BINARY_DIR       — top-level dirs, never change
# CMAKE_CURRENT_SOURCE_DIR / _BINARY_DIR    — current CMakeLists.txt's dirs
# PROJECT_NAME, PROJECT_SOURCE_DIR          — from the nearest project() call
# CMAKE_BUILD_TYPE                          — Debug, Release, etc.
# CMAKE_SYSTEM_NAME / CMAKE_HOST_SYSTEM_NAME — Linux, Darwin, Windows

message(STATUS "Project name         : ${PROJECT_NAME}")
message(STATUS "Project name (upper) : ${PROJECT_NAME_UPPER}")
message(STATUS "Source dir           : ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Build dir            : ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "System               : ${CMAKE_SYSTEM_NAME}")
message(STATUS "Greeting             : ${APP_GREETING} (${GREETING_LENGTH} chars)")
message(STATUS "Repeat               : ${GREETING_REPEAT}")
message(STATUS "Feature X            : ${ENABLE_FEATURE_X}")

# ── Platform detection ────────────────────────────────────────────────────────
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Platform: Linux")
    set(PLATFORM_DEFINE "PLATFORM_LINUX=1")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Platform: macOS")
    set(PLATFORM_DEFINE "PLATFORM_MACOS=1")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Platform: Windows")
    set(PLATFORM_DEFINE "PLATFORM_WINDOWS=1")
else()
    message(STATUS "Platform: ${CMAKE_SYSTEM_NAME} (unknown)")
    set(PLATFORM_DEFINE "PLATFORM_UNKNOWN=1")
endif()

# ── Compiler detection ────────────────────────────────────────────────────────
# CMAKE_CXX_COMPILER_ID: "GNU", "Clang", "AppleClang", "MSVC", "Intel"
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
    set(COMPILER_DEFINE "COMPILER_GCC_CLANG=1")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Compiler: MSVC ${CMAKE_CXX_COMPILER_VERSION}")
    set(COMPILER_DEFINE "COMPILER_MSVC=1")
endif()

# ── Build the executable ──────────────────────────────────────────────────────
add_executable(varsdemo ${MY_SOURCES})

target_compile_definitions(varsdemo PRIVATE
    APP_GREETING="${APP_GREETING}"
    GREETING_REPEAT=${GREETING_REPEAT}
    ${PLATFORM_DEFINE}
    ${COMPILER_DEFINE}
    $<$<BOOL:${SHOW_ENV_INFO}>:SHOW_ENV_INFO=1>
)

message(STATUS "")
message(STATUS "=== Step 13: Variables & Cache ===")
message(STATUS "  Build:  cmake --build build")
message(STATUS "  Run:    ./build/varsdemo")
message(STATUS "")
