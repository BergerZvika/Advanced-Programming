#!/bin/bash
# =============================================================================
# tutorial.sh — Step 12: Compiler Flags, Warnings, and Defines
# Covers target_compile_options, target_compile_definitions, option(),
# generator expressions for per-compiler flags, and AddressSanitizer.
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
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 12 — Compiler Flags, Warnings, and Defines")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

p_section "Goal of This Step"

p_info "Real projects need to control compiler flags: enable warnings,"
p_info "add preprocessor defines, handle differences between GCC/Clang/MSVC,"
p_info "and conditionally enable tools like AddressSanitizer."

# ── Three commands for flags ──────────────────────────────────────────────────
p_section "Three Commands for Compiler Flags"

p_info "CMake has three target_compile_* commands:"
p_info ""
p_box "  target_compile_options(myapp PRIVATE -Wall -Wextra)"
p_box "    Adds raw compiler flags (-Wall, -O2, -fsanitize=address, etc.)"
p_box "    Use for anything that's just a compiler switch."
p_info ""
p_box "  target_compile_definitions(myapp PRIVATE DEBUG=1 APP_NAME=\"foo\")"
p_box "    Adds -D flags (preprocessor defines)."
p_box "    Equivalent to #define at the top of every source file."
p_info ""
p_box "  target_compile_features(myapp PUBLIC cxx_std_17)"
p_box "    Requests a language standard or feature (portable across compilers)."
p_box "    Translates to -std=c++17 (or /std:c++17 on MSVC)."

# ── PRIVATE vs PUBLIC for flags ───────────────────────────────────────────────
p_section "PRIVATE vs PUBLIC for Flags"

p_info "The same PRIVATE/PUBLIC/INTERFACE rules apply to flags:"
p_info ""
p_box "  PRIVATE  → only this target is compiled with the flag"
p_box "  PUBLIC   → this target AND consumers inherit the flag"
p_box "  INTERFACE→ only consumers inherit it"
p_info ""
p_info "WARNINGS should always be PRIVATE."
p_box "  If you made warnings PUBLIC, every library that links yours"
p_box "  would inherit your -Wall -Wextra, including third-party code"
p_box "  that may not compile cleanly at that warning level."
p_info ""
p_info "DEFINES that ARE part of the public API should be PUBLIC."
p_box "  Example: if APP_VERSION affects your public header's behaviour,"
p_box "  make it PUBLIC so consumers compile with the same define."

# ── option() ─────────────────────────────────────────────────────────────────
p_section "option() — User-Controllable Boolean Flags"

p_info "option(ENABLE_WARNINGS \"description\" ON)"
p_info ""
p_box "  Creates a boolean cache variable the user can override:"
p_box "    cmake -S . -B build -DENABLE_WARNINGS=OFF"
p_box ""
p_box "  Visible in ccmake/cmake-gui as a checkbox."
p_box "  Default value is the third argument (ON here)."
p_box ""
p_box "  The if(ENABLE_WARNINGS) block then conditionally adds warning flags."

# ── Generator expressions for per-compiler flags ──────────────────────────────
p_section "Per-Compiler Flags (Generator Expressions)"

p_info "GCC uses -Wall. MSVC uses /W4. They are NOT compatible."
p_info "Generator expressions let you express both in one CMakeLists.txt:"
p_info ""
p_box '  target_compile_options(app PRIVATE'
p_box '      $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:'
p_box '          -Wall -Wextra -Wpedantic'
p_box '      >'
p_box '      $<$<CXX_COMPILER_ID:MSVC>:'
p_box '          /W4 /WX'
p_box '      >'
p_box '  )'
p_info ""
p_info "Breaking down \$<\$<CXX_COMPILER_ID:GNU>:-Wall>:"
p_box "  \$<condition:value>   → if condition is true, expand to value"
p_box "  \$<CXX_COMPILER_ID:GNU>  → true when using GCC"
p_box "  Result: adds -Wall ONLY when compiling with GCC"
p_info ""
p_info "The outer \$<\$<BOOL:\${ENABLE_WARNINGS}>:...> wraps the whole block"
p_box "  → the flags are included only if ENABLE_WARNINGS is ON"

