// Concept: std::cout — type-safe stream output.
//
// vs C:
//   printf relies on YOU matching format specifiers to arg types.
//   cout uses operator<< — overloaded once per type, so the right thing
//   happens automatically. It's also extensible: define operator<< for
//   your own types and you can stream them too. (See step9 of cpp-oop.)
#include <iostream>
#include <string>

int main() {
    // Multiple insertions chain left-to-right.
    std::cout << "Hello"  << ", "  << "World" << "\n";

    // Numbers, strings, char, bool — all routed to the right overload.
    int    n = 5;
    double d = 1.5;
    std::string s = "foo";
    char        c = 'A';
    bool        b = true;

    std::cout << "int:    " << n << "\n"
              << "double: " << d << "\n"
              << "string: " << s << "\n"
              << "char:   " << c << "\n"
              << "bool:   " << b << "  (use std::boolalpha for true/false)\n";

    // std::endl flushes the buffer; "\n" does not. Prefer "\n" except when
    // you really need a flush (e.g. logging just before a crash).
    std::cout << "newline only \n";
    std::cout << "flush also  " << std::endl;

    // std::cerr is the unbuffered error stream (separate from std::cout).
    std::cerr << "this goes to stderr\n";
}
