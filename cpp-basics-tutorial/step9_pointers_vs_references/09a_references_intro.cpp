// Concept: references — an ALIAS for an existing variable.
//
// vs C:
//   C has NO references. The closest tools are pointers (which can be null
//   or reseated) and macros. C++ adds 'T&' which is bound to one variable
//   at construction and never reseats — it cannot be null.
//
// Properties:
//   - Must be initialised when declared.
//   - Cannot be reseated to refer to a different object.
//   - Cannot be null.
//   - Has the same address as its referent — &ref == &orig.
#include <iostream>

int main() {
    int  x = 7;
    int& r = x;                 // r is bound to x for life

    std::cout << "x  = " << x  << "  &x  = " << &x  << "\n";
    std::cout << "r  = " << r  << "  &r  = " << &r  << "  (same address)\n";

    r = 42;                     // assigns through r → x becomes 42
    std::cout << "after r = 42:  x = " << x << "\n";

    int y = 99;
    r = y;                      // does NOT reseat — copies y INTO x
    std::cout << "after r = y :  x = " << x << "  (r still aliases x)\n";

    // int& bad;                // ← compile error: must be initialised
    // int& null_r = nullptr;   // ← compile error: cannot bind reference to null
}
