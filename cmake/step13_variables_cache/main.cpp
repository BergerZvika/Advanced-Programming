#include <iostream>
#include <string>

#ifndef APP_GREETING
#  define APP_GREETING "hello"
#endif
#ifndef GREETING_REPEAT
#  define GREETING_REPEAT 1
#endif

int main() {
    std::cout << "\n=== CMake Variables Demo ===\n\n";

    for (int i = 0; i < GREETING_REPEAT; ++i) {
        std::cout << "  " << APP_GREETING << "\n";
    }
    std::cout << "\n";

#ifdef SHOW_ENV_INFO
    std::cout << "Platform  : "
#if defined(PLATFORM_LINUX)
              << "Linux"
#elif defined(PLATFORM_MACOS)
              << "macOS"
#elif defined(PLATFORM_WINDOWS)
              << "Windows"
#else
              << "Unknown"
#endif
              << "\n";

    std::cout << "Compiler  : "
#if defined(COMPILER_GCC_CLANG)
              << "GCC or Clang"
#elif defined(COMPILER_MSVC)
              << "MSVC"
#else
              << "Unknown"
#endif
              << "\n";
#endif // SHOW_ENV_INFO

    std::cout << "\n";
    return 0;
}
