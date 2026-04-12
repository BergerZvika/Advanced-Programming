#!/bin/bash
# =============================================================================
# tutorial.sh — Step 5: Mixed C and C++
# Covers declaring multiple languages, C/C++ standards, EXTENSIONS OFF,
# and extern "C" for C/C++ interoperability.
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
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 5 — Mixed C and C++: Standards, Extensions, Interop")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

# ── Goal ─────────────────────────────────────────────────────────────────────
p_section "Goal of This Step"

p_info "Many projects mix C and C++: fast C math routines called from C++."
p_info "Learn how CMake handles two languages, how to request a specific"
p_info "standard (C11, C++17), and why CMAKE_CXX_EXTENSIONS OFF matters."

# ── How CMake picks the compiler per file ──────────────────────────────────────
p_section "How CMake Picks the Compiler Per File"

p_info "CMake uses file extensions to decide which compiler to use:"
p_info ""
p_box "  Extension    Compiler"
p_box "  ─────────────────────────────────────────────────"
p_box "  .c           C compiler   (gcc / clang)"
p_box "  .cpp .cxx    C++ compiler (g++ / clang++)"
p_box "  .f .f90      Fortran compiler"
p_box "  .cu          CUDA compiler (nvcc)"
p_info ""
p_info "In step 5 we have:"
p_box "  main.cpp         → compiled by g++"
p_box "  cmath_bridge.c   → compiled by gcc"
p_box "  cpp_analysis.cpp → compiled by g++"
p_info ""
p_info "All their .o files are linked together by the C++ linker (g++),"
p_info "which knows how to handle both C and C++ object files."

# ── CMakeLists.txt ────────────────────────────────────────────────────────────
p_section "CMakeLists.txt — Language Standards"

echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""

p_info "project(MultiLang C CXX)"
p_box "  Declares both C and C++ languages."
p_box "  CMake will detect both gcc AND g++."
p_info ""

p_info "set(CMAKE_C_STANDARD 11)"
p_info "set(CMAKE_C_STANDARD_REQUIRED ON)"
p_box "  Requests C11 for all C files."
p_box "  The 'REQUIRED ON' means: if the compiler can't do C11, error out."
p_box "  Without REQUIRED, CMake might silently fall back to C99."
p_box "  C11 adds: _Generic, _Alignas, atomics, anonymous structs."
p_info ""

p_info "set(CMAKE_CXX_STANDARD 17)"
p_info "set(CMAKE_CXX_STANDARD_REQUIRED ON)"
p_info "set(CMAKE_CXX_EXTENSIONS OFF)"
p_box "  Requests C++17 for all C++ files."
p_box ""
p_box "  CMAKE_CXX_EXTENSIONS OFF ← the important one:"
p_box "    OFF → -std=c++17    (strict ISO C++17 only)"
p_box "    ON  → -std=gnu++17  (C++17 + GCC-specific GNU extensions)"
p_box ""
p_box "  Why OFF?"
p_box "    Code with -std=c++17 compiles on GCC, Clang, AND MSVC."
p_box "    Code with -std=gnu++17 uses GCC extensions that Clang may"
p_box "    not support, and MSVC certainly doesn't."
p_box "    Turning it OFF keeps your code portable."

# ── extern "C" ────────────────────────────────────────────────────────────────
p_section "extern \"C\" — The C/C++ Interop Bridge"

p_info "C++ mangles function names. C does not."
p_info ""
p_box "  C++ compiles:  void add(int a, int b)  →  _Z3addii   (mangled)"
p_box "  C compiles:    void add(int a, int b)  →  add        (plain)"
p_info ""
p_info "If C++ calls a function compiled by C, the linker looks for the"
p_info "mangled name but the C object only exports the plain name → error."
p_info ""
p_info "extern \"C\" tells the C++ compiler: 'don't mangle this name'."
p_info ""
p_info "The bridge header (cmath_bridge.h) uses the standard pattern:"
echo ""
cat "$STEP_DIR/cmath_bridge.h"
echo ""
p_info "#ifdef __cplusplus wraps extern \"C\" so the same header works"
p_info "when included from BOTH C files (which don't understand extern \"C\")"
p_info "AND C++ files (which need it)."

# ── Build and run ─────────────────────────────────────────────────────────────
p_section "Build and Run"

cd "$STEP_DIR"
rm -rf build

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release 2>&1 | tail -3
cmake --build build -j4 2>&1

p_info ""
p_cmd "./build/multilang"
echo ""
./build/multilang

# ── Verify the flags ─────────────────────────────────────────────────────────
p_section "Verify the Language Flags Used"

p_info "Check that C++17 strict mode (-std=c++17, not gnu++17) was used:"
p_info ""
cmake --build build --verbose 2>&1 | grep -oE "\-std=[a-z0-9+]+" | sort -u
p_info ""
p_info "You should see: -std=c11 and -std=c++17 (no 'gnu' prefix)"

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 5 Summary"

p_ok "project(name C CXX) — enables both compilers"
p_ok "CMake selects gcc for .c files and g++ for .cpp files automatically"
p_ok "CMAKE_C_STANDARD / CMAKE_CXX_STANDARD — request a language version"
p_ok "_STANDARD_REQUIRED ON — fail if the standard is unavailable"
p_ok "CMAKE_CXX_EXTENSIONS OFF → -std=c++17 (portable, not gnu++17)"
p_ok "extern \"C\" bridges C/C++: prevents C++ name mangling for C functions"
echo ""
p_info "Next: cd ../step6_modular && bash tutorial.sh"
echo ""
