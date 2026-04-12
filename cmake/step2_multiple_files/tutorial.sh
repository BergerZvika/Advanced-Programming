#!/bin/bash
# =============================================================================
# tutorial.sh — Step 2: Multiple Source Files
# Covers listing multiple .c files, why explicit lists beat file(GLOB),
# and how to inspect what CMake compiled.
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

echo ""
echo -e "${CYAN}╔══════════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 2 — Multiple Source Files")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

# ── Goal ─────────────────────────────────────────────────────────────────────
p_section "Goal of This Step"

p_info "Most real programs have more than one .c file."
p_info "Learn how to list multiple source files, how CMake compiles each"
p_info "one separately, and why you should list files explicitly."

# ── Project structure ─────────────────────────────────────────────────────────
p_section "Project Structure"

p_box "  step2_multiple_files/"
p_box "  ├── CMakeLists.txt"
p_box "  ├── main.c           ← entry point"
p_box "  ├── math_utils.c     ← implementation"
p_box "  └── math_utils.h     ← header (declarations)"
p_info ""
p_info "The files:"
echo ""
echo "--- main.c ---"
cat "$STEP_DIR/main.c"
echo ""
echo "--- math_utils.h ---"
cat "$STEP_DIR/math_utils.h"

# ── CMakeLists.txt ────────────────────────────────────────────────────────────
p_section "CMakeLists.txt — Line by Line"

echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""

p_info "The key change from step 1:"
p_info ""
p_info "  add_executable(calculator"
p_info "      main.c"
p_info "      math_utils.c"
p_info "  )"
p_info ""
p_info "You simply LIST all the .c files that belong to the target."
p_info "CMake will compile each one separately and then link them together."

# ── How compilation works ─────────────────────────────────────────────────────
p_section "How Multi-File Compilation Works"

p_box "  Source files      Compiled separately        Linked together"
p_box ""
p_box "  main.c       ──→  main.c.o    ─┐"
p_box "  math_utils.c ──→  math_utils.c.o ─┤ linker ──→  calculator"
p_box ""
p_info "Each .c file is an independent TRANSLATION UNIT."
p_info "CMake compiles them in parallel (with -j) because they don't"
p_info "depend on each other — then the linker combines the .o files."
p_info ""
p_info "This is why headers use #ifndef guards / #pragma once:"
p_info "the same header can be included in many .c files without the"
p_info "compiler seeing duplicate definitions in the final link."

# ── Why not file(GLOB)? ───────────────────────────────────────────────────────
p_section "Why NOT file(GLOB)?"

p_info "You might wonder: why not just say 'compile all .c files'?"
p_info ""
p_info "CMake does have a GLOB command:"
p_box '  file(GLOB SOURCES "*.c")          # ← AVOID THIS'
p_box '  add_executable(calculator ${SOURCES})'
p_info ""
p_info "The problem: GLOB is evaluated at CONFIGURE time, not BUILD time."
p_info ""
p_info "Scenario:"
p_box "  1. You run cmake -S . -B build    → GLOB finds main.c, math_utils.c"
p_box "  2. You add a new file: trig.c"
p_box "  3. You run cmake --build build"
p_box "  4. trig.c is IGNORED — cmake was never re-run!"
p_info ""
p_info "With explicit lists, adding a file to CMakeLists.txt forces"
p_info "cmake to re-run because CMakeLists.txt changed. CMake always"
p_info "tracks its own file as a dependency."

# ── Build and run ─────────────────────────────────────────────────────────────
p_section "Build and Run"

cd "$STEP_DIR"
rm -rf build

p_cmd "cmake -S . -B build"
cmake -S . -B build 2>&1 | tail -3

p_info ""
p_cmd "cmake --build build -j4"
p_info "  -j4 = compile up to 4 files in parallel (faster on multi-core)"
cmake --build build -j4 2>&1

p_info ""
p_cmd "./build/calculator"
echo ""
./build/calculator

# ── Inspect what CMake compiled ───────────────────────────────────────────────
p_section "Inspect: See What Was Compiled (--verbose)"

p_info "Use --verbose to see both compile commands:"
p_info ""
cmake --build build --verbose 2>&1

p_info ""
p_info "You can see two separate gcc calls:"
p_info "  1. gcc ... -c main.c       → produces main.c.o"
p_info "  2. gcc ... -c math_utils.c → produces math_utils.c.o"
p_info "  3. gcc ... main.c.o math_utils.c.o -o calculator"

# ── Inspect CMake cache ────────────────────────────────────────────────────────
p_section "Inspect the CMake Cache"

p_info "List what CMake discovered and stored in CMakeCache.txt:"
p_info ""
p_cmd "cmake -S . -B build -L"
p_info ""
cmake -S . -B build -L 2>&1 | grep -E "^(CMAKE_BUILD_TYPE|CMAKE_C_COMPILER|CMAKE_INSTALL)" || true

p_info ""
p_info "These settings persist. If you run cmake again without -D flags,"
p_info "it uses the cached values."

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 2 Summary"

p_ok "List all .c files explicitly in add_executable()"
p_ok "CMake compiles each file separately into a .o object, then links them"
p_ok "Never use file(GLOB) — new files get missed until you re-run cmake"
p_ok "cmake --build build -j4 — parallel build (use number of CPU cores)"
p_ok "cmake --build build --verbose — see the exact gcc commands"
p_ok "cmake -S . -B build -L — list cached settings"
echo ""
p_info "Next: cd ../step3_include_dirs && bash tutorial.sh"
echo ""
