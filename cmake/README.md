# CMake Tutorial — Complete Step-by-Step Guide

A hands-on CMake tutorial from a single source file all the way to
external dependencies, testing, install rules, compiler flags, and
generated headers. Every step has a **runnable `tutorial.sh`** script
that explains each concept interactively, plus a working `CMakeLists.txt`
with detailed inline comments.

---

## How to Use This Tutorial

Every step has two things:

1. **`tutorial.sh`** — run this first. It explains every concept, walks
   through each line of the CMakeLists.txt, and runs the build so you
   see real output.
2. **`CMakeLists.txt`** — the working build file with detailed inline
   comments on every line and flag.

```bash
# Start here — concepts before any code:
bash step0_concepts/cmake_intro.sh

# Then work through each step:
bash step1_hello_world/tutorial.sh
bash step2_multiple_files/tutorial.sh
# ... and so on
```

---

## Prerequisites

```bash
# Install on Ubuntu/Debian
sudo apt update && sudo apt install cmake build-essential git
#   cmake           → the CMake tool itself
#   build-essential → gcc, g++, make, and core headers
#   git             → required by FetchContent (steps 7-8-10-11)

# Verify (need CMake 3.15+)
cmake --version   # prints cmake version 3.x.y
gcc --version     # prints gcc (Ubuntu ...) x.y.z
g++ --version     # prints g++ (Ubuntu ...) x.y.z
```

---

## Tutorial Overview

| Step | Directory | Script | Topic |
|------|-----------|--------|-------|
| 0 | `step0_concepts/` | `cmake_intro.sh` | What CMake is, 3 phases, generators, cache, target model |
| 1 | `step1_hello_world/` | `tutorial.sh` | Minimum CMakeLists.txt, configure/build/run cycle |
| 2 | `step2_multiple_files/` | `tutorial.sh` | Multiple source files, explicit lists vs GLOB |
| 3 | `step3_include_dirs/` | `tutorial.sh` | target_include_directories, PRIVATE/PUBLIC/INTERFACE |
| 4 | `step4_libraries/` | `tutorial.sh` | add_library (STATIC/SHARED), add_subdirectory, transitive deps |
| 5 | `step5_multilang/` | `tutorial.sh` | Mixed C/C++, standards, EXTENSIONS OFF, extern "C" |
| 6 | `step6_modular/` | `tutorial.sh` | Multi-level subdirectories, target_compile_features |
| 7 | `step7_fetchcontent/` | `tutorial.sh` | FetchContent, GIT_SHALLOW, namespaced targets |
| 8 | `step8_testing/` | `tutorial.sh` | CTest, Catch2, catch_discover_tests, ctest flags |
| 9 | `step9_install/` | `tutorial.sh` | install(), GNUInstallDirs, BUILD/INSTALL_INTERFACE |
| 10 | `step10_cpp_python/` | `tutorial.sh` | C++ + Python via pybind11 |
| 11 | `step11_cpp_java/` | `tutorial.sh` | C++ + Java via JNI |
| 12 | `step12_compiler_flags/` | `tutorial.sh` | Warnings, defines, option(), per-compiler flags, ASan |
| 13 | `step13_variables_cache/` | `tutorial.sh` | set(), cache, option(), if/else, platform detection |
| 14 | `step14_cpp_java_python/` | — | C++ embedding Python + calling Java (JNI) in one binary |

---

## Project Structure

```
cmake/
├── step0_concepts/         What CMake is; three phases; target model
├── step1_hello_world/      Basic single-file C compilation
├── step2_multiple_files/   Multiple .c files, one executable
├── step3_include_dirs/     Headers in a separate include/ folder
├── step4_libraries/        Static library in a subdirectory
├── step5_multilang/        Mixed C and C++ in one target
├── step6_modular/          Multi-subdirectory modular project
├── step7_fetchcontent/     Auto-download external dependencies
├── step8_testing/          Unit testing with CTest + Catch2
├── step9_install/          Shared library + install rules
├── step10_cpp_python/      C++ library exposed to Python via pybind11
├── step11_cpp_java/        C++ library called from Java via JNI
├── step12_compiler_flags/  Warnings, defines, per-compiler flags, ASan
├── step13_variables_cache/ set(), cache, option(), conditionals, platform detection
└── step14_cpp_java_python/ C++ binary embedding Python + calling Java via JNI
```

---

## Step 1 — Hello World (single C file)

**What you learn:** minimum viable CMakeLists.txt, the configure/build/run workflow.

```bash
cd step1_hello_world

mkdir build
cd build
cmake ..
make
./hello

rm -rf build
cmake -S . -B build
cmake --build build
./build/hello

cmake -S . -B build_debug -DCMAKE_BUILD_TYPE=Debug
cmake -S . -B build_release -DCMAKE_BUILD_TYPE=Release
cmake --build build --verbose
cmake --build build -j4
cmake --help


# Configure: CMake reads CMakeLists.txt and generates build files


cmake -S . -B build
#   cmake          → invoke the cmake tool
#   -S .           → Source directory: where CMakeLists.txt lives (. = current dir)
#   -B build       → Build directory: where generated files and binaries go
#                    Created automatically if it doesn't exist.
#                    Keeping the build dir separate from the source tree is called
#                    an "out-of-source" build — the most important CMake practice.
#                    Never pass the source dir as both -S and -B; that would
#                    scatter build files throughout your source tree.

# Build: compile the code
cmake --build build
#   --build build  → invoke the native build tool (make/ninja) in the build/ dir
#                    CMake acts as a wrapper so the same command works regardless
#                    of whether the generator is Make, Ninja, Xcode, etc.
```