# ── Preprocessor defines ──────────────────────────────────────────────────────
p_section "Preprocessor Defines"

p_info "target_compile_definitions(app PRIVATE APP_NAME=\"FlagsDemo\" VERSION=12)"
p_info ""
p_box "  Translates to: -DAPP_NAME=\"FlagsDemo\" -DVERSION=12"
p_box "  Code can then use: #ifdef APP_NAME / APP_NAME / VERSION"
p_box ""
p_box "  Build-type-specific defines:"
p_box '    $<$<CONFIG:Debug>:DEBUG_BUILD=1>'
p_box "    → -DDEBUG_BUILD=1 only in Debug builds"
p_box '    $<$<CONFIG:Release>:RELEASE_BUILD=1>'
p_box "    → -DRELEASE_BUILD=1 only in Release builds"

# ── CMakeLists.txt ────────────────────────────────────────────────────────────
p_section "CMakeLists.txt"

echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""

# ── Build: default (warnings ON, Debug) ──────────────────────────────────────
p_section "Build: Default (warnings ON, Debug)"

cd "$STEP_DIR"
rm -rf build build_release build_nowarnings

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug 2>&1
cmake --build build 2>&1

p_info ""
p_cmd "./build/flagsdemo"
echo ""
./build/flagsdemo

# ── Verify warning flags ──────────────────────────────────────────────────────
p_section "Verify: Check What Flags Were Used"

p_cmd "cmake --build build --verbose 2>&1 | grep -oE '\\-W[a-z]+' | sort -u"
cmake --build build --verbose 2>&1 | grep -oE '\-W[a-z]+' | sort -u

# ── Build: Release (different defines) ───────────────────────────────────────
p_section "Build: Release (different defines)"

cmake -S . -B build_release -DCMAKE_BUILD_TYPE=Release 2>&1 | tail -5
cmake --build build_release 2>&1 | tail -2
echo ""
./build_release/flagsdemo

# ── Disable warnings ──────────────────────────────────────────────────────────
p_section "Build: Warnings Disabled"

cmake -S . -B build_nowarnings -DENABLE_WARNINGS=OFF 2>&1 | tail -5
cmake --build build_nowarnings --verbose 2>&1 | grep -oE '\-W[a-z]+' | sort -u | head -5 || \
  p_info "(no -W flags — warnings disabled)"

# ── AddressSanitizer ──────────────────────────────────────────────────────────
p_section "AddressSanitizer (optional)"

p_info "Enable ASan to detect memory bugs at runtime:"
p_cmd "cmake -S . -B build_asan -DCMAKE_BUILD_TYPE=Debug -DENABLE_ASAN=ON"
p_info ""
p_info "When you run the binary, ASan prints detailed reports for:"
p_box "  • Use-after-free          • Stack buffer overflow"
p_box "  • Heap buffer overflow    • Memory leaks"
p_info ""
p_info "(Not running now to keep the tutorial output clean)"

# ── target_link_options ────────────────────────────────────────────────────────
p_section "Bonus: target_link_options"

p_info "You can also add flags to the LINKER step:"
p_info ""
p_box "  target_link_options(myapp PRIVATE"
p_box "      -Wl,--as-needed    # don't link unused shared libs"
p_box "      -Wl,-rpath,\$ORIGIN  # find .so relative to the executable"
p_box "  )"
p_info ""
p_info "Use this for linker flags that don't affect compilation."

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build build_release build_nowarnings

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 12 Summary"

p_ok "target_compile_options() — raw compiler flags (-Wall, -O2, etc.)"
p_ok "target_compile_definitions() — preprocessor defines (-DFOO=1)"
p_ok "Always use PRIVATE for warnings — don't leak them to consumers"
p_ok "option() — user-overridable boolean: cmake -DENABLE_X=OFF"
p_ok "Generator expressions for per-compiler flags: \$<\$<CXX_COMPILER_ID:GNU>:-Wall>"
p_ok "\$<\$<CONFIG:Debug>:DEFINE=1> — build-type-conditional defines"
p_ok "target_link_options() — flags for the linker step"
echo ""
p_info "Next: cd ../step13_variables_cache && bash tutorial.sh"
echo ""
