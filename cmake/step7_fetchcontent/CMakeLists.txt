cmake_minimum_required(VERSION 3.15)
project(FetchDemo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Loads FetchContent_Declare() and FetchContent_MakeAvailable() commands.
# No download happens here.
include(FetchContent)

# ── nlohmann/json ──────────────────────────────────────────────────────────────

# Registers a dependency. Nothing is downloaded yet.
# GIT_TAG: pin to a tag or SHA (never a branch) for reproducible builds.
# GIT_SHALLOW TRUE: clone only the tagged commit — skips full history.
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
    GIT_SHALLOW    TRUE
)

# ── {fmt} ──────────────────────────────────────────────────────────────────────

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        10.2.1
    GIT_SHALLOW    TRUE
)

# Downloads (first run only) and calls add_subdirectory() on each dependency.
# Result targets:
#   nlohmann_json::nlohmann_json — header-only
#   fmt::fmt                     — compiled library
# The :: namespace signals an external package; CMake errors if the target
# doesn't exist (unlike a plain name like "fmt", silently treated as -lfmt).
FetchContent_MakeAvailable(nlohmann_json fmt)

add_executable(fetchapp main.cpp)

# nlohmann_json::nlohmann_json — adds include dir only (header-only, no .a/.so)
# fmt::fmt                     — adds -lfmt and fmt's include dir
target_link_libraries(fetchapp PRIVATE
    nlohmann_json::nlohmann_json
    fmt::fmt
)