Run the result:
```bash
./build/hello
```

Expected output:
```
Hello from CMake!
This is Step 1: single file compilation.
```

**Bonus — try different generators and build types:**

```bash
# Clean start: remove the entire build directory
rm -rf build
#   Useful when you want to switch generators or when CMakeCache.txt
#   contains stale settings.  Always safe: cmake -S . -B build re-creates it.

# Use Ninja instead of Make (faster incremental builds)
cmake -S . -B build -G Ninja
#   -G Ninja       → Generator: tells CMake which build system to generate files for.
#                    The default on Linux is "Unix Makefiles".
#                    Ninja builds are typically 2-5× faster than Make for
#                    large projects because Ninja has lower overhead and
#                    better parallelism.
#                    Run  cmake --help  to list all generators available on your system.
cmake --build build

# Debug build (no optimisation, debug symbols)
cmake -S . -B build_debug -DCMAKE_BUILD_TYPE=Debug
#   -D<VAR>=<VALUE>           → Define a CMake cache variable.
#                               The -D prefix sets it in CMakeCache.txt, which
#                               persists across cmake re-runs on the same build dir.
#   CMAKE_BUILD_TYPE=Debug    → Controls the compiler flags for all targets:
#                               Debug:   -g -O0         (symbols, no optimisation)
#                               Release: -O3 -DNDEBUG   (max speed, asserts off)
#                               RelWithDebInfo: -O2 -g  (speed + symbols)
#                               MinSizeRel: -Os          (minimum binary size)
cmake --build build_debug

# Release build (full optimisation)
cmake -S . -B build_release -DCMAKE_BUILD_TYPE=Release
cmake --build build_release

# Verbose output — see the exact compiler command for every file
cmake --build build --verbose
#   --verbose (or -v)  → Print each compile and link command as it runs.
#                         Shows the full gcc/g++ invocation with all flags,
#                         include paths (-I), defines (-D), etc.
#                         Invaluable for debugging "why isn't my header found?"

# Parallel build with 4 jobs
cmake --build build -j4
#   -j4 (or --parallel 4)  → Run up to 4 compile jobs simultaneously.
#                             Rule of thumb: use the number of CPU cores
#                             or slightly more (e.g. -j$(nproc)).
#                             Reduces build time roughly proportionally to
#                             the number of independent translation units.

# List all available generators on your machine
cmake --help
#   Prints generators, commands, and options.
#   The "Generators" section lists what's installed (Make, Ninja, Xcode...).
```

---

## Step 2 — Multiple Source Files

**What you learn:** listing multiple `.c` files, why explicit lists beat `file(GLOB)`.

```bash
cd ../step2_multiple_files

cmake -S . -B build
cmake --build build -j4
#   -j4  → parallel build; see Step 1 for explanation

./build/calculator
```

Expected output:
```
3 + 4     = 7
3 * 4     = 12
2 ^ 10    = 1024
5 ^ 3     = 125
```

**Inspect the build:**

```bash
# See which files were compiled and with what flags
cmake --build build --verbose
#   Shows a line like:
#     gcc -Ibuild ... -c main.c -o main.c.o
#     gcc -Ibuild ... -c math_utils.c -o math_utils.c.o
#     gcc ... main.c.o math_utils.c.o -o calculator

# Print all CMake cache variables (without help strings)
cmake -S . -B build -L
#   -L   → list non-advanced cache variables after configuring.
#          Shows user-facing variables like CMAKE_BUILD_TYPE,
#          CMAKE_INSTALL_PREFIX, CMAKE_C_COMPILER, etc.

# Print cache variables including advanced ones, with help text
cmake -S . -B build -LAH
#   -L   → list variables
#   -A   → include "advanced" variables (compiler internals, module paths, etc.)
#   -H   → include the help string for each variable
#   The output is verbose but useful when debugging a configure problem.
```

---

## Step 3 — Header Files & Include Directories

**What you learn:** `target_include_directories`, `PRIVATE` vs `PUBLIC` vs `INTERFACE`.

```bash
cd ../step3_include_dirs

cmake -S . -B build
cmake --build build

./build/strtools
```

Expected output:
```
=== Step 3: Headers in Separate Include Directory ===

Original : hello world
Upper    : HELLO WORLD

Before reverse : CMake is great
After reverse  : taerg si ekamc

'l' count in 'hello world' : 3
```

**Experiment with the compiler:**

```bash
# Use Clang instead of GCC
cmake -S . -B build_clang -DCMAKE_C_COMPILER=clang
#   CMAKE_C_COMPILER=clang  → Override the C compiler.
#                              CMake normally auto-detects gcc.
#                              Set this to clang, clang-14, /usr/bin/clang, etc.
#                              CMAKE_CXX_COMPILER is the equivalent for C++.
#   Important: always set this on the FIRST configure of a build dir.
#   Changing the compiler after a CMakeCache.txt exists may not fully take
#   effect; do  rm -rf build_clang  first to be safe.
cmake --build build_clang

# Generate compile_commands.json (a compilation database)
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
#   CMAKE_EXPORT_COMPILE_COMMANDS=ON  → Write build/compile_commands.json.
#                                        This file lists every source file with its
#                                        exact compiler invocation (flags, defines,
#                                        include paths).  Used by:
#                                          • clangd (language server for VS Code, Vim)
#                                          • clang-tidy (static analysis)
#                                          • include-what-you-use
#                                        Symlink or copy it to the source root:
#                                          ln -s build/compile_commands.json .
cat build/compile_commands.json
#   Shows JSON entries like:
#   { "file": ".../src/main.c",
#     "command": "gcc -Iinclude ... -c src/main.c" }
```

---

