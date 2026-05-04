// Concept: 'constexpr' — evaluated at COMPILE time when possible.
//
// vs C:
//   C has '#define' macros (no type, no scope) and '_Generic' / __builtins,
//   but no first-class compile-time function evaluation. C++11 introduced
//   'constexpr' for true type-checked compile-time computation.
//
//   Difference from const:
//     const     →  "this name does not change after initialisation"
//     constexpr →  "this expression can be computed at compile time"
#include <iostream>

constexpr long factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

int main() {
    constexpr long f10 = factorial(10);     // computed at compile time
    int arr[factorial(4)];                  // 24 ints — array bound is constexpr
    static_assert(factorial(6) == 720,      // checked at compile time
                  "math is broken");

    std::cout << "factorial(10) = " << f10 << "\n";
    std::cout << "arr length    = " << sizeof(arr)/sizeof(int) << "  (24)\n";

    // Runtime call — same function works at runtime too:
    int n = 5;
    std::cout << "factorial(5)  = " << factorial(n) << "  (runtime)\n";
}
