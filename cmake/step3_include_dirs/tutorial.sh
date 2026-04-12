#!/bin/bash
# =============================================================================
# tutorial.sh — Step 3: Include Directories
# Covers target_include_directories, PRIVATE/PUBLIC/INTERFACE, and
# why the visibility keyword matters for library users.
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
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 3 — Include Directories: PRIVATE / PUBLIC / INTERFACE")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

# ── Goal ─────────────────────────────────────────────────────────────────────
p_section "Goal of This Step"

p_info "Real projects separate headers from source files."
p_info "You need to tell CMake where to find headers — and WHICH targets"
p_info "should be allowed to see them."
p_info "That is what PRIVATE, PUBLIC, and INTERFACE control."

# ── Project structure ─────────────────────────────────────────────────────────
p_section "Project Structure"

p_box "  step3_include_dirs/"
p_box "  ├── CMakeLists.txt"
p_box "  ├── include/"
p_box "  │   └── string_utils.h    ← header lives here"
p_box "  └── src/"
p_box "      ├── main.c            ← includes string_utils.h"
p_box "      └── string_utils.c    ← implementation"
p_info ""
p_info "Without telling CMake where 'include/' is, #include \"string_utils.h\""
p_info "would fail — the compiler doesn't know to look there."

# ── CMakeLists.txt ────────────────────────────────────────────────────────────
p_section "CMakeLists.txt — Line by Line"

echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""

# ── The -I flag ───────────────────────────────────────────────────────────────
p_section "What target_include_directories Actually Does"

p_info "target_include_directories(strtools PRIVATE include)"
p_info "adds a -I flag to the compile command:"
p_info ""
p_box "  gcc -Iinclude -c src/main.c -o main.c.o"
p_box "       ^^^^^^^^"
p_box "       tells the compiler: 'also look in include/ for header files'"
p_info ""
p_info "Without it, the compiler only searches the system include paths"
p_info "(/usr/include, /usr/local/include) and the current directory."

# ── PRIVATE vs PUBLIC vs INTERFACE ────────────────────────────────────────────
p_section "Understanding PRIVATE / PUBLIC / INTERFACE"

p_info "These keywords control PROPAGATION — who else gets this -I path."
p_info ""
p_info "Imagine three targets: strtools (executable) and a hypothetical"
p_info "libA (library). strtools links libA."
p_info ""
p_box "  ┌─────────────────────────────────────────────────────────────┐"
p_box "  │ PRIVATE                                                     │"
p_box "  │   target_include_directories(libA PRIVATE include/)         │"
p_box "  │                                                             │"
p_box "  │   libA's sources get -Iinclude/                             │"
p_box "  │   strtools does NOT get -Iinclude/                          │"
p_box "  │                                                             │"
p_box "  │   Use when: headers are internal implementation details.    │"
p_box "  │   Callers of libA don't #include any of libA's headers.     │"
p_box "  └─────────────────────────────────────────────────────────────┘"
p_info ""
p_box "  ┌─────────────────────────────────────────────────────────────┐"
p_box "  │ PUBLIC                                                      │"
p_box "  │   target_include_directories(libA PUBLIC include/)          │"
p_box "  │                                                             │"
p_box "  │   libA's sources get -Iinclude/                             │"
p_box "  │   strtools ALSO gets -Iinclude/ automatically               │"
p_box "  │                                                             │"
p_box "  │   Use when: headers form part of libA's public API.         │"
p_box "  │   Callers need them to compile code that uses libA.         │"
p_box "  └─────────────────────────────────────────────────────────────┘"
p_info ""
p_box "  ┌─────────────────────────────────────────────────────────────┐"
p_box "  │ INTERFACE                                                   │"
p_box "  │   target_include_directories(libA INTERFACE include/)       │"
p_box "  │                                                             │"
p_box "  │   libA's sources do NOT get -Iinclude/                      │"
p_box "  │   strtools gets -Iinclude/ automatically                    │"
p_box "  │                                                             │"
p_box "  │   Use when: libA is header-only (nothing to compile).       │"
p_box "  │   The 'library' is just headers; only consumers need them.  │"
p_box "  └─────────────────────────────────────────────────────────────┘"
p_info ""
p_info "Rule of thumb:"
p_info "  executable        → always PRIVATE (nothing links to an executable)"
p_info "  compiled library  → PRIVATE for internal headers, PUBLIC for API headers"
p_info "  header-only lib   → INTERFACE for all headers"

# ── Build and run ─────────────────────────────────────────────────────────────
p_section "Build and Run"

cd "$STEP_DIR"
rm -rf build

cmake -S . -B build 2>&1 | tail -3
cmake --build build 2>&1

p_info ""
p_cmd "./build/strtools"
echo ""
./build/strtools

# ── See the -I flag in the compile command ────────────────────────────────────
p_section "See the -I Flag in Action"

p_info "Rebuild with --verbose to see the -Iinclude flag:"
p_info ""
cmake --build build --verbose 2>&1 | grep "\-I"
p_info ""
p_info "You can see -Iinclude in the gcc invocation."

# ── Use a different compiler ──────────────────────────────────────────────────
p_section "Bonus: Use Clang Instead of GCC"

if command -v clang &>/dev/null; then
    cmake -S . -B build_clang -DCMAKE_C_COMPILER=clang 2>&1 | tail -3
    cmake --build build_clang 2>&1
    p_ok "Built successfully with Clang"
    ./build_clang/strtools | head -3
    rm -rf build_clang
else
    p_info "Clang is not installed. To try it:"
    p_cmd "sudo apt install clang"
    p_cmd "cmake -S . -B build_clang -DCMAKE_C_COMPILER=clang"
    p_cmd "cmake --build build_clang"
    p_info ""
    p_info "The same CMakeLists.txt works with any C compiler."
fi

# ── compile_commands.json ─────────────────────────────────────────────────────
p_section "Bonus: compile_commands.json (IDE / Linter Support)"

p_info "Generate a compilation database for editors like VS Code:"
p_info ""
p_cmd "cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON 2>&1 | tail -2
p_info ""
p_info "build/compile_commands.json now contains:"
python3 -c "import json; d=json.load(open('build/compile_commands.json')); print(json.dumps(d, indent=2))" 2>/dev/null || \
  cat build/compile_commands.json
p_info ""
p_info "Editors (clangd, VS Code C/C++ extension) read this file to know"
p_info "which include paths apply to each file — enabling accurate IntelliSense."

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 3 Summary"

p_ok "target_include_directories() adds -I<path> to the compile command"
p_ok "PRIVATE  = only this target gets the path"
p_ok "PUBLIC   = this target + all targets that link to it"
p_ok "INTERFACE = only those who link to it (header-only libraries)"
p_ok "Executables always use PRIVATE (nothing can link to them)"
p_ok "CMAKE_EXPORT_COMPILE_COMMANDS=ON generates compile_commands.json for IDEs"
echo ""
p_info "Next: cd ../step4_libraries && bash tutorial.sh"
echo ""