## Step 4 — Static & Shared Libraries

**What you learn:** `add_library`, `add_subdirectory`, linking with `target_link_libraries`.

```bash
cd ../step4_libraries

cmake -S . -B build
cmake --build build -j4

./build/vecapp
```

Expected output:
```
=== Step 4: Static & Shared Libraries ===

a      = (1.00, 2.00, 3.00)
b      = (4.00, 5.00, 6.00)
a + b  = (5.00, 7.00, 9.00)
a * 2  = (2.00, 4.00, 6.00)
dot(a,b) = 32.00
|a|      = 3.7417
```

**Switch to SHARED library:**

```bash
# Edit mylib/CMakeLists.txt: change STATIC → SHARED, then:
cmake -S . -B build_shared
cmake --build build_shared

# Check dynamic dependencies of the resulting binary
ldd build_shared/vecapp
#   ldd    → "list dynamic dependencies" (Linux utility)
#            Prints every .so the binary needs at runtime and where
#            the linker will find it.
#   You should see libvec3.so listed.  If vecapp were a STATIC build
#   ldd would show no vec3 dependency — vec3 was merged in at link time.

# List symbols exported by the shared library
nm -D build_shared/libvec3.so | grep vec3
#   nm    → "name list" — print symbol table of an object/library file
#   -D    → show only DYNAMIC symbols (exported in the .so's symbol table)
#           Without -D you'd also see internal symbols.
#   grep vec3  → filter for vec3_ function names
#   Exported symbols are what C code in other .so files can call.
```

**Inspect the link commands:**

```bash
cmake --build build --verbose 2>&1 | grep -E "(link|ar)"
#   2>&1          → redirect stderr to stdout so grep sees it all
#   grep -E       → extended regex; matches lines containing "link" or "ar"
#   "ar"          → the archiver tool that creates .a files (Static ARchive)
#   "link"        → the linker command
```

---

## Step 5 — Mixed C and C++

**What you learn:** multi-language projects, `extern "C"` for C/C++ interop,
`CMAKE_CXX_EXTENSIONS OFF`, per-language standards.

```bash
cd ../step5_multilang

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
#   CMAKE_BUILD_TYPE=Release  → enables -O3 optimisation.
#                               Relevant here because the step uses math-heavy
#                               functions where optimisation is visible.
cmake --build build -j4

./build/multilang
```

Expected output:
```
=== Step 5: Mixed C and C++ ===

C functions:
  fast_sqrt(2)  = 1.414214
  fast_sqrt(9)  = 3.000000
  fast_log2(8)  = 3.000000
  fast_log2(1024) = 10.000000

C++ Stats over {4,7,13,2,1,9,15,6}:
  mean   = 7.125000
  stddev = 4.481270
  median = 6.500000
```

**Check which language flags were used:**

```bash
cmake --build build --verbose 2>&1 | grep -E "\-std=(c|gnu)\++"
#   Grep for the -std=c++17 (or -std=gnu++17) flag.
#   With CMAKE_CXX_EXTENSIONS OFF you should see -std=c++17 (no "gnu").
#   With CMAKE_CXX_EXTENSIONS ON you would see -std=gnu++17.
```

---

## Step 6 — Modular Project (Subdirectories)

**What you learn:** multi-level `add_subdirectory`, library dependency propagation,
`PUBLIC` include paths flowing through the dependency graph.

```bash
cd ../step6_modular

cmake -S . -B build
cmake --build build -j4

./build/apps/geoapp
#   Note the path: apps/ subdirectory, because add_executable() was
#   called in apps/CMakeLists.txt.  CMake places output binaries in a
#   directory that mirrors the source tree structure by default.
```

Expected output:
```
=== Step 6: Modular Project with Subdirectories ===

============================================
  Circle radius         5.000000
  Circle area           78.539816
  Rect (8x3) area       24.000000
  dist(p1, origin)      5.000000
  dist(p1, p2)          3.605551
  p1 in circle?         YES
  p2 in circle?         NO
============================================
```

**Explore the build tree:**

```bash
# List all build targets (executables, libraries, custom targets)
cmake --build build --target help
#   --target help  → prints every target that the build system knows about.
#                    Useful for discovering clean, install, test meta-targets
#                    and any custom targets defined with add_custom_target().

# Generate a dependency graph (requires graphviz)
cmake --graphviz=build/deps.dot -S . -B build
#   --graphviz=<file>  → generate a Graphviz DOT file showing the dependency
#                        graph of all targets (libraries, executables, custom).
#                        Each node is a target; edges are link dependencies.
dot -Tpng build/deps.dot -o build/deps.png
#   dot    → Graphviz layout engine (install: sudo apt install graphviz)
#   -Tpng  → output format: PNG image
#   -o     → output file
#   Open build/deps.png to see geoapp → geometry → io visually.
```

---

## Step 7 — FetchContent (External Dependencies)

**What you learn:** `FetchContent_Declare` + `FetchContent_MakeAvailable` to
auto-download and build `nlohmann/json` and `{fmt}` from GitHub.

> **Note:** First run downloads ~10 MB from GitHub. Subsequent runs use the cache.

```bash
cd ../step7_fetchcontent

# Configure (downloads dependencies on first run)
cmake -S . -B build
#   On first run CMake clones nlohmann/json and fmt into build/_deps/.
#   On subsequent runs it checks if GIT_TAG changed; if not, skips download.
cmake --build build -j4

./build/fetchapp
```

