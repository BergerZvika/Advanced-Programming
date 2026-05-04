// Concept: the 'bool' type.
//
// vs C:
//   In C the language had no native boolean until C99 added '_Bool' (and the
//   <stdbool.h> macros 'bool', 'true', 'false'). Pre-C99 code used 'int'
//   with the convention 0 == false, anything-else == true.
//   In C++ 'bool', 'true', 'false' are built-in keywords from day one, and
//   booleans round-trip cleanly to and from integers (true → 1, false → 0).
#include <iostream>

int main() {
    bool a = true;
    bool b = false;
    bool c = (3 < 5);              // any comparison yields a real bool
    bool d = 42;                   // implicit int → bool: anything non-zero is true

    std::cout << "true  prints as: " << a << "\n";
    std::cout << "false prints as: " << b << "\n";
    std::cout << "3 < 5  →  "          << c << "\n";
    std::cout << "bool d = 42 →  "     << d << "\n";

    // Force "true"/"false" output instead of 1/0:
    std::cout << std::boolalpha;
    std::cout << "with boolalpha → " << a << " / " << b << "\n";

    // sizeof(bool) is implementation-defined but is always at least 1 byte.
    std::cout << "sizeof(bool) = " << sizeof(bool) << " byte(s)\n";
}
