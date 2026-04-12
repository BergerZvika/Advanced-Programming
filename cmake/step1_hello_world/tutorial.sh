#!/bin/bash
# =============================================================================
# tutorial.sh — Step 1: Hello World
# Walks through every line of the 5-line CMakeLists.txt, then runs the
# full configure → build → run cycle with explanations at each stage.
# =============================================================================

set -euo pipefail

YELLOW='\033[1;33m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
BLUE='\033[0;34m'
BOLD='\033[1m'
RESET='\033[0m'

STEP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

p_section() { echo -e "\n${YELLOW}=== $1 ===${RESET}"; }
p_info()    { echo -e "  ${CYAN}$1${RESET}"; }
p_cmd()     { echo -e "  ${GREEN}\$ $1${RESET}"; }
p_ok()      { echo -e "  ${GREEN}✔  $1${RESET}"; }
p_box()     { echo -e "  ${BLUE}$1${RESET}"; }
p_run()     { echo -e "  ${GREEN}\$ $1${RESET}"; eval "$1"; }

echo ""
echo -e "${CYAN}╔══════════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 1 — Hello World: Minimum CMakeLists.txt")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

# ── Goal ─────────────────────────────────────────────────────────────────────
p_section "Goal of This Step"

p_info "Compile a single C file into an executable using the smallest"
p_info "possible CMakeLists.txt. Understand every line of it, and"
p_info "run through the full configure → build → run cycle."

# ── The source file ───────────────────────────────────────────────────────────
p_section "The Source File: main.c"

p_info "This is what we want to compile:"
echo ""
cat "$STEP_DIR/main.c"
echo ""

# ── Read the CMakeLists.txt line by line ──────────────────────────────────────
p_section "CMakeLists.txt — Line by Line"

p_info "The complete CMakeLists.txt is only 3 lines of actual code:"
echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""

p_info "Line 1 — cmake_minimum_required(VERSION 3.15)"
p_box "  ┌──────────────────────────────────────────────────────────────┐"
p_box "  │ This MUST be the very first line of every CMakeLists.txt.   │"
p_box "  │ It tells CMake the oldest version this file was written for. │"
p_box "  │ If someone tries to build with an older CMake, they get a   │"
p_box "  │ clear error message instead of mysterious failures.          │"
p_box "  │                                                              │"
p_box "  │ Why 3.15?                                                    │"
p_box "  │   3.15 introduced the -S/-B syntax we use everywhere.       │"
p_box "  │   It is a safe baseline for almost all modern Linux systems. │"
p_box "  └──────────────────────────────────────────────────────────────┘"
p_info ""
p_info "Line 2 — project(HelloWorld C)"
p_box "  ┌──────────────────────────────────────────────────────────────┐"
p_box "  │ Names the project 'HelloWorld' and says we use C only.      │"
p_box "  │                                                              │"
p_box "  │ CMake uses this to:                                          │"
p_box "  │   • Set CMAKE_PROJECT_NAME = 'HelloWorld'                   │"
p_box "  │   • Detect the C compiler (gcc/clang/cl)                    │"
p_box "  │   • Skip C++ detection entirely (no g++ required)           │"
p_box "  │                                                              │"
p_box "  │ If you omit the language list, CMake enables C AND C++.     │"
p_box "  │ Always list only what you actually use — faster configure.  │"
p_box "  └──────────────────────────────────────────────────────────────┘"
p_info ""
p_info "Line 3 — add_executable(hello main.c)"
p_box "  ┌──────────────────────────────────────────────────────────────┐"
p_box "  │ Creates a BUILD TARGET named 'hello' from 'main.c'.         │"
p_box "  │                                                              │"
p_box "  │ 'hello' is:                                                  │"
p_box "  │   • The logical name used in other cmake commands           │"
p_box "  │   • The output binary name:                                  │"
p_box "  │       Linux/macOS : build/hello                             │"
p_box "  │       Windows     : build/hello.exe                         │"
p_box "  │                                                              │"
p_box "  │ CMake automatically:                                         │"
p_box "  │   1. Compiles main.c → main.c.o                             │"
p_box "  │   2. Links main.c.o → hello                                 │"
p_box "  └──────────────────────────────────────────────────────────────┘"