Expected output:
```
=== Step 7: FetchContent - External Dependencies ===

JSON output:
{
  "features": ["fetchcontent", "json", "fmt", "auto-download"],
  "project": "CMake Tutorial",
  "settings": {"debug": false, "parallel": 4},
  "version": 7
}

Squares: [1, 4, 9, 16, 25, 36]
Pi is approximately 3.1415926536

Parsed: name=Alice, score=95.5
```

**Inspect downloaded dependencies:**

```bash
# List what FetchContent downloaded
ls build/_deps/
#   Shows directories like:
#     nlohmann_json-src/    ← the cloned source
#     nlohmann_json-build/  ← its build artifacts
#     nlohmann_json-subbuild/ ← internal CMake download project

ls build/_deps/nlohmann_json-src/
#   The actual nlohmann/json repo contents: include/, tests/, etc.

ls build/_deps/fmt-src/
#   The {fmt} source: src/, include/, test/, etc.
```

**Force re-download:**

```bash
rm -rf build/_deps
cmake --build build -j4
#   Deleting _deps removes the cached sources.
#   The next build triggers a fresh git clone for each dependency.
#   Useful when you suspect the cache is corrupted or you want to
#   pick up a newer patch version.
```

---

## Step 8 — Testing with CTest + Catch2

**What you learn:** `enable_testing()`, `add_test()`, `catch_discover_tests()`,
running tests with `ctest`.

> **Note:** First run downloads Catch2 from GitHub (~2 MB).

```bash
cd ../step8_testing

cmake -S . -B build
cmake --build build -j4

# Run all tests
ctest --test-dir build
#   ctest           → CMake's test runner (bundled with cmake)
#   --test-dir build → look for CTestTestfile.cmake in this directory.
#                      Equivalent to  cd build && ctest, but lets you
#                      run ctest from the source root.
```

Expected output:
```
Test project .../step8_testing/build
    Start 1: factorial - normal cases
1/8 Test #1: factorial - normal cases ..........   Passed    0.00 sec
    Start 2: factorial - negative input returns sentinel
2/8 Test #2: factorial - negative input ...........Passed    0.00 sec
...
100% tests passed, 0 tests failed out of 8
```

**More ctest options:**

```bash
# Verbose: show PASS/FAIL and stdout/stderr for every test
ctest --test-dir build -V
#   -V (or --verbose)  → print each test's output whether it passes or fails.
#                        By default only failed tests print output.

# Run only tests whose name matches a regex pattern
ctest --test-dir build -R "factorial"
#   -R <regex>  → include tests whose name matches the regular expression.
#                 "factorial" matches "factorial - normal cases",
#                 "factorial - negative input", etc.
ctest --test-dir build -R "gcd"
#   Matches only tests with "gcd" in the name.
#   Use -R to quickly re-run a failing subset without waiting for all tests.

# Exclude tests by pattern
ctest --test-dir build -E "edge"
#   -E <regex>  → exclude tests matching this pattern.
#                 Opposite of -R; useful when a group of tests is known broken.

# Show output only for failed tests (ideal for CI logs)
ctest --test-dir build --output-on-failure
#   --output-on-failure  → suppress passing tests' stdout; only print
#                           failing tests' output.  Clean CI logs.

# Run tests in parallel (all CPU cores)
ctest --test-dir build -j4
#   -j4 (or --parallel 4)  → run up to 4 tests simultaneously.
#                             Each test runs in its own process, so there
#                             is no shared state between them.
#                             Use -j$(nproc) to use all available cores.

# Run a specific test binary directly (bypasses CTest, uses Catch2 output)
./build/tests/test_basic
#   Runs the test binary directly, printing Catch2's own formatted output.
#   More readable than ctest output for debugging a specific failing test.

./build/tests/test_basic "[factorial]"
#   Pass a Catch2 tag filter.  Runs only TEST_CASEs tagged with [factorial].
#   Catch2 tags are declared in the test source:  TEST_CASE("...", "[factorial]")

./build/tests/test_edge_cases --list-tests
#   --list-tests  → Catch2 flag; print all test names without running them.
#                   Helpful for discovering what's in a test binary.
```

**Intentionally break a test to see failure output:**

```bash
# Edit src/math.cpp: introduce a bug, rebuild, re-run
cmake --build build -j4
ctest --test-dir build --output-on-failure
#   CMake detects that math.cpp changed and recompiles only what's needed.
#   ctest shows the failing test case(s) with their assertion output.
```

---

## Step 9 — Install Rules

**What you learn:** `install(TARGETS ...)`, `install(DIRECTORY ...)`,
`GNUInstallDirs`, `BUILD_INTERFACE` vs `INSTALL_INTERFACE` generator expressions.

```bash
cd ../step9_install

cmake -S . -B build
cmake --build build

# Run before installing (uses the build-dir binary)
./build/myapp
```

Expected output:
```
=== Step 9: Install Rules ===

repeat('ha', 3)             = hahaha
join(['a','b','c'], '-')    = a-b-c
starts_with('hello','hel')  = true
to_snake_case('CamelCase')  = camel_case
to_snake_case('MyBigClass') = my_big_class
```

**Install to a local prefix (no sudo needed):**

```bash
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=$HOME/.local
#   CMAKE_INSTALL_PREFIX  → root directory where files are installed.
#                           Default: /usr/local (requires sudo on most systems).
#                           $HOME/.local is a user-writable location that many
#                           tools (pip, cargo, go install) already use.
#                           You can set any path: /opt/myapp, /tmp/test, etc.
#   Always set this on the configure step, not the install step, so that
#   install rules using ${CMAKE_INSTALL_PREFIX} resolve correctly.

cmake --build build

cmake --install build
#   cmake --install <build-dir>  → runs the install rules defined in CMakeLists.txt
#                                   (the install() commands).
#   Copies files from the build tree to the install prefix.
#   Equivalent to  make install  or  ninja install  but generator-independent.

# Verify the installed files
ls $HOME/.local/bin/
#   Should contain: myapp

ls $HOME/.local/lib/
#   Should contain: libmylib.so (or libmylib.so.1.0.0)

ls $HOME/.local/include/
#   Should contain: mylib.h

# Run the installed binary
$HOME/.local/bin/myapp
```

