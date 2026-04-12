#include <iostream>
#include <string>
#include <vector>
#include <numeric>

// APP_NAME and APP_VERSION are defined via target_compile_definitions()
// in CMakeLists.txt — no #define here. CMake injects them as -DAPP_NAME=...
// on the compiler command line.
#ifndef APP_NAME
#  define APP_NAME "unknown"
#endif
#ifndef APP_VERSION
#  define APP_VERSION 0
#endif

// Demonstrates code that generates warnings at different levels.
// Build with -Wall -Wextra to see them.

void demo_warnings() {
    // -Wshadow: 'i' shadows the loop variable in an outer scope
    for (int i = 0; i < 3; ++i) {
        // This inner 'i' shadows the outer 'i' — Wshadow warns here
        // (intentionally commented out to keep the build clean by default)
        // int i = i + 1;
    }

    // -Wconversion: narrowing from int to short
    // short s = 70000; // warning: implicit narrowing from int to short

    std::vector<int> v = {1, 2, 3, 4, 5};
    double mean = std::accumulate(v.begin(), v.end(), 0.0) / v.size();
    std::cout << "  mean of {1..5} = " << mean << "\n";
}

int main() {
    std::cout << "\n";
    std::cout << "  APP_NAME    = " << APP_NAME    << "\n";
    std::cout << "  APP_VERSION = " << APP_VERSION << "\n";

#ifdef DEBUG_BUILD
    std::cout << "  Build type  = DEBUG\n";
#elif defined(RELEASE_BUILD)
    std::cout << "  Build type  = RELEASE\n";
#else
    std::cout << "  Build type  = UNKNOWN\n";
#endif

    std::cout << "\n";
    demo_warnings();
    std::cout << "\n";
    return 0;
}
