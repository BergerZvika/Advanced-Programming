// Concept: printf vs std::cout.
//
// vs C:
//   C uses format strings — the compiler does NOT type-check arguments
//   against the format specifiers (%d / %s / %f). Mismatches → undefined.
//   C++ uses STREAM insertion via operator<< — the type is known at compile
//   time, so the right formatting is selected automatically.
//
// Both are still legal in C++ (cstdio is a C++ header that wraps stdio.h).
#include <cstdio>     // C: printf
#include <iostream>   // C++: cout

int main() {
    int   age   = 42;
    double pi   = 3.14159;
    const char* name = "Ada";

    // C-style — relies on you matching %d / %f / %s correctly:
    std::printf("[printf] %s is %d years old, pi = %.2f\n", name, age, pi);

    // C++ stream — types are deduced; chained insertions are left-to-right.
    std::cout << "[cout]   " << name << " is " << age
              << " years old, pi = " << pi << "\n";
}