# ── Phase 1: Configure ────────────────────────────────────────────────────────
p_section "Phase 1: Configure"

p_info "The configure phase reads CMakeLists.txt and GENERATES build files."
p_info "Run this from the step directory:"
p_info ""
p_cmd "cmake -S . -B build"
p_info ""
p_info "What each flag means:"
p_info "  -S .      → Source: use CMakeLists.txt in the current directory"
p_info "  -B build  → Build: put all generated files in ./build/"
p_info "              (created automatically if it doesn't exist)"
p_info ""
p_info "Running it now:"
echo ""

cd "$STEP_DIR"
rm -rf build
cmake -S . -B build 2>&1

p_info ""
p_info "What CMake just created in build/:"
p_box "  build/"
p_box "  ├── CMakeCache.txt        ← your settings, persisted for next run"
p_box "  ├── CMakeFiles/           ← compiler detection results, object rules"
p_box "  ├── Makefile              ← the real build file (or build.ninja)"
p_box "  └── cmake_install.cmake   ← install rules (used in step 9)"

# ── Phase 2: Build ────────────────────────────────────────────────────────────
p_section "Phase 2: Build"

p_info "The build phase invokes the real build tool (make/ninja) to compile."
p_info ""
p_cmd "cmake --build build"
p_info ""
p_info "Why use 'cmake --build' instead of 'make'?"
p_info "  cmake --build is generator-independent. The same command works"
p_info "  whether the generator is Make, Ninja, Xcode, or Visual Studio."
p_info ""
p_info "Running it now:"
echo ""

cmake --build build 2>&1

p_info ""
p_ok "build/hello was created"
ls -lh build/hello

# ── Verbose: see the actual compiler command ───────────────────────────────────
p_section "What the Compiler Actually Ran (--verbose)"

p_info "Add --verbose to see the exact gcc command CMake generated:"
p_info ""
p_cmd "cmake --build build --verbose"
p_info ""
cmake --build build --verbose 2>&1
p_info ""
p_info "You can see the full gcc invocation including all flags CMake added."

# ── Phase 3: Run ─────────────────────────────────────────────────────────────
p_section "Phase 3: Run the Executable"

p_cmd "./build/hello"
echo ""
./build/hello

# ── Try different build types ─────────────────────────────────────────────────
p_section "Experiment: Debug vs Release Build"

p_info "Let's compare what Debug and Release do to the binary:"
p_info ""

cmake -S . -B build_debug   -DCMAKE_BUILD_TYPE=Debug   2>&1 | tail -3
cmake -S . -B build_release -DCMAKE_BUILD_TYPE=Release 2>&1 | tail -3
cmake --build build_debug   --verbose 2>&1 | grep -oE "\-g|\-O[0-9s]" | sort -u | tr '\n' ' '
echo ""
cmake --build build_release --verbose 2>&1 | grep -oE "\-g|\-O[0-9s]" | sort -u | tr '\n' ' '
echo ""

p_info ""
p_info "Debug flags:   -g (debug symbols) -O0 (no optimisation)"
p_info "Release flags: -O3 (maximum speed) -DNDEBUG (disables assert())"
p_info ""
ls -lh build_debug/hello build_release/hello
p_info ""
p_info "The Debug binary is larger because it contains symbol information."

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build build_debug build_release

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 1 Summary"

p_ok "cmake_minimum_required(VERSION 3.15) — always first, sets CMake policy"
p_ok "project(HelloWorld C) — names project, enables C compiler detection"
p_ok "add_executable(hello main.c) — defines a build target"
p_ok "cmake -S . -B build — configure: read CMakeLists.txt, generate Makefile"
p_ok "cmake --build build — build: compile and link"
p_ok "cmake --build build --verbose — see the exact compiler command"
p_ok "-DCMAKE_BUILD_TYPE=Debug/Release — control optimisation and debug symbols"
echo ""
p_info "Next: cd ../step2_multiple_files && bash tutorial.sh"
echo ""
