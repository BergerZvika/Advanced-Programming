cmake_minimum_required(VERSION 3.15)
project(CompilerFlags CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Option: let the user enable/disable warnings ──────────────────────────────
# option() creates a BOOL cache variable; override with cmake -DFOO=OFF.
option(ENABLE_WARNINGS "Turn on extra compiler warnings" ON)
option(ENABLE_ASAN      "Enable AddressSanitizer (debug builds only)" OFF)

# ── Target ────────────────────────────────────────────────────────────────────
add_executable(flagsdemo main.cpp)

# ── Compiler warnings ─────────────────────────────────────────────────────────
# PRIVATE: keep warnings out of consumers (third-party libs may not be clean).
# $<$<BOOL:${ENABLE_WARNINGS}>:...> — include flags only if option is ON.
# $<CXX_COMPILER_ID:GNU/Clang/MSVC> — compiler-specific flag selection.
if(ENABLE_WARNINGS)
    target_compile_options(flagsdemo PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
            -Wall        # Enable most common warnings
            -Wextra      # Enable extra warnings not covered by -Wall
            -Wpedantic   # Warn about non-standard C++ constructs
            -Wshadow     # Warn when a variable shadows another in outer scope
            -Wconversion # Warn on implicit type narrowing (int → char)
            -Wnull-dereference  # Warn on potential null pointer dereferences
        >
        $<$<CXX_COMPILER_ID:MSVC>:
            /W4          # Warning level 4 (detailed)
            /WX          # Treat warnings as errors
        >
    )
endif()

# ── AddressSanitizer ──────────────────────────────────────────────────────────
# Detects use-after-free, buffer overflows, leaks, double-free.
# Requires both compile AND link flags. Only useful in Debug builds.
# -fno-omit-frame-pointer: preserves stack frames for readable ASan traces.
if(ENABLE_ASAN)
    target_compile_options(flagsdemo PRIVATE -fsanitize=address -fno-omit-frame-pointer)
    target_link_options(flagsdemo    PRIVATE -fsanitize=address)
endif()

# ── Preprocessor defines ──────────────────────────────────────────────────────
# Adds -D flags. PRIVATE keeps defines local; PUBLIC propagates to consumers.
target_compile_definitions(flagsdemo PRIVATE
    APP_NAME="FlagsDemo"    # string macro: accessed as APP_NAME in C++ code
    APP_VERSION=12          # integer macro: accessed as APP_VERSION
    # NDEBUG is set automatically when CMAKE_BUILD_TYPE=Release
)

# ── Build-type-specific defines ───────────────────────────────────────────────
# $<CONFIG:Debug> is 1 in Debug builds, 0 otherwise.
target_compile_definitions(flagsdemo PRIVATE
    $<$<CONFIG:Debug>:DEBUG_BUILD=1>
    $<$<CONFIG:Release>:RELEASE_BUILD=1>
)

# ── Print a summary at configure time ─────────────────────────────────────────
message(STATUS "")
message(STATUS "=== Step 12: Compiler Flags ===")
message(STATUS "  ENABLE_WARNINGS : ${ENABLE_WARNINGS}")
message(STATUS "  ENABLE_ASAN     : ${ENABLE_ASAN}")
message(STATUS "  Build type      : ${CMAKE_BUILD_TYPE}")
message(STATUS "")
message(STATUS "  Build:  cmake --build build")
message(STATUS "  Run:    ./build/flagsdemo")
message(STATUS "")
