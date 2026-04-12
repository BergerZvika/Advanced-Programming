#!/bin/bash
# =============================================================================
# tutorial.sh — Step 11: C++ + Java via JNI
# Covers find_package(Java), find_package(JNI), include(UseJava), add_jar(),
# GENERATE_NATIVE_HEADERS, add_library(SHARED), and java.library.path.
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
echo -e "${CYAN}║${RESET}${BOLD}$(printf "%-78s" "  Step 11 — C++ + Java via JNI")${RESET}${CYAN}║${RESET}"
echo -e "${CYAN}╚══════════════════════════════════════════════════════════════════════════════╝${RESET}"
echo ""

p_section "Goal of This Step"

p_info "JNI (Java Native Interface) lets Java code call C++ functions."
p_info "You declare methods as 'native' in Java, implement them in C++,"
p_info "and the JVM loads your shared library at runtime."
p_info ""
p_info "CMake orchestrates both sides: compile the .java into a .jar AND"
p_info "compile the .cpp into a .so — with the correct JNI headers automatically."

# ── How JNI works ─────────────────────────────────────────────────────────────
p_section "How JNI Works"

p_box "  1. Java class declares methods with 'native' keyword"
p_box "     public static native int add(int a, int b);"
p_box ""
p_box "  2. javac -h generates a C header from the .class file:"
p_box "     com_tutorial_NativeMath.h  with signature:"
p_box "     JNIEXPORT jint JNICALL Java_com_tutorial_NativeMath_add"
p_box "         (JNIEnv*, jclass, jint, jint);"
p_box ""
p_box "  3. C++ file implements that exact function signature"
p_box ""
p_box "  4. Java loads the shared library at runtime:"
p_box "     System.loadLibrary(\"nativemath\");"
p_box "     → searches java.library.path for libnativemath.so"
p_box ""
p_box "  5. JVM bridges: java call → native C++ function"

# ── Project structure ─────────────────────────────────────────────────────────
p_section "Project Structure"

p_box "  step11_cpp_java/"
p_box "  ├── CMakeLists.txt"
p_box "  └── src/"
p_box "      ├── com/tutorial/"
p_box "      │   ├── NativeMath.java   ← declares native methods"
p_box "      │   └── Main.java         ← calls native methods from Java"
p_box "      └── jni/"
p_box "          └── native_math.cpp   ← C++ implementations"

# ── Java source ───────────────────────────────────────────────────────────────
p_section "Java Source: NativeMath.java"

echo ""
cat "$STEP_DIR/src/com/tutorial/NativeMath.java"
echo ""

p_info "The 'native' keyword:"
p_box "  Tells the JVM: no bytecode body here — look in a native shared library."
p_box "  System.loadLibrary(\"nativemath\") loads libnativemath.so when the class"
p_box "  is first used."
p_info ""
p_info "JNI type mapping:"
p_box "  Java int    → C jint         Java long   → C jlong"
p_box "  Java double → C jdouble      Java boolean→ C jboolean"
p_box "  Java String → C jstring      Java int[]  → C jintArray"
p_box "  Java double[]→ C jdoubleArray"

# ── CMakeLists.txt walkthrough ────────────────────────────────────────────────
p_section "CMakeLists.txt Walkthrough"

echo ""
cat "$STEP_DIR/CMakeLists.txt"
echo ""

p_info "Six steps in the CMakeLists.txt:"
p_info ""
p_info "Step 1 — project(CppJavaDemo CXX Java)"
p_box "   Declare BOTH CXX and Java languages."
p_box "   Java tells CMake to find javac and validate it at configure time."
p_box "   Required before include(UseJava)."
p_info ""
p_info "Step 2 — find_package(Java 11 REQUIRED COMPONENTS Development)"
p_box "   Finds the JDK. '11' = minimum version."
p_box "   'Development' provides both javac AND java."
p_box "   Sets: Java_JAVAC_EXECUTABLE, Java_JAVA_EXECUTABLE, Java_VERSION"
p_info ""
p_info "Step 3 — JAVA_HOME auto-detection"
p_box "   Many systems have symlinks: /usr/bin/javac → /etc/alternatives/javac"
p_box "                               → /usr/lib/jvm/java-17-openjdk-amd64/bin/javac"
p_box "   We REALPATH-resolve javac, strip 'bin/', go up one dir → JDK root."
p_box "   find_package(JNI) uses JAVA_HOME to find jni.h."
p_info ""
p_info "Step 4 — find_package(JNI REQUIRED)"
p_box "   Finds jni.h and jni_md.h using JAVA_HOME."
p_box "   CRITICAL: must come BEFORE include(UseJava)."
p_box "   add_jar(GENERATE_NATIVE_HEADERS) captures JNI_INCLUDE_DIRS at creation time."
p_info ""
p_info "Step 5 — include(UseJava) + add_jar()"
p_box "   UseJava provides add_jar() — CMake's Java compiler support."
p_box "   add_jar(TutorialJar SOURCES ... ENTRY_POINT ... GENERATE_NATIVE_HEADERS ...)"
p_box "     ENTRY_POINT: sets Main-Class in MANIFEST.MF → enables 'java -jar'"
p_box "     GENERATE_NATIVE_HEADERS tutorial-native:"
p_box "       Runs javac -h on classes with native methods"
p_box "       Creates an INTERFACE target 'tutorial-native' carrying:"
p_box "         - include path to generated com_tutorial_NativeMath.h"
p_box "         - JNI_INCLUDE_DIRS (jni.h, jni_md.h)"
p_info ""
p_info "Step 6 — add_library(nativemath SHARED) + target_link_libraries(... tutorial-native)"
p_box "   SHARED because System.loadLibrary() does a runtime dlopen()."
p_box "   Linking tutorial-native propagates both include paths automatically."
p_box "   No manual target_include_directories() needed."

