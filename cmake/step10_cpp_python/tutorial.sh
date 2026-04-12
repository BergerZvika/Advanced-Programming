#!/bin/bash
# =============================================================================
# tutorial.sh — Step 10: C++ + Python via pybind11
# Covers find_package(Python3), FetchContent for pybind11, pybind11_add_module,
# POSITION_INDEPENDENT_CODE, add_custom_target, and PYTHONPATH.
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
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 10 — C++ + Python via pybind11")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

p_section "Goal of This Step"

p_info "You have a fast C++ library and want to call it from Python."
p_info "pybind11 generates the Python bindings automatically from C++ headers."
p_info "CMake orchestrates: build the .so, set PYTHONPATH, run the demo."

# ── Project structure ─────────────────────────────────────────────────────────
p_section "Project Structure"

p_box "  step10_cpp_python/"
p_box "  ├── CMakeLists.txt         ← build script"
p_box "  ├── demo.py                ← Python demo that imports the C++ module"
p_box "  ├── include/"
p_box "  │   └── vec3.hpp           ← C++ Vec3 class + Stats functions (header)"
p_box "  └── src/"
p_box "      ├── vec3.cpp           ← C++ implementation"
p_box "      └── bindings.cpp       ← pybind11 glue code"

# ── Why pybind11? ─────────────────────────────────────────────────────────────
p_section "Why pybind11?"

p_info "pybind11 is a header-only C++ library. You write a thin 'bindings' file"
p_info "that describes what to expose to Python, and pybind11 generates all the"
p_info "CPython API boilerplate (PyArg_ParseTuple, PyObject*, etc.) for you."
p_info ""
p_box "  C++ class Vec3  →  PYBIND11_MODULE(myvec3, m) { py::class_<Vec3>... }"
p_box "  Python:  import myvec3; v = myvec3.Vec3(1, 2, 3)"

# ── CMakeLists.txt walkthrough ────────────────────────────────────────────────
p_section "CMakeLists.txt Walkthrough"

echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""

p_info "Key decisions in this CMakeLists.txt:"
p_info ""
p_info "1. cmake_minimum_required(VERSION 3.18)"
p_box "   3.18 added Development.Module component for find_package(Python3)."
p_box "   Earlier CMake only supports 'Development' which requires libpython —"
p_box "   often missing in virtualenvs and conda environments."
p_info ""
p_info "2. find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)"
p_box "   Interpreter — finds python3 executable → Python3_EXECUTABLE"
p_box "   Development.Module — finds Python.h → creates Python3::Module target"
p_box "   Why not 'Development'? That also requires libpython3.x.so (the embed lib),"
p_box "   which many virtualenvs don't ship. .Module is sufficient for extensions."
p_info ""
p_info "3. FetchContent_Declare / FetchContent_MakeAvailable"
p_box "   Downloads pybind11 at configure time if not already cached."
p_box "   GIT_SHALLOW TRUE → git clone --depth=1 (no history, faster download)"
p_box "   After MakeAvailable: pybind11_add_module() is a valid CMake command."
p_info ""
p_info "4. add_library(vec3lib STATIC src/vec3.cpp)"
p_box "   Build C++ code as STATIC. The extension .so will embed it directly."
p_box "   Benefit: only one file to ship (myvec3.so), no separate libvec3lib.so."
p_info ""
p_info "5. POSITION_INDEPENDENT_CODE ON on the STATIC library"
p_box "   Shared objects (.so) must contain position-independent code (-fPIC)."
p_box "   When a STATIC lib is linked INTO a .so, its .o files must also have -fPIC."
p_box "   Without this property you get a linker error:"
p_box "     relocation R_X86_64_PC32 ... can not be used when making a shared object;"
p_box "     recompile with -fPIC"
p_info ""
p_info "6. pybind11_add_module(myvec3 src/bindings.cpp)"
p_box "   pybind11's version of add_library(myvec3 MODULE ...)."
p_box "   Auto-adds: ABI suffix in filename, -fvisibility=hidden, strip in Release."
p_box "   Output: myvec3.cpython-3XX-x86_64-linux-gnu.so  (Python-importable name)"
p_info ""
p_info "7. add_custom_target(run_demo ...) with cmake -E env PYTHONPATH=..."
p_box "   cmake -E env: portable 'run command with env var' (works on Windows too)"
p_box "   PYTHONPATH=\${CMAKE_BINARY_DIR}: tells Python where to find myvec3.so"
p_box "   DEPENDS myvec3: ensures .so is built before the demo runs"
p_box "   VERBATIM: prevents CMake from mangling the PYTHONPATH= argument"

