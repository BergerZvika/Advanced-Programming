#!/bin/bash
# =============================================================================
# tutorial.sh — Step 4: Libraries
# Covers add_library (STATIC vs SHARED), add_subdirectory, and how
# target_link_libraries propagates include paths automatically.
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
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 4 — Libraries: STATIC, SHARED, add_subdirectory")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

# ── Goal ─────────────────────────────────────────────────────────────────────
p_section "Goal of This Step"

p_info "Learn to build reusable code as a library."
p_info "Understand STATIC vs SHARED libraries, how to organise code in"
p_info "subdirectories, and how CMake propagates include paths automatically."

# ── Project structure ─────────────────────────────────────────────────────────
p_section "Project Structure"

p_box "  step4_libraries/"
p_box "  ├── CMakeLists.txt          ← top-level: creates vecapp, links vec3"
p_box "  ├── main.c                  ← uses the vec3 library"
p_box "  └── mylib/"
p_box "      ├── CMakeLists.txt      ← defines the vec3 library target"
p_box "      ├── vec3.h              ← public API"
p_box "      └── vector.c            ← implementation"
p_info ""
p_info "The library lives in its own subdirectory with its own CMakeLists.txt."
p_info "This is the standard pattern for reusable libraries in CMake projects."

# ── add_library ───────────────────────────────────────────────────────────────
p_section "add_library — Creating a Library Target"

p_info "The library's CMakeLists.txt (mylib/CMakeLists.txt):"
echo ""
cat "$STEP_DIR/mylib/CMakeLists.txt"
echo ""

p_info "add_library(vec3 STATIC vector.c)"
p_info ""
p_info "The second argument is the library TYPE:"
p_info ""
p_box "  STATIC"
p_box "    Produces: libvec3.a (Linux/macOS)  or  vec3.lib (Windows)"
p_box "    The .a is an ARCHIVE of .o files."
p_box "    At link time, the linker copies vec3's code INTO the executable."
p_box "    Result: one self-contained binary, no runtime dependency."
p_box "    Trade-off: each app that uses vec3 carries its own copy."
p_info ""
p_box "  SHARED"
p_box "    Produces: libvec3.so (Linux)  or  libvec3.dylib (macOS)"
p_box "    The executable just records 'I need libvec3.so'."
p_box "    The OS loads it into memory at runtime (when the app starts)."
p_box "    Result: smaller executable; library can be updated independently."
p_box "    Trade-off: the .so must be present on the system at runtime."
p_info ""
p_box "  Choosing:"
p_box "    STATIC  → simpler deployment, one file to ship"
p_box "    SHARED  → share one copy across many apps, easier updates"

# ── add_subdirectory ──────────────────────────────────────────────────────────
p_section "add_subdirectory — Bringing In Subdirectories"

p_info "The top-level CMakeLists.txt:"
echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""

p_info "add_subdirectory(mylib)"
p_info ""
p_info "This tells CMake: 'go into mylib/ and process its CMakeLists.txt'."
p_info "After this line, the 'vec3' target is defined and available here."
p_info ""
p_info "⚠ ORDER MATTERS:"
p_box "  add_subdirectory(mylib)      ← vec3 defined here"
p_box "  add_executable(vecapp ...)   ← vecapp defined after"
p_box "  target_link_libraries(vecapp ... vec3)  ← vec3 must already exist"
p_info ""
p_info "If you put add_subdirectory AFTER target_link_libraries, CMake"
p_info "would fail with 'target vec3 not found'."

# ── Transitive include propagation ────────────────────────────────────────────
p_section "The Magic: Automatic Include Propagation"

p_info "In mylib/CMakeLists.txt:"
p_box "  target_include_directories(vec3 PUBLIC \${CMAKE_CURRENT_SOURCE_DIR})"
p_info ""
p_info "PUBLIC means: vec3 AND its consumers get -Imylib/"
p_info ""
p_info "So in the top-level CMakeLists.txt, we ONLY need:"
p_box "  target_link_libraries(vecapp PRIVATE vec3)"
p_info ""
p_info "And vecapp automatically gets -Imylib/ from vec3's PUBLIC include!"
p_info "No explicit target_include_directories(vecapp ...) is needed."
p_info ""
p_info "This is CMake's TARGET-BASED dependency model:"
p_box "  link a target → automatically inherit its public properties"
p_info ""
p_info "The old way (pre-CMake 3.x) was directory-level:"
p_box "  include_directories(mylib/)   ← applies to ALL targets, can't scope it"
p_info "The modern target-based way is much cleaner and safer."

# ── Build the static version ──────────────────────────────────────────────────
p_section "Build: Static Library"

cd "$STEP_DIR"
rm -rf build build_shared

cmake -S . -B build 2>&1 | tail -3
cmake --build build -j4 2>&1

p_info ""
p_cmd "./build/vecapp"
echo ""
./build/vecapp

p_info ""
p_info "What files were produced?"
find build -name "*.a" -o -name "*.o" 2>/dev/null | grep -v "CMakeFiles/_deps" | sort | head -20
p_info ""
p_info "libvec3.a = the static archive, merged into vecapp at link time"
p_info "vecapp    = the executable (contains vec3 code inside it)"

# ── See the link command ──────────────────────────────────────────────────────
p_section "See the Link Command (--verbose)"

cmake --build build --verbose 2>&1 | grep -E "(ar |link|vecapp)" | head -5 || true
p_info ""
p_info "You can see:"
p_info "  • ar: creates libvec3.a from vector.c.o (archive command)"
p_info "  • gcc: links main.c.o + libvec3.a → vecapp"

# ── Switch to SHARED ──────────────────────────────────────────────────────────
p_section "Switch to SHARED Library"

p_info "Edit mylib/CMakeLists.txt: change STATIC to SHARED."
p_info "Or use BUILD_SHARED_LIBS to override globally:"
p_info ""
p_cmd "cmake -S . -B build_shared -DBUILD_SHARED_LIBS=ON"
cmake -S . -B build_shared -DBUILD_SHARED_LIBS=ON 2>&1 | tail -3
cmake --build build_shared -j4 2>&1

p_info ""
p_info "What files were produced?"
find build_shared -name "*.so" -o -name "vecapp" 2>/dev/null | grep -v "CMakeFiles" | sort | head -10
p_info ""
p_info "libvec3.so = the shared object"
p_info "vecapp     = the executable (does NOT contain vec3 code)"
p_info ""

if command -v ldd &>/dev/null; then
    p_cmd "ldd build_shared/vecapp | grep vec3"
    ldd build_shared/vecapp | grep vec3 || p_info "(vec3 dep shown in ldd output above)"
fi

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build build_shared

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 4 Summary"

p_ok "add_library(name STATIC src.c) — create a static archive (.a)"
p_ok "add_library(name SHARED src.c) — create a shared object (.so)"
p_ok "add_subdirectory(mylib) — process subdirectory's CMakeLists.txt"
p_ok "add_subdirectory must come BEFORE targets that link to its libraries"
p_ok "PUBLIC include dirs propagate automatically through target_link_libraries"
p_ok "BUILD_SHARED_LIBS=ON overrides STATIC → SHARED globally"
echo ""
p_info "Next: cd ../step5_multilang && bash tutorial.sh"
echo ""