# ── C++ JNI function signatures ───────────────────────────────────────────────
p_section "JNI Function Name Mangling"

p_info "The C++ function name must EXACTLY match the JNI naming convention:"
p_box ""
p_box "  Java:  public static native int add(int a, int b);"
p_box "         in class com.tutorial.NativeMath"
p_box ""
p_box "  C++:   JNIEXPORT jint JNICALL"
p_box "         Java_com_tutorial_NativeMath_add(JNIEnv* env, jclass cls, jint a, jint b)"
p_box ""
p_box "  Rule:  Java_<package_dots_as_underscores>_<ClassName>_<methodName>"
p_box ""
p_box "  JNIEXPORT  → marks the symbol as exported from the .so"
p_box "  JNICALL    → sets the calling convention (important on Windows)"
p_box "  JNIEnv*    → handle to the JVM — used to create Java objects, throw exceptions"
p_box "  jclass     → the Java class object (for static methods)"
p_box "               for instance methods it's jobject (the 'this' reference)"

# ── Build ─────────────────────────────────────────────────────────────────────
p_section "Build"

cd "$STEP_DIR"
rm -rf build

p_cmd "cmake -S . -B build"
echo ""
cmake -S . -B build 2>&1

echo ""
p_cmd "cmake --build build"
cmake --build build 2>&1

# ── Inspect outputs ───────────────────────────────────────────────────────────
p_section "Inspect Build Outputs"

echo ""
p_cmd "ls build/*.so build/*.jar build/jni_headers/ 2>/dev/null"
ls build/*.so build/*.jar 2>/dev/null && true
ls build/jni_headers/ 2>/dev/null && true

p_info ""
p_info "Generated JNI header (first 15 lines):"
head -15 build/jni_headers/com_tutorial_NativeMath.h 2>/dev/null || true

# ── Run the demo ──────────────────────────────────────────────────────────────
p_section "Run: Java calls C++"

p_cmd "cmake --build build --target run"
echo ""
cmake --build build --target run 2>&1

# ── java.library.path ─────────────────────────────────────────────────────────
p_section "Understanding java.library.path"

p_info "System.loadLibrary(\"nativemath\") searches for libnativemath.so"
p_info "in the directories listed by the java.library.path JVM property."
p_info ""
p_info "Without -Djava.library.path=build/, you'd get:"
p_box "  Exception in thread \"main\" java.lang.UnsatisfiedLinkError:"
p_box "    no nativemath in java.library.path"
p_info ""
p_info "In the CMakeLists.txt run target:"
p_box "  -Djava.library.path=\${CMAKE_BINARY_DIR}"
p_box "  → tells the JVM to also look in the CMake build directory"
p_info ""
p_info "For installed/deployed applications:"
p_box "  Place libnativemath.so in a standard lib directory (/usr/lib)"
p_box "  OR set LD_LIBRARY_PATH=/path/to/lib before launching the JVM"
p_box "  OR pass -Djava.library.path=/path/to/lib at JVM startup"

# ── Comparison: JNI vs pybind11 ───────────────────────────────────────────────
p_section "JNI vs pybind11 — Comparison"

p_box "  Feature             JNI                     pybind11"
p_box "  ──────────────────────────────────────────────────────────"
p_box "  Language            Java                    Python"
p_box "  Header generation   javac -h (automatic)    manual bindings.cpp"
p_box "  Type mapping        manual (jint, jstring)  automatic (int, str)"
p_box "  Error handling      manual JNIEnv checks    automatic exceptions"
p_box "  Boilerplate         high                    low"
p_box "  Performance         low overhead            low overhead"
p_box "  Library type        SHARED (.so/.dll)       MODULE (.so)"
p_box "  Loading             System.loadLibrary()    Python import system"
p_box "  JAVA_HOME needed    yes                     no"

# ── Clean up ──────────────────────────────────────────────────────────────────
rm -rf build

# ── Summary ───────────────────────────────────────────────────────────────────
p_section "Step 11 Summary"

p_ok "project(CppJavaDemo CXX Java) — declare both languages upfront"
p_ok "find_package(Java 11 REQUIRED COMPONENTS Development)"
p_ok "JAVA_HOME auto-detection via REALPATH → DIRECTORY → ABSOLUTE"
p_ok "find_package(JNI) BEFORE include(UseJava) — ordering is critical"
p_ok "include(UseJava) + add_jar(GENERATE_NATIVE_HEADERS tutorial-native)"
p_ok "GENERATE_NATIVE_HEADERS creates INTERFACE target with jni.h + generated .h"
p_ok "add_library(nativemath SHARED) — SHARED required for dlopen() by JVM"
p_ok "target_link_libraries(PRIVATE tutorial-native) — propagates include paths"
p_ok "-Djava.library.path — tells JVM where to find libnativemath.so at runtime"
p_ok "VERBATIM on add_custom_target — prevents shell mangling of JVM -D arguments"
echo ""
p_info "You now know CMake from hello world to"
p_info "libraries, testing, install, external deps, Python bindings, and Java JNI."
echo ""
