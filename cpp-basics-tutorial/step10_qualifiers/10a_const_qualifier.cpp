// Concept: 'const' — read-only qualifier.
//
// vs C:
//   C has 'const' too — but only on variables and parameters. C++ adds:
//     - const member functions (cannot mutate the object)
//     - top-level const on return types
//     - 'constexpr' for compile-time constants (next file)
//
// Pointer-/reference-const positions (same in C and C++):
//   const T*       pointer to const T   — can't modify *p, can reseat p
//   T* const       const pointer to T   — can modify *p, can't reseat p
//   const T* const       both
//   const T&       reference to const T — common parameter form
#include <iostream>

void print(const int& v) {
    // v += 1;     // ← compile error: v is a reference-to-const
    std::cout << "  read-only: " << v << "\n";
}

int main() {
    const int max  = 100;        // immutable variable
    int x = 5, y = 7;

    const int* pc  = &x;         // pointer-to-const
    pc = &y;                     // OK: reseat the pointer
    // *pc = 9;                  // ← error: target is const

    int* const cp  = &x;         // const pointer
    *cp = 11;                    // OK: target is mutable
    // cp = &y;                  // ← error: pointer is const

    print(max);
    std::cout << "max=" << max << "  x=" << x << "  *pc=" << *pc << "\n";
}
