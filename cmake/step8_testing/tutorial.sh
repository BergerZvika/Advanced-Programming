#!/bin/bash
# =============================================================================
# tutorial.sh — Step 8: Testing with CTest + Catch2
# Covers enable_testing, add_test, catch_discover_tests, and all ctest options.
# NOTE: First run downloads Catch2 from GitHub (~2 MB).
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
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 8 — Testing: CTest + Catch2")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

p_section "Goal of This Step"

p_info "Every serious project needs automated tests."
p_info "Learn how CMake's CTest infrastructure works and how Catch2"
p_info "integrates to register individual test cases automatically."

# ── CTest vs Catch2 ───────────────────────────────────────────────────────────
p_section "CTest vs Catch2 — What Each Does"

p_box "  CTest (built into CMake)"
p_box "    CMake's test RUNNER."
p_box "    Runs registered test executables, captures output, reports pass/fail."
p_box "    Knows nothing about test CASES inside a binary — just runs it."
p_box "    Added with: enable_testing() + add_test()"
p_info ""
p_box "  Catch2"
p_box "    A C++ testing FRAMEWORK."
p_box "    Provides TEST_CASE(), REQUIRE(), CHECK(), SECTION() macros."
p_box "    Each TEST_CASE becomes a named unit."
p_box "    catch_discover_tests() bridges Catch2 → CTest:"
p_box "      it asks the binary to list its test cases, then registers"
p_box "      each one as a separate CTest test."
p_info ""
p_info "Together: Catch2 writes the tests, CTest runs and reports them."

# ── CMakeLists.txt walkthrough ────────────────────────────────────────────────
p_section "Root CMakeLists.txt"

echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""

p_info "add_library(mathlib STATIC src/math.cpp)"
p_box "  Compiles math functions as a STATIC library."
p_box "  Both test binaries link mathlib — we compile it once, link twice."
p_box "  If we listed math.cpp in each test's add_executable(), we'd"
p_box "  compile it twice (once per test target)."
p_info ""

p_info "target_include_directories(mathlib PUBLIC src)"
p_box "  PUBLIC → test binaries that link mathlib get -Isrc/ automatically."
p_box "  They can write #include \"math.hpp\" without any extra setup."
p_info ""

p_info "enable_testing()"
p_box "  MUST be in the ROOT CMakeLists.txt."
p_box "  Activates CTest for this directory and ALL subdirectories."
p_box "  If you put it only in tests/CMakeLists.txt, 'ctest' run from"
p_box "  the build root finds ZERO tests."
p_info ""

p_info "add_subdirectory(tests)"
p_box "  Must come AFTER enable_testing() and AFTER mathlib is defined."

# ── tests/CMakeLists.txt ──────────────────────────────────────────────────────
p_section "tests/CMakeLists.txt"

echo ""
cat "$STEP_DIR/tests/CMakeLists.txt"
echo ""

p_info "Catch2::Catch2WithMain"
p_box "  Links Catch2 WITH a pre-built main()."
p_box "  Your test file only needs TEST_CASE blocks — no main() needed."
p_box "  Alternative: Catch2::Catch2 (you write your own main())."
p_info ""

p_info "catch_discover_tests(test_basic)"
p_box "  Runs: ./test_basic --list-test-names-only"
p_box "  Gets back: 'factorial - normal cases', 'factorial - negative input', ..."
p_box "  Calls add_test() for each one."
p_box "  Result: ctest shows individual test cases, not just one binary."
p_box "  You can run a single failing case with: ctest -R 'factorial'"

# ── Build and run ─────────────────────────────────────────────────────────────
p_section "Build and Run"

cd "$STEP_DIR"
rm -rf build

cmake -S . -B build 2>&1
cmake --build build -j4 2>&1

p_info ""
p_info "Run all tests:"
p_cmd "ctest --test-dir build"
echo ""
ctest --test-dir build 2>&1

# ── More ctest options ────────────────────────────────────────────────────────
p_section "More ctest Options"

p_info "Verbose output (show each test's stdout):"
p_cmd "ctest --test-dir build -V"
echo ""
ctest --test-dir build -V 2>&1

p_info ""
p_info "Run only tests matching 'factorial':"
p_cmd "ctest --test-dir build -R factorial"
echo ""
ctest --test-dir build -R factorial 2>&1

p_info ""
p_info "Parallel test execution:"
p_cmd "ctest --test-dir build -j4"
ctest --test-dir build -j4 2>&1

p_info ""
p_info "Show output only for failing tests (best for CI):"
p_cmd "ctest --test-dir build --output-on-failure"
ctest --test-dir build --output-on-failure 2>&1

# ── Run a test binary directly ────────────────────────────────────────────────
p_section "Run a Test Binary Directly"

p_info "Bypass CTest entirely — use Catch2's output directly:"
p_info ""
p_cmd "./build/tests/test_basic"
echo ""
./build/tests/test_basic 2>&1 || true

p_info ""
p_info "Filter to a specific tag:"
p_cmd './build/tests/test_basic "[factorial]"'
./build/tests/test_basic "[factorial]" 2>&1 || true

p_info ""
p_info "List all tests in the binary:"
p_cmd "./build/tests/test_basic --list-tests"
./build/tests/test_basic --list-tests 2>&1 || true

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 8 Summary"

p_ok "enable_testing() must be in the ROOT CMakeLists.txt"
p_ok "Build math as a library — compile once, link into multiple test targets"
p_ok "Catch2::Catch2WithMain — provides main(), you just write TEST_CASE blocks"
p_ok "catch_discover_tests() — registers each TEST_CASE as a separate CTest test"
p_ok "ctest --test-dir build — run all tests"
p_ok "ctest -V — verbose; ctest -R pattern — filter; ctest -j4 — parallel"
p_ok "Run test binary directly for Catch2's richer output format"
echo ""
p_info "Next: cd ../step9_install && bash tutorial.sh"
echo ""