**Install to /tmp for inspection (does not require modifying your home dir):**

```bash
cmake --install build --prefix /tmp/cmake_install_test
#   --prefix <path>  → override CMAKE_INSTALL_PREFIX for this one install run.
#                       Useful for inspecting the install layout without
#                       actually installing to your system.
#                       Takes precedence over the cached CMAKE_INSTALL_PREFIX.

find /tmp/cmake_install_test -type f
#   Shows all installed files:
#     /tmp/cmake_install_test/bin/myapp
#     /tmp/cmake_install_test/lib/libmylib.so
#     /tmp/cmake_install_test/include/mylib.hpp
```

**Install only specific components:**

```bash
cmake --install build --component Runtime
#   --component <name>  → install only targets/files that belong to a named
#                          component.  Components are declared with the
#                          COMPONENT keyword in install() rules, e.g.:
#                            install(TARGETS myapp RUNTIME COMPONENT Runtime)
#                            install(TARGETS mylib LIBRARY COMPONENT Devel)
#                          This lets users install only the runtime (.exe + .so)
#                          without the development headers and static lib.
#   This step's CMakeLists.txt doesn't declare components explicitly,
#   so --component Runtime has no effect here — it's shown for reference.
```

---

## Step 10 — C++ + Python (pybind11)

**What you learn:** `pybind11_add_module`, exposing C++ classes and functions to
Python, `POSITION_INDEPENDENT_CODE`, `Development.Module`, the `PYTHONPATH` trick
for running demo scripts without installing, and where C++ speedups actually matter.

### Prerequisites
```bash
sudo apt install python3-dev
#   python3-dev  → installs Python.h and the extension module stub.
#                  Required for find_package(Python3 COMPONENTS Development.Module).
#                  pybind11 is fetched automatically from GitHub — no system install needed.
```

### Build & run

```bash
cd step10_cpp_python

# Configure (downloads pybind11 on first run — ~5 MB)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
#   Release  → enables -O3 and -DNDEBUG.
#              Important here: the step includes a C++ vs Python speed benchmark.
#              Without optimisation the C++ advantage is partially hidden.

# Build the extension module (.so)
cmake --build build -j4

# Run the Python demo (sets PYTHONPATH automatically via the run_demo target)
cmake --build build --target run_demo
#   --target run_demo  → build and then execute the custom "run_demo" target.
#                         The target uses  cmake -E env PYTHONPATH=build
#                         so Python can find myvec3.cpython-...so in the
#                         build directory without installing it.
```

Expected output (abridged):
```
====================================================
  Step 10: C++ library called from Python (pybind11)
====================================================

--- Vec3 class ---
a            = Vec3(1.000000, 2.000000, 3.000000)
a.dot(b)     = 32.0
a.cross(b)   = Vec3(-3.000000, 6.000000, -3.000000)
|a|          = 3.741657
angle(a,b)   = 0.225726 rad  (12.9332°)

--- Stats (C++ backend) ---
mean       = 5.0
stddev     = 2.000000

--- Performance: C++ vs Python (stddev on 10k-element list × 1000 calls) ---
C++ stddev  : 58 ms
Python      : 860 ms
Speedup     : ~15x  (C++ is faster)
```

python3 demo.py
cp build/myvec3*.so .
python3 demo.py

**Explore the extension module from Python directly:**

```bash
cd build
PYTHONPATH=. python3
#   PYTHONPATH=.  → add the current directory (build/) to Python's module
#                   search path for this one command.
#                   Python finds myvec3.cpython-310-x86_64-linux-gnu.so here.

>>> import myvec3
>>> help(myvec3)           # shows the module docstring and all exposed names
>>> help(myvec3.Vec3)      # shows the Vec3 class methods and signatures
>>> v = myvec3.Vec3(1, 2, 3)
>>> v.norm()               # calls C++ Vec3::norm() from Python
>>> myvec3.stats.mean([1,2,3,4,5])
```

**Inspect the generated .so:**

```bash
# See what Python ABI suffix was used in the filename
ls build/*.so
#   Output: myvec3.cpython-310-x86_64-linux-gnu.so
#   The suffix encodes: CPython version (310=3.10), architecture (x86_64),
#   OS (linux), ABI tag (gnu).  Python's import system checks for this exact
#   suffix, which is why the module name in Python is just "myvec3".

# See the Python initialisation function exported by the module
nm -D build/myvec3*.so | grep PyInit
#   nm   → name list: print symbol table
#   -D   → show only dynamic (exported) symbols
#   grep PyInit  → filter for the module init function
#   Output should be:  T  PyInit_myvec3
#   "T" means the symbol is in the text (code) section and is exported.
#   Python calls PyInit_myvec3() when  import myvec3  executes.
```

**Change build type to Debug:**

```bash
cmake -S . -B build_debug -DCMAKE_BUILD_TYPE=Debug
#   Debug  → no -O3, adds -g debug symbols.
#             Compile is faster, but the benchmark will show no speedup
#             because the C++ code is unoptimised.
cmake --build build_debug -j4
cmake --build build_debug --target run_demo
```

**How the static library → shared module works:**

```
vec3.cpp  ──→  libvec3lib.a  (POSITION_INDEPENDENT_CODE ON = -fPIC)
                    │
bindings.cpp ──→  myvec3.cpython-310-x86_64-linux-gnu.so
                    │
                Python import system loads this .so
```

