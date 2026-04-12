#!/bin/bash
# =============================================================================
# cmake_intro.sh
# Step 0 — What is CMake? Why does it exist? The three-phase build cycle,
# generators, out-of-source builds, and how the pieces fit together.
# Run this BEFORE step 1. No compiler required.
# =============================================================================

set -euo pipefail

YELLOW='\033[1;33m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
BLUE='\033[0;34m'
BOLD='\033[1m'
RESET='\033[0m'

p_section() { echo -e "\n${YELLOW}=== $1 ===${RESET}"; }
p_info()    { echo -e "  ${CYAN}$1${RESET}"; }
p_cmd()     { echo -e "  ${GREEN}\$ $1${RESET}"; }
p_ok()      { echo -e "  ${GREEN}✔  $1${RESET}"; }
p_box()     { echo -e "  ${BLUE}$1${RESET}"; }

echo ""
echo -e "${CYAN}╔══════════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 0 — CMake Concepts: What, Why, and How")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

# ── What is CMake? ────────────────────────────────────────────────────────────
p_section "What is CMake?"

p_info "CMake is a BUILD SYSTEM GENERATOR."
p_info ""
p_info "It does NOT compile your code directly."
p_info "Instead it reads your CMakeLists.txt and GENERATES the files"
p_info "that a real build tool (Make, Ninja, Xcode, Visual Studio) needs."
p_info ""
p_info "You describe WHAT you want to build (targets, sources, dependencies)."
p_info "CMake figures out HOW to build it on any platform."

# ── The problem CMake solves ──────────────────────────────────────────────────
p_section "The Problem CMake Solves"

p_info "Before CMake, building C/C++ across platforms was painful:"
p_info ""
p_box "  Linux:   write a Makefile"
p_box "  macOS:   write a different Makefile (or Xcode project)"
p_box "  Windows: write a Visual Studio .sln / .vcxproj"
p_box "           (and keep all three in sync manually)"
p_info ""
p_info "CMake replaces all three. You write ONE CMakeLists.txt."
p_info "CMake generates the right files for each platform automatically."

# ── The three phases ──────────────────────────────────────────────────────────
p_section "The Three Phases of a CMake Build"

p_info "Every CMake project has exactly three phases:"
p_info ""
p_box "  ┌─────────────────────────────────────────────────────────────┐"
p_box "  │  Phase 1: CONFIGURE                                         │"
p_box "  │  cmake -S . -B build                                        │"
p_box "  │                                                             │"
p_box "  │  CMake reads CMakeLists.txt, detects your compiler,         │"
p_box "  │  resolves all targets and dependencies, and GENERATES       │"
p_box "  │  the build files (Makefile / build.ninja / .sln etc.)       │"
p_box "  │  in the build/ directory.                                   │"
p_box "  │                                                             │"
p_box "  │  Result: build/Makefile (or build/build.ninja)             │"
p_box "  │          build/CMakeCache.txt  ← stores your settings      │"
p_box "  └─────────────────────────────────────────────────────────────┘"
p_info ""
p_box "  ┌─────────────────────────────────────────────────────────────┐"
p_box "  │  Phase 2: BUILD                                             │"
p_box "  │  cmake --build build                                        │"
p_box "  │                                                             │"
p_box "  │  Invokes the real build tool (make/ninja) to compile        │"
p_box "  │  your source files and link your targets.                   │"
p_box "  │                                                             │"
p_box "  │  Result: build/hello  (or build/libmylib.a etc.)           │"
p_box "  └─────────────────────────────────────────────────────────────┘"
p_info ""
p_box "  ┌─────────────────────────────────────────────────────────────┐"
p_box "  │  Phase 3: INSTALL  (optional)                               │"
p_box "  │  cmake --install build                                      │"
p_box "  │                                                             │"
p_box "  │  Copies binaries, headers, and libraries to the install     │"
p_box "  │  prefix (/usr/local or a path you choose).                  │"
p_box "  └─────────────────────────────────────────────────────────────┘"
p_info ""
p_info "You almost always run phases 1 and 2."
p_info "Phase 1 only needs to run once (or when CMakeLists.txt changes)."
p_info "Phase 2 re-runs every time you change source code."

