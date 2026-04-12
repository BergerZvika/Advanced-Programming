#!/bin/bash
# =============================================================================
# tutorial.sh — Step 7: FetchContent
# Covers FetchContent_Declare, FetchContent_MakeAvailable, GIT_SHALLOW,
# namespaced targets, and the _deps/ cache directory.
# NOTE: First run downloads ~10 MB from GitHub.
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
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 7 — FetchContent: Auto-Download Dependencies")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

p_section "Goal of This Step"

p_info "Almost every real project uses third-party libraries."
p_info "Learn how CMake's FetchContent module downloads and integrates"
p_info "external dependencies without requiring a system install."

# ── The problem ───────────────────────────────────────────────────────────────
p_section "The Problem: Managing External Dependencies"

p_info "Old approaches:"
p_box "  • Copy source into your repo  → repo bloat, hard to update"
p_box "  • Require system install      → breaks portability, CI pain"
p_box "  • Git submodules              → messy, clones full history"
p_info ""
p_info "FetchContent (CMake 3.11+):"
p_box "  • Downloads only at configure time (cached for subsequent runs)"
p_box "  • Pin to an exact version (tag or SHA)"
p_box "  • No system install needed — anyone can clone & build"
p_box "  • The downloaded library is built AS PART OF your project"

# ── CMakeLists.txt walkthrough ────────────────────────────────────────────────
p_section "CMakeLists.txt — Line by Line"

echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""

p_info "include(FetchContent)"
p_box "  Loads the FetchContent module (built into CMake)."
p_box "  Provides: FetchContent_Declare() and FetchContent_MakeAvailable()."
p_box "  No internet access yet — just loads the CMake commands."
p_info ""

p_info "FetchContent_Declare(nlohmann_json ...)"
p_box "  REGISTERS the dependency — still no download."
p_box ""
p_box "  Arguments:"
p_box "    nlohmann_json         → your chosen name (any identifier)"
p_box "    GIT_REPOSITORY <url>  → where to clone from"
p_box "    GIT_TAG v3.11.3       → which commit/tag to check out"
p_box "                           Always pin to a TAG or SHA, not 'main'!"
p_box "                           Branches change; tags are permanent."
p_box "    GIT_SHALLOW TRUE      → fetch only the tagged commit"
p_box "                           = git clone --depth=1"
p_box "                           Saves bandwidth: no full history downloaded"
p_info ""

p_info "FetchContent_MakeAvailable(nlohmann_json fmt)"
p_box "  For each dependency:"
p_box "    1. If build/_deps/<name>-src/ exists → use cached source"
p_box "    2. Otherwise → git clone into build/_deps/<name>-src/"
p_box "    3. Run add_subdirectory() on the downloaded source"
p_box "       → creates CMake targets from the library's CMakeLists.txt"
p_info ""

p_info "target_link_libraries(fetchapp PRIVATE nlohmann_json::nlohmann_json fmt::fmt)"
p_box "  The :: (double colon) syntax means 'namespaced IMPORTED target'."
p_box ""
p_box "  Why :: instead of just 'fmt'?"
p_box "    If 'fmt' doesn't exist as a target, CMake treats it as a linker"
p_box "    flag (-lfmt) and silently continues — hard to debug."
p_box "    If 'fmt::fmt' doesn't exist, CMake gives an IMMEDIATE ERROR."
p_box "    The :: syntax guarantees the target must be defined."

# ── Where files go ────────────────────────────────────────────────────────────
p_section "Where FetchContent Puts Files"

p_box "  build/"
p_box "  └── _deps/"
p_box "      ├── nlohmann_json-src/       ← cloned source (read-only, don't edit)"
p_box "      ├── nlohmann_json-build/     ← compiled artifacts"
p_box "      ├── nlohmann_json-subbuild/  ← CMake's internal download project"
p_box "      ├── fmt-src/"
p_box "      ├── fmt-build/"
p_box "      └── fmt-subbuild/"
p_info ""
p_info "On re-runs, CMake checks if GIT_TAG changed."
p_info "If not, the source dir is reused — no re-download."

# ── Build ─────────────────────────────────────────────────────────────────────
p_section "Build (First Run Downloads Dependencies)"

cd "$STEP_DIR"
rm -rf build

p_info "First configure — you'll see FetchContent downloading:"
p_info ""
cmake -S . -B build 2>&1
p_info ""
cmake --build build -j4 2>&1

p_info ""
p_cmd "./build/fetchapp"
echo ""
./build/fetchapp

# ── Inspect the downloaded deps ───────────────────────────────────────────────
p_section "Inspect the Downloaded Dependencies"

p_cmd "ls build/_deps/"
ls build/_deps/ 2>/dev/null || p_info "(dirs not found)"

p_info ""
p_info "The second configure is fast because sources are already there:"
time cmake -S . -B build 2>&1 | tail -2

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 7 Summary"

p_ok "include(FetchContent) — loads the module, no download yet"
p_ok "FetchContent_Declare() — registers a dep: name, URL, tag"
p_ok "GIT_TAG — always pin to a tag or SHA, never a branch"
p_ok "GIT_SHALLOW TRUE — download only the tagged commit (saves bandwidth)"
p_ok "FetchContent_MakeAvailable() — download (once) + add_subdirectory"
p_ok "Use namespaced targets (fmt::fmt) — errors immediately if not found"
p_ok "Cached in build/_deps/ — subsequent runs reuse the download"
echo ""
p_info "Next: cd ../step8_testing && bash tutorial.sh"
echo ""