---

## Step 11 — C++ + Java (JNI)

**What you learn:** `find_package(Java)`, `find_package(JNI)`, `include(UseJava)`,
`add_jar(GENERATE_NATIVE_HEADERS)`, `JNIEXPORT`/`JNICALL` naming convention,
`System.loadLibrary`, JNI type mapping, string and array marshalling between Java and C++.

### Prerequisites

```bash
sudo apt install default-jdk
#   default-jdk  → installs OpenJDK (typically 17 or 21 on modern Ubuntu).
#                  Provides: javac, java, and the JNI headers (jni.h, jni_md.h).

javac -version   # should print javac 17.x or higher
```

### Build & run

```bash
cd ../step11_cpp_java

# Configure (auto-detects JAVA_HOME from javac location)
cmake -S . -B build
#   CMake finds javac via find_package(Java REQUIRED COMPONENTS Development).
#   If JAVA_HOME is not set, the CMakeLists.txt auto-detects it from
#   javac's real path (following symlinks).

# Build: compiles Java → .jar, generates JNI header, compiles C++ → .so
cmake --build build -j4
#   Three things happen in dependency order:
#   1. javac compiles .java → .class → TutorialJar.jar
#      and  javac -h  generates com_tutorial_NativeMath.h
#   2. g++ compiles native_math.cpp (which #includes that generated .h)
#      → libnativemath.so
#   3. Both artifacts are placed in the build directory.

# Run (sets java.library.path so the JVM finds libnativemath.so)
cmake --build build --target run
#   --target run  → executes the custom "run" target which runs:
#                    java -Djava.library.path=build -jar TutorialJar.jar
#                   -Djava.library.path=build  tells the JVM to search
#                   the build/ directory for libnativemath.so when
#                   System.loadLibrary("nativemath") is called.
```

Expected output:
```
============================================
  Step 11: C++ via JNI called from Java
============================================

--- Arithmetic (C++ implementation) ---
  add(7, 5)                    = 12
  multiply(6, 7)               = 42
  power(2.0, 10)               = 1024.0
...
```

  java -Djava.library.path=build -jar build/TutorialJar.jar

**Inspect the generated JNI header:**

```bash
cat build/jni_headers/com_tutorial_NativeMath.h
#   Shows auto-generated C function signatures, e.g.:
#     JNIEXPORT jint JNICALL Java_com_tutorial_NativeMath_add
#         (JNIEnv *, jclass, jint, jint);
#
#   JNIEXPORT  → expands to __attribute__((visibility("default"))) on GCC.
#                 Ensures the symbol is exported from the .so and visible
#                 to the JVM's dlsym() call.
#
#   JNICALL    → calling convention; empty on Linux x86, __stdcall on Windows.
#                 Must match exactly between the header and the .cpp implementation.
#
#   Java_com_tutorial_NativeMath_add
#     Function naming rule (MUST be exact):
#       "Java_"  +  package dots→underscores  +  "_"  +  class  +  "_"  +  method
#       Java_ + com_tutorial_ + NativeMath_ + add
#     Any mismatch causes UnsatisfiedLinkError at runtime.
```

**Inspect the jar manifest:**

```bash
unzip -p build/TutorialJar.jar META-INF/MANIFEST.MF
#   unzip -p  → extract to stdout instead of a file
#   META-INF/MANIFEST.MF  → the JAR manifest file
#   You should see:  Main-Class: com.tutorial.Main
#   This is what makes  java -jar TutorialJar.jar  work without specifying
#   the main class on the command line.
```

**Run manually (without the CMake run target):**

```bash
java -Djava.library.path=build -jar build/TutorialJar.jar
#   java                          → JVM executable
#   -Djava.library.path=build     → System property that tells System.loadLibrary()
#                                   where to find libnativemath.so.
#                                   Equivalent to LD_LIBRARY_PATH on Linux, but
#                                   scoped to JVM native library loading only.
#   -jar build/TutorialJar.jar    → run the jar using its Main-Class manifest entry.
```

**JNI naming rule** — critical for matching Java ↔ C++:

```
Java method:  com.tutorial.NativeMath.reverseString(String)
C++ function: Java_com_tutorial_NativeMath_reverseString(JNIEnv*, jclass, jstring)
              ^─── always  ^─── dots→underscores    ^─── method name
```

**JNI type mapping cheatsheet:**

```
Java type    │ JNI type       │ C++ usage
─────────────┼────────────────┼──────────────────────────────────────────
int          │ jint           │ 32-bit int, use directly
long         │ jlong          │ 64-bit int (long long), use directly
double       │ jdouble        │ double, use directly
boolean      │ jboolean       │ return JNI_TRUE or JNI_FALSE
String       │ jstring        │ GetStringUTFChars / ReleaseStringUTFChars
double[]     │ jdoubleArray   │ GetDoubleArrayElements / ReleaseDoubleArrayElements
             │                │ NewDoubleArray + SetDoubleArrayRegion (to return)
```

---

## Step 12 — Compiler Flags, Warnings, and Defines

**What you learn:** `target_compile_options`, `target_compile_definitions`, `option()`,
generator expressions for per-compiler flags, and AddressSanitizer.

```bash
cd step12_compiler_flags
bash tutorial.sh       # interactive walkthrough
```

