#!/bin/bash
# =============================================================================
# tutorial.sh — Step 9: Install Rules
# Covers install(), GNUInstallDirs, BUILD_INTERFACE vs INSTALL_INTERFACE,
# CMAKE_INSTALL_PREFIX, and cmake --install flags.
# =============================================================================

set -euo pipefail

YELLOW='\033[1;33m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
BLUE='\033[0;34m'
BOLD='\033[1m'
RESET='\033[0m'

STEP_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
INSTALL_DIR="/tmp/cmake_tutorial_install_$$"

p_section() { echo -e "\n${YELLOW}=== $1 ===${RESET}"; }
p_info()    { echo -e "  ${CYAN}$1${RESET}"; }
p_cmd()     { echo -e "  ${GREEN}\$ $1${RESET}"; }
p_ok()      { echo -e "  ${GREEN}✔  $1${RESET}"; }
p_box()     { echo -e "  ${BLUE}$1${RESET}"; }

echo ""
echo -e "${CYAN}╔══════════════════════════════════════════════════════════════════════════════╗${RESET}"
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 9 — Install Rules: cmake --install")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

p_section "Goal of This Step"

p_info "A library is only useful if other projects can find and use it."
p_info "Learn how to define install rules so your project installs cleanly"
p_info "to any prefix, and understand the difference between build-time"
p_info "and install-time paths."

# ── Why install rules? ────────────────────────────────────────────────────────
p_section "Why Install Rules?"

p_info "Without install rules, your library only works within its own build."
p_info "With install rules, you can run:"
p_info ""
p_cmd "cmake --install build --prefix /opt/myproject"
p_info ""
p_info "And get a layout that other projects can consume:"
p_box "  /opt/myproject/"
p_box "  ├── bin/"
p_box "  │   └── myapp"
p_box "  ├── lib/"
p_box "  │   └── libmylib.so"
p_box "  └── include/"
p_box "      └── mylib.hpp"
p_info ""
p_info "Other CMake projects then find your library with:"
p_box "  find_package(mylib REQUIRED)"

# ── GNUInstallDirs ────────────────────────────────────────────────────────────
p_section "GNUInstallDirs — Why Use Standard Directories?"

p_info "include(GNUInstallDirs) defines variables for standard FHS paths:"
p_info ""
p_box "  Variable                      Default (relative to prefix)"
p_box "  ────────────────────────────────────────────────────────────"
p_box "  CMAKE_INSTALL_BINDIR          bin/"
p_box "  CMAKE_INSTALL_LIBDIR          lib/   (or lib64/ on Fedora/RHEL)"
p_box "  CMAKE_INSTALL_INCLUDEDIR      include/"
p_box "  CMAKE_INSTALL_DATADIR         share/"
p_box "  CMAKE_INSTALL_FULL_BINDIR     \${prefix}/bin/  (absolute)"
p_info ""
p_info "Why not just hardcode 'lib/'?"
p_box "  On Debian/Ubuntu: lib/x86_64-linux-gnu/"
p_box "  On Fedora/RHEL:   lib64/"
p_box "  Using the variable makes your package install correctly everywhere."

# ── CMakeLists.txt walkthrough ────────────────────────────────────────────────
p_section "CMakeLists.txt — Install Rules Explained"

echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""

p_info "BUILD_INTERFACE vs INSTALL_INTERFACE:"
p_box ""
p_box "  While building (inside this project):"
p_box "    → headers are in: <source>/include/"
p_box ""
p_box "  After installing:"
p_box "    → headers are in: \${prefix}/include/"
p_box ""
p_box "  These are DIFFERENT paths. Generator expressions let you specify both:"
p_box '    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>'
p_box '    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>'
p_box ""
p_box "  During build:   the BUILD_INTERFACE path is active"
p_box "  After install:  the INSTALL_INTERFACE path is recorded in"
p_box "                  the exported target for find_package() consumers"
p_info ""

p_info "install(TARGETS mylib myapp RUNTIME ... LIBRARY ... ARCHIVE ...)"
p_box "  RUNTIME  → executables and .dll files  → PREFIX/bin/"
p_box "  LIBRARY  → .so / .dylib files          → PREFIX/lib/"
p_box "  ARCHIVE  → .a / .lib files             → PREFIX/lib/"
p_info ""

p_info 'install(DIRECTORY include/ ... FILES_MATCHING PATTERN "*.hpp")'
p_box "  include/  (with trailing slash) → copy CONTENTS, not the dir itself"
p_box "  FILES_MATCHING PATTERN *.hpp   → only .hpp files, skip others"

# ── Build and run ─────────────────────────────────────────────────────────────
p_section "Build"

cd "$STEP_DIR"
rm -rf build

cmake -S . -B build -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR" 2>&1 | grep -E "(Install|STATUS)"
cmake --build build 2>&1

p_info ""
p_cmd "./build/myapp"
echo ""
./build/myapp

# ── Install ───────────────────────────────────────────────────────────────────
p_section "Install to a Temporary Prefix"

p_cmd "cmake --install build --prefix $INSTALL_DIR"
echo ""
cmake --install build --prefix "$INSTALL_DIR" 2>&1

p_info ""
p_info "What was installed:"
find "$INSTALL_DIR" -type f | sort | sed "s|$INSTALL_DIR/||g" | while read f; do
    echo "  $f"
done

p_info ""
p_info "Run the installed binary:"
p_cmd "$INSTALL_DIR/bin/myapp"
echo ""
"$INSTALL_DIR/bin/myapp"

# ── Override prefix at install time ───────────────────────────────────────────
p_section "Override Prefix at Install Time"

ALT_DIR="/tmp/cmake_tutorial_alt_$$"
p_info "You can override the prefix per install run:"
p_cmd "cmake --install build --prefix $ALT_DIR"
cmake --install build --prefix "$ALT_DIR" 2>&1

p_info ""
p_info "Contents:"
find "$ALT_DIR" -type f | sort | sed "s|$ALT_DIR/||g" | while read f; do
    echo "  $f"
done

# ── Strip debug symbols on install ────────────────────────────────────────────
p_section "Strip Debug Symbols on Install"

p_info "For production installs, strip debug symbols to reduce size:"
STRIP_DIR="/tmp/cmake_tutorial_strip_$$"

cmake -S . -B build_debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="$STRIP_DIR" 2>&1 | tail -1
cmake --build build_debug 2>&1 | tail -2

p_cmd "cmake --install build_debug --strip --prefix $STRIP_DIR"
cmake --install build_debug --strip --prefix "$STRIP_DIR" 2>&1

p_info ""
p_info "Size comparison:"
ls -lh build_debug/myapp "$STRIP_DIR/bin/myapp" 2>/dev/null || true
p_info "(Debug binary is larger due to embedded symbol table)"

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build build_debug "$INSTALL_DIR" "$ALT_DIR" "$STRIP_DIR"

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 9 Summary"

p_ok "include(GNUInstallDirs) — platform-correct dir variables"
p_ok "CMAKE_INSTALL_BINDIR / LIBDIR / INCLUDEDIR — use these, never hardcode"
p_ok "install(TARGETS ... RUNTIME/LIBRARY/ARCHIVE DESTINATION ...)"
p_ok "install(DIRECTORY include/ ... FILES_MATCHING PATTERN '*.hpp')"
p_ok 'BUILD_INTERFACE vs INSTALL_INTERFACE — different paths in build vs install'
p_ok "cmake --install build --prefix /my/path — install to any prefix"
p_ok "cmake --install build --strip — remove debug symbols on install"
echo ""
p_info "Next: cd ../step12_compiler_flags && bash tutorial.sh"
echo ""
