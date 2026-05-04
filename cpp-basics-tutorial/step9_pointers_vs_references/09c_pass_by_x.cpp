// Concept: the four ways to pass an argument in C++.
//
//   by value          (copy)              T x         like C — copy-in
//   by pointer        (caller's object)   T* x        like C — manual indirection
//   by reference      (caller's object)   T& x        C++ only — no null
//   by const reference                    const T& x  read-only, no copy — common
//
// vs C:
//   C only has the first two. The 'pass by const reference' idiom in C++ is
//   the modern equivalent of 'pass a const T*' but cleaner at call sites.
#include <iostream>
#include <string>

void by_value(std::string s)            { s += "!"; }
void by_pointer(std::string* s)         { if (s) *s += "!"; }
void by_reference(std::string& s)       { s += "!"; }
void by_const_reference(const std::string& s) {
    std::cout << "  read-only view: " << s << "\n";
    // s += "x";   // ← compile error: cannot modify a const reference
}

int main() {
    std::string a = "value", b = "ptr", c = "ref", d = "cref";
    by_value(a);            // a unchanged — function got a copy
    by_pointer(&b);         // b changed
    by_reference(c);        // c changed
    by_const_reference(d);  // d unchanged (read-only)

    std::cout << "a=" << a << "  b=" << b << "  c=" << c << "  d=" << d << "\n";
    std::cout << "(only a is unchanged — value pass made a copy)\n";
}