Or run manually:
```bash
# Default: warnings ON, Debug build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/flagsdemo

# Disable warnings
cmake -S . -B build_nw -DENABLE_WARNINGS=OFF
cmake --build build_nw

# Enable AddressSanitizer
cmake -S . -B build_asan -DCMAKE_BUILD_TYPE=Debug -DENABLE_ASAN=ON
cmake --build build_asan
./build_asan/flagsdemo

# Release build (different defines)
cmake -S . -B build_rel -DCMAKE_BUILD_TYPE=Release
cmake --build build_rel
./build_rel/flagsdemo
```

**Key commands introduced:**

```cmake
# Raw compiler flags — PRIVATE so they don't leak to consumers
target_compile_options(app PRIVATE -Wall -Wextra -Wpedantic)

# Per-compiler flags with generator expressions
target_compile_options(app PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
        -Wall -Wextra>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

# Preprocessor defines
target_compile_definitions(app PRIVATE
    APP_NAME="MyApp"
    VERSION=2
    $<$<CONFIG:Debug>:DEBUG_BUILD=1>   # only in Debug
)

# AddressSanitizer (both compile and link need the flag)
target_compile_options(app PRIVATE -fsanitize=address)
target_link_options(app    PRIVATE -fsanitize=address)

# User-controllable boolean option
option(ENABLE_FEATURE "Enable feature X" OFF)
# Override: cmake -DENABLE_FEATURE=ON -S . -B build
```

---

## Step 13 — Variables and the Cache

**What you learn:** `set()`, cache variables, `option()`, `if/else`, platform and compiler
detection, string and list operations.

```bash
cd step13_variables_cache
bash tutorial.sh       # interactive walkthrough
```

Or run manually:
```bash
cmake -S . -B build
cmake --build build
./build/varsdemo

# Override a cache variable
cmake -S . -B build_rep -DGREETING_REPEAT=5
cmake --build build_rep
./build_rep/varsdemo

# List all cache variables with help text
cmake -S . -B build -LAH
```

**Key concepts:**

```cmake
# Regular variable — lives only for this cmake run
set(MY_SOURCES main.cpp utils.cpp)

# Cache variable — stored in CMakeCache.txt, survives between runs
# Types: STRING  BOOL  PATH  FILEPATH  INTERNAL
set(APP_PORT 8080 CACHE STRING "TCP port the server listens on")

# Boolean cache variable (option() is shorthand)
option(ENABLE_TLS "Enable TLS support" ON)
# Equivalent to: set(ENABLE_TLS ON CACHE BOOL "Enable TLS support")

# Conditionals
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Building for Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Building for Windows")
endif()

# Compiler detection
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(app PRIVATE -Wall)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(app PRIVATE /W4)
endif()

# String operations
string(TOUPPER "${PROJECT_NAME}" NAME_UPPER)
string(TIMESTAMP BUILD_DATE "%Y-%m-%d" UTC)

# List operations
list(APPEND SOURCES extra.cpp)
list(REMOVE_ITEM SOURCES unused.cpp)
```

---

## Step 14 — C++ + Java + Python in One Binary

**What you learn:** embedding the Python interpreter (`Python3::Python` / `libpython`),
calling Java code from C++ via JNI (`libjvm`), `find_package(Python3 COMPONENTS Development)`,
`add_jar(GENERATE_NATIVE_HEADERS)`, `BUILD_RPATH` for non-standard `.so` paths.

### Prerequisites
```bash
sudo apt install python3-dev default-jdk
#   python3-dev  → Python.h and libpython.so (embedding, not just extension modules)
#   default-jdk  → javac, java, jni.h, jni_md.h
```

### Build & run

```bash
cd step14_cpp_java_python

cmake -S . -B build
cmake --build build -j4

./build/combined
```

Expected output:
```
[Python] Hello from Python, World!
[Java]   Hello from Java, World!
```

**How it works:**

```
Hello.py  ──xxd -i──→  hello_py_data.h   (compile-time, bytes baked into binary)
Hello.java ─add_jar──→  HelloJar.jar      (compile-time, copied next to binary)

main.cpp
  ├── PyRun_SimpleString(Hello_py)  → runs embedded Hello.py, defines greet()
  │   PyObject_CallFunction(greet)  → calls greet("World"), returns Python str
  └── JNI_CreateJavaVM()            → loads HelloJar.jar, calls Hello.greet()
```

**Compile-time embedding with xxd:**

```cmake
# xxd -i Hello.py generates a C header with the file's bytes as a char array:
#   unsigned char Hello_py[] = { 0x64, 0x65, 0x66, ... };
#   unsigned int  Hello_py_len = 42;
# No .py file is needed on disk at runtime — the source is inside the binary.
add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/hello_py_data.h
    COMMAND xxd -i Hello.py ${CMAKE_CURRENT_BINARY_DIR}/hello_py_data.h
    DEPENDS Hello.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Embedding Hello.py → hello_py_data.h"
)
```

```cpp
// main.cpp — use the embedded Python source
#include "hello_py_data.h"   // Hello_py[], Hello_py_len

// Hello_py is not null-terminated — copy into std::string first
std::string src(reinterpret_cast<const char*>(Hello_py), Hello_py_len);
PyRun_SimpleString(src.c_str());          // defines greet() in __main__

PyObject* fn  = PyObject_GetAttrString(PyImport_AddModule("__main__"), "greet");
PyObject* res = PyObject_CallFunction(fn, "s", "World");
// → "Hello from Python, World!"
```

```cmake
# Embed Python interpreter (requires libpython, not just .so extension stub)
find_package(Python3 REQUIRED COMPONENTS Development)
target_link_libraries(combined PRIVATE Python3::Python)

# Embed JVM
find_package(Java 11 REQUIRED COMPONENTS Development)
find_package(JNI REQUIRED)
target_link_libraries(combined PRIVATE ${JNI_LIBRARIES})
target_include_directories(combined PRIVATE ${JNI_INCLUDE_DIRS})

# libjvm.so lives in a non-standard path — embed it in RPATH
set_target_properties(combined PROPERTIES BUILD_RPATH "${_jvm_dir}")
```