# ── Out-of-source builds ──────────────────────────────────────────────────────
p_section "Out-of-Source Builds (The Most Important Habit)"

p_info "NEVER do this:"
p_cmd "cd myproject && cmake .   # ← BAD: scatters build files in source tree"
p_info ""
p_info "ALWAYS do this:"
p_cmd "cmake -S . -B build       # ← GOOD: all generated files go into build/"
p_info ""
p_info "  -S .      = Source directory (where CMakeLists.txt lives)"
p_info "  -B build  = Build directory (created automatically if missing)"
p_info ""
p_info "Why out-of-source?"
p_info "  • Your source tree stays clean — git status shows only your code"
p_info "  • You can have multiple build dirs at once:"
p_cmd "    cmake -S . -B build_debug   -DCMAKE_BUILD_TYPE=Debug"
p_cmd "    cmake -S . -B build_release -DCMAKE_BUILD_TYPE=Release"
p_cmd "    cmake -S . -B build_clang   -DCMAKE_C_COMPILER=clang"
p_info "  • To start fresh: just delete build/ and re-run configure"

# ── Generators ────────────────────────────────────────────────────────────────
p_section "Generators — What CMake Generates"

p_info "A 'generator' is the build system CMake produces files for."
p_info ""
p_info "Common generators:"
p_info ""
p_box "  Generator              Platform      Build command"
p_box "  ─────────────────────────────────────────────────────────────"
p_box "  Unix Makefiles         Linux/macOS   make"
p_box "  Ninja                  All           ninja  (faster than make)"
p_box "  Visual Studio 17 2022  Windows       msbuild / VS IDE"
p_box "  Xcode                  macOS         xcodebuild / Xcode IDE"
p_box "  Ninja Multi-Config     All           ninja (Debug+Release same dir)"
p_info ""
p_info "The default on Linux is 'Unix Makefiles'."
p_info "Ninja is generally faster and is the preferred generator for CI."
p_info ""
p_cmd "cmake -S . -B build -G Ninja         # use Ninja"
p_cmd "cmake -S . -B build -G 'Unix Makefiles'  # use Make explicitly"
p_cmd "cmake --help                          # list generators available on YOUR machine"

# ── CMakeCache.txt ────────────────────────────────────────────────────────────
p_section "CMakeCache.txt — The Settings File"

p_info "After configure, build/CMakeCache.txt stores every setting CMake detected"
p_info "or that you passed with -D:"
p_info ""
p_box "  CMAKE_BUILD_TYPE          = Debug"
p_box "  CMAKE_C_COMPILER          = /usr/bin/gcc"
p_box "  CMAKE_CXX_COMPILER        = /usr/bin/g++"
p_box "  CMAKE_INSTALL_PREFIX      = /usr/local"
p_box "  ... (hundreds more)"
p_info ""
p_info "Settings in the cache PERSIST between cmake runs on the same build dir."
p_info "You only need to pass -DCMAKE_BUILD_TYPE=Debug ONCE; it's remembered."
p_info ""
p_info "When to delete the cache:"
p_info "  • Changing compilers"
p_info "  • Changing generators"
p_info "  • Something seems wrong and you want a clean start"
p_cmd "rm -rf build/          # clean everything"
p_cmd "cmake -S . -B build --fresh  # reconfigure, deleting old cache"

# ── What is CMakeLists.txt? ───────────────────────────────────────────────────
p_section "What Is CMakeLists.txt?"

p_info "CMakeLists.txt is the recipe file CMake reads during configure."
p_info "It's a simple script written in CMake's own language."
p_info ""
p_info "The three most important commands you'll use every time:"
p_info ""
p_box "  cmake_minimum_required(VERSION 3.15)"
p_box "    → Declare the minimum CMake version your project needs."
p_box "      Always the FIRST line."
p_info ""
p_box "  project(MyApp C CXX)"
p_box "    → Name the project and declare which languages are used."
p_box "      Always the SECOND line."
p_info ""
p_box "  add_executable(myapp main.c)"
p_box "    → Define a build target: compile main.c into an executable."
p_info ""
p_info "That's it for a hello world. Everything else builds on these three."

