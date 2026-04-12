#!/bin/bash
# =============================================================================
# tutorial.sh — Step 6: Modular Project
# Covers multi-level add_subdirectory, how PUBLIC properties flow through
# the dependency graph, and target_compile_features.
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
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 6 — Modular Project: Multi-Level Dependencies")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

p_section "Goal of This Step"

p_info "Real projects have many libraries in many subdirectories."
p_info "Learn how CMake's dependency graph propagates properties"
p_info "automatically across multiple levels."

# ── Project structure ─────────────────────────────────────────────────────────
p_section "Project Structure"

p_box "  step6_modular/"
p_box "  ├── CMakeLists.txt            ← root: includes libs/ and apps/"
p_box "  ├── libs/"
p_box "  │   ├── CMakeLists.txt        ← groups the libraries"
p_box "  │   ├── geometry/"
p_box "  │   │   ├── CMakeLists.txt    ← defines 'geometry' target"
p_box "  │   │   ├── geometry.hpp"
p_box "  │   │   └── geometry.cpp"
p_box "  │   └── io/"
p_box "  │       ├── CMakeLists.txt    ← defines 'io' target"
p_box "  │       ├── io.hpp"
p_box "  │       └── io.cpp"
p_box "  └── apps/"
p_box "      ├── CMakeLists.txt        ← defines 'geoapp' executable"
p_box "      └── main.cpp"

# ── Walk through each CMakeLists.txt ─────────────────────────────────────────
p_section "CMakeLists.txt Files — Top to Bottom"

p_info "ROOT (step6_modular/CMakeLists.txt):"
echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""
p_box "  The root just includes two subdirectories."
p_box "  libs/ MUST come before apps/ because apps/ links to libs' targets."

p_info ""
p_info "LIBS GROUPING (libs/CMakeLists.txt):"
echo ""
cat "$STEP_DIR/libs/CMakeLists.txt"
echo ""
p_box "  This file is a simple router: it pulls in both library subdirs."
p_box "  geometry and io are independent — their order doesn't matter."

p_info ""
p_info "GEOMETRY LIBRARY (libs/geometry/CMakeLists.txt):"
echo ""
cat "$STEP_DIR/libs/geometry/CMakeLists.txt"
echo ""
p_box "  target_compile_features(geometry PUBLIC cxx_std_17)"
p_box "  This is the preferred alternative to CMAKE_CXX_STANDARD."
p_box "  It is per-target and propagates through the dependency graph."
p_box "  Any target that links 'geometry' will also compile with C++17."

p_info ""
p_info "APPS (apps/CMakeLists.txt):"
echo ""
cat "$STEP_DIR/apps/CMakeLists.txt"
echo ""
p_box "  geoapp links geometry and io — that's all it needs to declare."
p_box "  It automatically inherits:"
p_box "    • -I<libs/geometry/>  from geometry's PUBLIC include"
p_box "    • -I<libs/io/>        from io's PUBLIC include"
p_box "    • -std=c++17          from both libraries' PUBLIC compile feature"

# ── The dependency graph ──────────────────────────────────────────────────────
p_section "The Dependency Graph"

p_box "  geoapp"
p_box "    ├── geometry (PRIVATE link)"
p_box "    │     └── includes: libs/geometry/  (PUBLIC → flows to geoapp)"
p_box "    │     └── feature:  cxx_std_17      (PUBLIC → flows to geoapp)"
p_box "    └── io (PRIVATE link)"
p_box "          └── includes: libs/io/        (PUBLIC → flows to geoapp)"
p_box "          └── feature:  cxx_std_17      (PUBLIC → flows to geoapp)"
p_info ""
p_info "geoapp does not need ANY target_include_directories or"
p_info "target_compile_features calls — it inherits everything."

# ── target_compile_features vs CMAKE_CXX_STANDARD ────────────────────────────
p_section "target_compile_features vs CMAKE_CXX_STANDARD"

p_info "Two ways to request a C++ standard:"
p_info ""
p_box "  Method 1 — Global variable (blunt instrument):"
p_box "    set(CMAKE_CXX_STANDARD 17)           ← applies to ALL targets"
p_box "    Works, but not scoped to a target."
p_info ""
p_box "  Method 2 — Per-target feature (fine-grained):"
p_box "    target_compile_features(mylib PUBLIC cxx_std_17)"
p_box "    Scoped to 'mylib' and propagated via PUBLIC."
p_box "    Better for libraries: consumers automatically get C++17."
p_info ""
p_info "In a project you own end-to-end, CMAKE_CXX_STANDARD is simpler."
p_info "In a library meant for others to use, target_compile_features is"
p_info "more correct because it expresses the requirement in the target."

# ── Build and run ─────────────────────────────────────────────────────────────
p_section "Build and Run"

cd "$STEP_DIR"
rm -rf build

cmake -S . -B build 2>&1 | tail -3
cmake --build build -j4 2>&1

p_info ""
p_cmd "./build/apps/geoapp"
echo ""
./build/apps/geoapp

# ── List all targets ─────────────────────────────────────────────────────────
p_section "Explore: List All Targets"

p_cmd "cmake --build build --target help"
cmake --build build --target help 2>&1 | head -20

p_info ""
p_info "You can see geometry, io, and geoapp as separate targets."
p_info "Build only the geometry library:"
p_cmd "cmake --build build --target geometry"

# ── Visualise the dependency graph ────────────────────────────────────────────
p_section "Bonus: Visualise the Dependency Graph"

if command -v dot &>/dev/null; then
    cmake --graphviz=build/deps.dot -S . -B build 2>/dev/null
    dot -Tpng build/deps.dot -o build/deps.png 2>/dev/null
    p_ok "Dependency graph image: build/deps.png"
else
    p_cmd "cmake --graphviz=build/deps.dot -S . -B build"
    p_cmd "dot -Tpng build/deps.dot -o build/deps.png"
    p_info "(Install graphviz: sudo apt install graphviz)"
fi

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 6 Summary"

p_ok "add_subdirectory() can be nested: root → libs/ → geometry/ and io/"
p_ok "Order matters: define targets BEFORE anything links to them"
p_ok "PUBLIC properties (includes, features) flow down the dependency graph"
p_ok "target_compile_features() is the per-target alternative to CMAKE_CXX_STANDARD"
p_ok "cmake --build build --target help lists all available targets"
p_ok "cmake --graphviz visualises the dependency graph"
echo ""
p_info "Next: cd ../step7_fetchcontent && bash tutorial.sh"
echo ""