# ── Build ─────────────────────────────────────────────────────────────────────
p_section "Build"

cd "$STEP_DIR"
rm -rf build

p_cmd "cmake -S . -B build"
p_info "(This downloads pybind11 — may take a moment on first run)"
echo ""
cmake -S . -B build 2>&1

echo ""
p_cmd "cmake --build build"
cmake --build build 2>&1

# ── Inspect the generated .so ─────────────────────────────────────────────────
p_section "Inspect the Generated Extension Module"

echo ""
p_cmd "ls build/myvec3*.so"
ls build/myvec3*.so 2>/dev/null || echo "  (no .so found — build may have used a different suffix)"

p_info ""
p_info "The filename encodes:"
p_box "  myvec3              → module name (what you 'import')"
p_box "  cpython-3XX         → CPython ABI version"
p_box "  x86_64-linux-gnu    → platform tag"
p_box "  .so                 → shared object"
p_info ""
p_info "Python's import machinery searches for exactly this name in sys.path."

# ── Run the demo ──────────────────────────────────────────────────────────────
p_section "Run the Python Demo"

p_cmd "cmake --build build --target run_demo"
echo ""
cmake --build build --target run_demo 2>&1

# ── Manual PYTHONPATH ─────────────────────────────────────────────────────────
p_section "Running Manually with PYTHONPATH"

p_info "You can also run the demo directly without CMake:"
p_cmd "PYTHONPATH=build python3 demo.py"
p_info ""
p_info "PYTHONPATH tells Python to search 'build/' for modules."
p_info "Without it, 'import myvec3' would fail with ModuleNotFoundError."
p_info ""
p_info "To install the module system-wide:"
p_box "  pip install pybind11"
p_box "  pip install . --build-option=build_ext"
p_box "  # Then: import myvec3  works from anywhere"

# ── Key difference: MODULE vs SHARED ─────────────────────────────────────────
p_section "MODULE vs SHARED vs STATIC — When to Use What"

p_box "  STATIC   → archived object files (.a / .lib)"
p_box "             use for: libraries linked into executables or other .so"
p_box "             our vec3lib is STATIC so it merges cleanly into the Python .so"
p_box ""
p_box "  SHARED   → shared library (.so / .dll)"
p_box "             use for: libraries loaded by multiple executables at runtime"
p_box "             System.loadLibrary() (Java/JNI) uses SHARED"
p_box ""
p_box "  MODULE   → shared library loaded explicitly by dlopen() or the Python import"
p_box "             system. NOT linked with -l at compile time."
p_box "             pybind11_add_module() creates a MODULE target"

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 10 Summary"

p_ok "cmake_minimum_required(VERSION 3.18) — needed for Development.Module"
p_ok "find_package(Python3 COMPONENTS Interpreter Development.Module)"
p_ok "FetchContent_Declare/MakeAvailable — download pybind11, no system install needed"
p_ok "add_library(STATIC) + POSITION_INDEPENDENT_CODE ON — embed into .so without -fPIC errors"
p_ok "pybind11_add_module() — creates Python extension module with correct ABI filename"
p_ok "add_custom_target + cmake -E env — portable PYTHONPATH for running the demo"
p_ok "DEPENDS — ensures .so is rebuilt before running the custom target"
p_ok "VERBATIM — pass COMMAND args without shell interpretation"
echo ""
p_info "Up next: Step 11 — C++ + Java via JNI (native methods)"
echo ""