# ── The target model ──────────────────────────────────────────────────────────
p_section "The Target Model (Core Concept)"

p_info "CMake organises everything around TARGETS."
p_info "A target is a named thing to build:"
p_info ""
p_box "  add_executable(myapp main.c)        → target named 'myapp'"
p_box "  add_library(mylib STATIC utils.c)   → target named 'mylib'"
p_box "  add_custom_target(docs ...)         → target named 'docs'"
p_info ""
p_info "Targets have PROPERTIES:"
p_box "  Sources, include dirs, compile flags, link libraries, ..."
p_info ""
p_info "Properties are attached with target_*() commands:"
p_box "  target_include_directories(myapp PRIVATE include/)"
p_box "  target_compile_options(myapp PRIVATE -Wall -Wextra)"
p_box "  target_link_libraries(myapp PRIVATE mylib)"
p_info ""
p_info "PRIVATE/PUBLIC/INTERFACE controls WHO inherits the property:"
p_box "  PRIVATE   = only this target"
p_box "  PUBLIC    = this target + anyone who links to it"
p_box "  INTERFACE = only those who link to it (not this target itself)"

# ── Build types ───────────────────────────────────────────────────────────────
p_section "Build Types (Debug vs Release)"

p_info "The CMAKE_BUILD_TYPE variable controls compiler optimisation and debug info:"
p_info ""
p_box "  Build Type       Compiler Flags      Use When"
p_box "  ──────────────────────────────────────────────────────────"
p_box "  Debug            -g -O0              Development, debugging"
p_box "  Release          -O3 -DNDEBUG        Production, distribution"
p_box "  RelWithDebInfo   -O2 -g              Profile in production"
p_box "  MinSizeRel       -Os -DNDEBUG        Embedded, minimal size"
p_info ""
p_cmd "cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug"
p_cmd "cmake -S . -B build -DCMAKE_BUILD_TYPE=Release"
p_info ""
p_info "Note: single-config generators (Make/Ninja) use CMAKE_BUILD_TYPE."
p_info "Multi-config generators (Visual Studio/Xcode) select the type at BUILD time:"
p_cmd "cmake --build build --config Release   # Visual Studio"

# ── Learning path ─────────────────────────────────────────────────────────────
p_section "Tutorial Learning Path"

p_info "This tutorial has 15 steps. Run each tutorial.sh script to learn."
p_info "Each step also has a working CMakeLists.txt you can inspect and run."
p_info ""
p_box "  Step 0  (this file)     CMake concepts & the build cycle"
p_box "  Step 1                  Hello World — minimum CMakeLists.txt"
p_box "  Step 2                  Multiple source files"
p_box "  Step 3                  Include directories (PRIVATE/PUBLIC/INTERFACE)"
p_box "  Step 4                  Libraries (STATIC, SHARED, add_subdirectory)"
p_box "  Step 5                  Mixed C and C++"
p_box "  Step 6                  Modular project (multi-level subdirectories)"
p_box "  Step 7                  FetchContent (external dependencies)"
p_box "  Step 8                  Testing (CTest + Catch2)"
p_box "  Step 9                  Install rules (cmake --install)"
p_box "  Step 10                 C++ + Python via pybind11"
p_box "  Step 11                 C++ + Java via JNI"
p_box "  Step 12  (NEW)          Compiler flags, warnings, and defines"
p_box "  Step 13  (NEW)          Variables, cache, option(), if/else"
p_box "  Step 14  (NEW)          configure_file() — generated headers"

p_section "Step 0 Complete"
p_ok "You understand what CMake is (a build system generator, not a compiler)"
p_ok "You know the three phases: configure → build → install"
p_ok "You know why out-of-source builds matter"
p_ok "You understand generators, CMakeCache.txt, and build types"
p_ok "You understand the target model and PRIVATE/PUBLIC/INTERFACE"
echo ""
p_info "Next: cd ../step1_hello_world && bash tutorial.sh"
echo ""
