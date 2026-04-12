cmake_minimum_required(VERSION 3.18)
project(CombinedDemo CXX Java)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Find Python (embedding) ───────────────────────────────────────────────────
# "Development" (not "Development.Module"): requires libpython.so to embed
# the interpreter inside a C++ binary. Development.Module is only for
# extension .so files loaded by Python, not for embedding.
find_package(Python3 REQUIRED COMPONENTS Development)
message(STATUS "Python3: ${Python3_VERSION}  lib: ${Python3_LIBRARIES}")

# ── Find Java + JNI ──────────────────────────────────────────────────────────
find_package(Java 11 REQUIRED COMPONENTS Development)

if(NOT DEFINED ENV{JAVA_HOME})
    get_filename_component(_javac_real "${Java_JAVAC_EXECUTABLE}" REALPATH)
    get_filename_component(_javac_bin  "${_javac_real}" DIRECTORY)
    get_filename_component(_java_home  "${_javac_bin}/.." ABSOLUTE)
    set(ENV{JAVA_HOME} "${_java_home}")
    message(STATUS "Auto-detected JAVA_HOME: ${_java_home}")
endif()

find_package(JNI REQUIRED)
message(STATUS "JNI_INCLUDE_DIRS: ${JNI_INCLUDE_DIRS}")
message(STATUS "JNI_LIBRARIES:    ${JNI_LIBRARIES}")

include(UseJava)

# ── Compile Java → HelloJar.jar ───────────────────────────────────────────────
add_jar(HelloJar SOURCES Hello.java)
get_target_property(_jar HelloJar JAR_FILE)

# ── Embed Hello.py → hello_py_data.h (compile-time) ──────────────────────────
# xxd -i reads Hello.py and writes a C header containing the file's bytes as a
# static unsigned char array.  The generated file looks like:
#   unsigned char Hello_py[] = { 0x64, 0x65, 0x66, ... };
#   unsigned int  Hello_py_len = 42;
# main.cpp #includes this header and passes Hello_py directly to
# PyRun_SimpleString(), so no .py file is needed on disk at runtime.
add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/hello_py_data.h
    COMMAND xxd -i Hello.py ${CMAKE_CURRENT_BINARY_DIR}/hello_py_data.h
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Hello.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Embedding Hello.py → hello_py_data.h"
)
add_custom_target(hello_py_embed
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/hello_py_data.h
)

# ── Build the combined executable ─────────────────────────────────────────────
add_executable(combined main.cpp ${CMAKE_CURRENT_BINARY_DIR}/hello_py_data.h)

# Python3::Python carries both include dirs and -lpython; JNI needs separate includes.
target_link_libraries(combined PRIVATE
    Python3::Python   # embeds the Python interpreter (libpython.so)
    ${JNI_LIBRARIES}  # embeds the JVM (libjvm.so)
)
target_include_directories(combined PRIVATE
    ${JNI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}   # so main.cpp can #include "hello_py_data.h"
)
add_dependencies(combined hello_py_embed)

add_dependencies(combined HelloJar)

# libjvm.so lives in a non-standard path — embed its directory in RPATH so
# the binary finds it without LD_LIBRARY_PATH.
list(GET JNI_LIBRARIES 0 _jvm_lib)
get_filename_component(_jvm_dir "${_jvm_lib}" DIRECTORY)
set_target_properties(combined PROPERTIES
    BUILD_RPATH   "${_jvm_dir}"
    INSTALL_RPATH "${_jvm_dir}"
)

# Copy HelloJar.jar next to the executable after every build.
# main.cpp locates it via argv[0] at runtime.
add_custom_command(TARGET combined POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${_jar}"
        $<TARGET_FILE_DIR:combined>/HelloJar.jar
    COMMENT "Copying HelloJar.jar next to combined"
)

message(STATUS "")
message(STATUS "=== Step 14: C++ + Java + Python ===")
message(STATUS "  Build:  cmake --build build")
message(STATUS "  Run:    ./build/combined")
message(STATUS "")
