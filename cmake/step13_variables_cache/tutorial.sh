#!/bin/bash
# =============================================================================
# tutorial.sh — Step 13: Variables and the Cache
# Covers set(), cache variables, option(), if/else, platform/compiler
# detection, string operations, and list manipulation.
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
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 13 — Variables, Cache, and Conditionals")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

p_section "Goal of This Step"

p_info "CMake's scripting language drives everything: variables, conditions,"
p_info "loops, and string operations. Understanding the variable system is"
p_info "essential for writing configurable, platform-aware build scripts."

# ── Regular vs Cache variables ────────────────────────────────────────────────
p_section "Regular Variables vs Cache Variables"

p_info "CMake has two kinds of variables:"
p_info ""
p_box "  Regular variable:  set(MY_VAR \"hello\")"
p_box "    • Lives only for the current cmake run"
p_box "    • Scope: current file and subdirectories processed below it"
p_box "    • Not visible in cmake-gui or ccmake"
p_box "    • Vanishes when cmake finishes"
p_info ""
p_box "  Cache variable:    set(MY_OPT ON CACHE BOOL \"Enable X\")"
p_box "    • Stored in build/CMakeCache.txt"
p_box "    • PERSISTS between cmake runs on the same build dir"
p_box "    • User can override:  cmake -DMY_OPT=OFF -S . -B build"
p_box "    • Visible in cmake-gui / ccmake as an interactive setting"
p_info ""
p_info "If a regular variable and a cache variable have the SAME name,"
p_info "the regular variable takes precedence in the current scope."

# ── Variable syntax ───────────────────────────────────────────────────────────
p_section "Variable Syntax"

p_info 'Expand a variable with ${VAR}:'
p_box '  set(NAME "world")'
p_box '  message("Hello ${NAME}")    → Hello world'
p_info ""
p_info 'Expand inside a string:'
p_box '  set(DIR "/tmp")'
p_box '  set(PATH "${DIR}/file.txt") → /tmp/file.txt'
p_info ""
p_info 'Access environment variables with $ENV{VAR}:'
p_box '  message("Home: $ENV{HOME}")'
p_info ""
p_info 'Undefined variables expand to empty string (no error):'
p_box '  message("${UNDEFINED_VAR}")  → (empty line)'
p_info ""
p_info 'Check if a variable is defined:'
p_box '  if(DEFINED MY_VAR)   → true if MY_VAR is set'
p_box '  if(MY_VAR)           → true if MY_VAR is set AND non-empty/non-zero'

# ── option() ─────────────────────────────────────────────────────────────────
p_section "option() — Boolean Cache Variables"

p_info "option(NAME \"description\" ON|OFF)"
p_info ""
p_box "  Shorthand for:  set(NAME ON CACHE BOOL \"description\")"
p_box "  Use option() for feature flags — it reads more clearly."
p_info ""
p_info "Override from the command line:"
p_cmd "cmake -S . -B build -DENABLE_FEATURE_X=ON"
p_info ""
p_info "Or interactively:"
p_cmd "ccmake build/   # text UI with checkboxes"
p_cmd "cmake-gui       # graphical UI with checkboxes"

# ── if/elseif/else ────────────────────────────────────────────────────────────
p_section "Conditionals: if() / elseif() / else()"

p_info "CMake's if() supports many comparison operators:"
p_info ""
p_box "  if(VAR)                 → true if VAR is defined and non-empty/non-zero"
p_box "  if(NOT VAR)             → inverse"
p_box "  if(A AND B)             → logical and"
p_box "  if(A OR B)              → logical or"
p_box ""
p_box "  Numeric comparisons:"
p_box "  if(A EQUAL B)           → A == B (numeric)"
p_box "  if(A LESS B)            → A < B"
p_box "  if(A GREATER B)         → A > B"
p_box ""
p_box "  String comparisons:"
p_box "  if(A STREQUAL B)        → exact string match"
p_box "  if(A MATCHES regex)     → regex match"
p_box ""
p_box "  Version comparisons:"
p_box "  if(A VERSION_LESS B)    → semantic version comparison"
p_box ""
p_box "  File tests:"
p_box "  if(EXISTS \"/path/to/file\")  → file or directory exists"
p_box "  if(IS_DIRECTORY \"/path\")    → is a directory"