---

## Useful CMake Commands (Reference)

```bash
# ── Configure ───────────────────────────────────────────────────────────────────
cmake -S <src> -B <build>
#   -S  → source dir (where CMakeLists.txt is)
#   -B  → build dir (created if absent; stores generated files and binaries)

cmake -S . -B build -G Ninja
#   -G Ninja  → use the Ninja generator instead of the default (Unix Makefiles)

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
#   -D<VAR>=<VAL>  → set a cache variable; persists between cmake re-runs

cmake -S . -B build -DCMAKE_C_COMPILER=clang
#   override the C compiler (use before any configure on this build dir)

cmake -S . -B build -DCMAKE_INSTALL_PREFIX=~
#   set the install root to the user's home directory

cmake -S . -B build -DSOME_OPTION=ON
#   set a project-defined option (declared with option() in CMakeLists.txt)

cmake -S . -B build --fresh
#   --fresh  → delete CMakeCache.txt before configuring (clean slate)
#              Useful when you change compilers or generators

# ── Build ────────────────────────────────────────────────────────────────────────
cmake --build build
#   invoke the underlying build tool (make/ninja) in build/

cmake --build build -j4
#   -j4 (--parallel 4)  → compile up to 4 files simultaneously

cmake --build build --verbose
#   print the exact compiler command for every translation unit

cmake --build build -t clean
#   -t clean  → run the "clean" target: delete all compiled objects and binaries
#               Does NOT delete CMakeCache.txt or generated build files;
#               for a full reset use rm -rf build/.

cmake --build build -t help
#   -t help  → list all available targets in the build system

cmake --build build --target run_demo
#   --target <name>  → build only this named target (and its dependencies)

cmake --build build --config Release
#   --config Release  → relevant for multi-config generators (Visual Studio, Xcode)
#                       where Debug/Release are selected at build time, not configure time

# ── Test ─────────────────────────────────────────────────────────────────────────
ctest --test-dir build
#   --test-dir build  → look for tests registered in build/ (CMake 3.20+)

ctest --test-dir build -V
#   -V  → verbose: print each test's output

ctest --test-dir build -R <pattern>
#   -R  → include only tests matching regex pattern

ctest --test-dir build -E <pattern>
#   -E  → exclude tests matching regex pattern

ctest --test-dir build -j4
#   -j4  → run up to 4 tests in parallel

ctest --test-dir build --output-on-failure
#   print output only for failed tests (clean CI logs)

ctest --test-dir build --rerun-failed
#   only re-run tests that failed in the last run

# ── Install ──────────────────────────────────────────────────────────────────────
cmake --install build
#   install using the prefix configured with -DCMAKE_INSTALL_PREFIX

cmake --install build --prefix /some/path
#   --prefix  → override CMAKE_INSTALL_PREFIX for this install only

cmake --install build --component Runtime
#   install only targets/files that belong to the "Runtime" component

cmake --install build --strip
#   --strip  → strip debug symbols from installed binaries (smaller files)

# ── Inspect ──────────────────────────────────────────────────────────────────────
cmake -S . -B build -L
#   -L   → list user-visible cache variables after configuring

cmake -S . -B build -LA
#   -LA  → list ALL cache variables (including advanced/internal)

cmake -S . -B build -LAH
#   -LAH → all variables with help strings

ccmake build/
#   text-based interactive UI to browse and edit cache variables
#   install: sudo apt install cmake-curses-gui

cmake-gui
#   graphical UI (install: sudo apt install cmake-qt-gui)

# Get help on any built-in CMake module, command, or property
cmake --help-module FindOpenSSL
#   prints the full documentation of the FindOpenSSL module

cmake --help-command target_link_libraries
#   prints the full documentation of target_link_libraries()

cmake --help-property INTERFACE_INCLUDE_DIRECTORIES
#   prints the full documentation of this target property
```

---

## Quick Troubleshooting

| Problem | Solution |
|---------|----------|
| `cmake: command not found` | `sudo apt install cmake` |
| `No CMAKE_C_COMPILER found` | `sudo apt install build-essential` |
| CMakeLists.txt changes ignored | Delete `build/CMakeCache.txt` and re-run cmake |
| Want a clean rebuild | `rm -rf build && cmake -S . -B build` |
| Step 7/8 download fails | Check internet connection; try `cmake -S . -B build --fresh` |
| `ccmake: command not found` | `sudo apt install cmake-curses-gui` |
| `ldd` shows missing .so | `LD_LIBRARY_PATH=./build/mylib:$LD_LIBRARY_PATH ./build/vecapp` |
| Step 10: `python3-dev` not found | `sudo apt install python3-dev` |
| Step 10: `relocation R_X86_64_PC32` | Static lib needs `-fPIC`; add `set_target_properties(mylib PROPERTIES POSITION_INDEPENDENT_CODE ON)` |
| Step 10: `ModuleNotFoundError: myvec3` | Run via `cmake --build build --target run_demo`, or: `PYTHONPATH=build python3 demo.py` |
| Step 11: `Could NOT find JNI` | `JAVA_HOME` not set; install full JDK: `sudo apt install default-jdk` |
| Step 11: `UnsatisfiedLinkError` at runtime | `.so` not on library path; use `-Djava.library.path=build` or `LD_LIBRARY_PATH=build java ...` |
| Step 11: wrong JNI function name | Run `javac -h` to regenerate header and compare to your C++ function names |
