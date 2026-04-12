cmake_minimum_required(VERSION 3.15)

# VERSION sets PROJECT_VERSION, PROJECT_VERSION_MAJOR/MINOR/PATCH automatically.
# LANGUAGES keyword is required when using VERSION or other keyword arguments.
project(InstallDemo
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Defines platform-correct install path variables (GNU/FHS conventions):
#   CMAKE_INSTALL_BINDIR     → bin/
#   CMAKE_INSTALL_LIBDIR     → lib/ (or lib64/ on some distros)
#   CMAKE_INSTALL_INCLUDEDIR → include/
include(GNUInstallDirs)

# ── Library ─────────────────────────────────────────────────────────────────────

add_library(mylib SHARED mylib.cpp)

# Two generator expressions for different build contexts:
#   BUILD_INTERFACE  — used when other targets in THIS build link mylib
#   INSTALL_INTERFACE — recorded in the exported target after cmake --install
target_include_directories(mylib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(mylib PUBLIC cxx_std_17)

# ── Executable ──────────────────────────────────────────────────────────────────

add_executable(myapp main.cpp)

target_link_libraries(myapp PRIVATE mylib)

# Embed the installed lib dir into the binary's RPATH so the dynamic linker
# finds libmylib.so without LD_LIBRARY_PATH.
# $ORIGIN/../lib: relative to the executable's location (bin/ → ../lib/).
set_target_properties(myapp PROPERTIES
    INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}"
)

# ── Install rules ───────────────────────────────────────────────────────────────

# RUNTIME → executables + .dll on Windows → PREFIX/bin/
# LIBRARY → .so/.dylib on Linux/macOS    → PREFIX/lib/
# ARCHIVE → .a and .lib import stubs     → PREFIX/lib/
install(TARGETS mylib myapp
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Trailing slash on "include/" copies its CONTENTS (not the directory itself):
# include/mylib.h → PREFIX/include/mylib.h  (not .../include/include/mylib.h).
# FILES_MATCHING PATTERN "*.h" skips non-header files.
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

# message() severity: STATUS (stdout --), WARNING (stderr), FATAL_ERROR (aborts)
message(STATUS "Install prefix : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  bin/         : ${CMAKE_INSTALL_FULL_BINDIR}")
message(STATUS "  lib/         : ${CMAKE_INSTALL_FULL_LIBDIR}")
message(STATUS "  include/     : ${CMAKE_INSTALL_FULL_INCLUDEDIR}")