# ── CMakeLists.txt ────────────────────────────────────────────────────────────
p_section "CMakeLists.txt"

echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""

# ── Build: defaults ───────────────────────────────────────────────────────────
p_section "Build: Default Settings"

cd "$STEP_DIR"
rm -rf build build_feat build_repeat

cmake -S . -B build 2>&1
cmake --build build 2>&1

p_info ""
p_cmd "./build/varsdemo"
echo ""
./build/varsdemo

# ── Override GREETING_REPEAT ──────────────────────────────────────────────────
p_section "Override: Change GREETING_REPEAT"

p_cmd "cmake -S . -B build_repeat -DGREETING_REPEAT=5 2>&1"
cmake -S . -B build_repeat -DGREETING_REPEAT=5 2>&1 | grep "Repeat"
cmake --build build_repeat 2>&1 | tail -1
echo ""
./build_repeat/varsdemo | grep -v "^$" | head -8

# ── Enable Feature X ──────────────────────────────────────────────────────────
p_section "Override: Enable Feature X"

# Create a stub feature_x.cpp so the build doesn't fail
cat > "$STEP_DIR/feature_x.cpp" << 'CPPEOF'
#include <iostream>
void feature_x_init() { std::cout << "  [Feature X loaded]\n"; }
CPPEOF

cmake -S . -B build_feat -DENABLE_FEATURE_X=ON 2>&1 | grep -E "(Feature|STATUS)"
cmake --build build_feat 2>&1 | tail -1
rm -f "$STEP_DIR/feature_x.cpp"

# ── Inspect the cache ─────────────────────────────────────────────────────────
p_section "Inspect the CMake Cache"

p_cmd "cmake -S . -B build -LAH"
p_info "(showing first 30 lines)"
cmake -S . -B build -LAH 2>&1 | head -30

# ── List the cache in a file ──────────────────────────────────────────────────
p_section "View the Cache File Directly"

p_cmd "cat build/CMakeCache.txt | grep -E '^(GREETING|ENABLE|SHOW)'"
grep -E "^(GREETING|ENABLE|SHOW)" build/CMakeCache.txt 2>/dev/null || \
  grep -E "^[A-Z]" build/CMakeCache.txt | head -10

# ── Useful built-in variables ─────────────────────────────────────────────────
p_section "Useful Built-In Variables Reference"

p_box "  Variable                      Value (this machine)"
p_box "  ───────────────────────────────────────────────────────────────"
cmake -S . -B build 2>/dev/null | grep -E "Project name|Platform|System|Compiler" || true
p_box ""
p_box "  CMAKE_SOURCE_DIR        = project root (top-level CMakeLists.txt dir)"
p_box "  CMAKE_BINARY_DIR        = top-level build dir"
p_box "  CMAKE_CURRENT_SOURCE_DIR = this CMakeLists.txt's directory"
p_box "  CMAKE_CURRENT_BINARY_DIR = build dir for this CMakeLists.txt"
p_box "  CMAKE_BUILD_TYPE        = Debug / Release / RelWithDebInfo / MinSizeRel"
p_box "  CMAKE_SYSTEM_NAME       = Linux / Darwin / Windows"
p_box "  CMAKE_CXX_COMPILER_ID   = GNU / Clang / MSVC / AppleClang"
p_box "  PROJECT_NAME            = from project() call"
p_box "  PROJECT_VERSION         = from project(... VERSION x.y.z)"

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build build_feat build_repeat

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 13 Summary"

p_ok "set(VAR value) — regular variable; lives for this cmake run"
p_ok "set(VAR value CACHE TYPE doc) — persisted in CMakeCache.txt"
p_ok "option(NAME desc ON) — boolean cache variable, shown in cmake-gui"
p_ok "cmake -DVAR=val — override any cache variable from the command line"
p_ok "if(VAR) / if(A STREQUAL B) / if(A LESS B) — rich conditional support"
p_ok "CMAKE_SYSTEM_NAME, CMAKE_CXX_COMPILER_ID — platform/compiler detection"
p_ok 'string(TOUPPER ...) list(APPEND ...) — string and list manipulation'
echo ""
p_info "Next: cd ../step14_configure_file && bash tutorial.sh"
echo ""
