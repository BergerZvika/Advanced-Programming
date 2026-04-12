cmake_minimum_required(VERSION 3.15)

# Java language must be declared here so CMake finds and validates javac
# before include(UseJava) runs.
project(CppJavaDemo CXX Java)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Step 1: Find Java ──────────────────────────────────────────────────────────

# COMPONENTS Development: provides javac + java runtime.
# Sets Java_JAVAC_EXECUTABLE, Java_JAVA_EXECUTABLE, Java_VERSION.
find_package(Java 11 REQUIRED COMPONENTS Development)

# ── Step 2: Find JNI ──────────────────────────────────────────────────────────

# Auto-detects JAVA_HOME by resolving symlinks from javac's path.
# Needed because find_package(JNI) uses JAVA_HOME to locate jni.h.
if(NOT DEFINED ENV{JAVA_HOME})
    get_filename_component(_javac_real "${Java_JAVAC_EXECUTABLE}" REALPATH)
    get_filename_component(_javac_bin  "${_javac_real}" DIRECTORY)
    get_filename_component(_java_home  "${_javac_bin}/.."  ABSOLUTE)
    set(ENV{JAVA_HOME} "${_java_home}")
    message(STATUS "Auto-detected JAVA_HOME: ${_java_home}")
endif()

# Finds jni.h and jni_md.h; sets JNI_INCLUDE_DIRS.
# MUST come BEFORE include(UseJava) — add_jar(GENERATE_NATIVE_HEADERS)
# captures JNI_INCLUDE_DIRS when it creates its INTERFACE target.
find_package(JNI REQUIRED)

message(STATUS "Java_JAVAC_EXECUTABLE : ${Java_JAVAC_EXECUTABLE}")
message(STATUS "Java_JAVA_EXECUTABLE  : ${Java_JAVA_EXECUTABLE}")
message(STATUS "JNI_INCLUDE_DIRS      : ${JNI_INCLUDE_DIRS}")

# ── Step 3: Enable UseJava module ──────────────────────────────────────────────

# Provides add_jar(), install_jar(), find_jar(), create_javadoc().
include(UseJava)

# ── Step 4: Compile Java and generate the JNI C header ────────────────────────

# ENTRY_POINT: sets Main-Class in MANIFEST.MF → enables  java -jar TutorialJar.jar
# GENERATE_NATIVE_HEADERS tutorial-native: runs  javac -h  on native-declared methods
#   and creates an INTERFACE target carrying the generated header dir + JNI_INCLUDE_DIRS.
# DESTINATION: generated .h file location (naming: pkg.Class → pkg_Class.h).
add_jar(TutorialJar
    SOURCES
        src/com/tutorial/NativeMath.java
        src/com/tutorial/Main.java
    ENTRY_POINT com.tutorial.Main
    GENERATE_NATIVE_HEADERS tutorial-native
        DESTINATION ${CMAKE_BINARY_DIR}/jni_headers
)

# ── Step 5: Build the C++ JNI shared library ───────────────────────────────────

# SHARED required: System.loadLibrary() can only dlopen() a shared library.
# Maps to: libnativemath.so (Linux/macOS) / nativemath.dll (Windows).
add_library(nativemath SHARED src/jni/native_math.cpp)

# "tutorial-native" propagates both the generated header dir and JNI_INCLUDE_DIRS.
target_link_libraries(nativemath PRIVATE tutorial-native)

# ── Step 6: run target ─────────────────────────────────────────────────────────

# JAR_FILE property holds the absolute path to the generated .jar.
get_target_property(_jar TutorialJar JAR_FILE)

# -Djava.library.path=${CMAKE_BINARY_DIR}: tells the JVM where to find
# libnativemath.so for System.loadLibrary("nativemath").
add_custom_target(run
    COMMAND ${Java_JAVA_EXECUTABLE}
            -Djava.library.path=${CMAKE_BINARY_DIR}
            -jar ${_jar}
    DEPENDS TutorialJar nativemath
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running Java + JNI demo"
    VERBATIM
)

message(STATUS "")
message(STATUS "=== Step 11: C++ + Java via JNI ===")
message(STATUS "  Build:  cmake --build build")
message(STATUS "  Run:    cmake --build build --target run")
message(STATUS "")
