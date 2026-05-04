// Concept: variable declarations and the various init styles in C++.
//
// vs C:
//   C only has copy-init   (int x = 7;) and zero-init for static storage.
//   C99 added designated initialisers for arrays/structs.
//   C++ adds:
//     direct init:        int x(7);
//     uniform brace init: int x{7};       (C++11) — disallows narrowing
//     value init:         int x{};        zero-init
//     constexpr / auto    (later steps)
#include <iostream>

int main() {
    int a = 7;          // copy initialisation     — works in C too
    int b(7);           // direct initialisation   — C++ only
    int c{7};           // uniform/brace init      — C++11, no narrowing
    int d{};            // value init: equivalent to int d = 0;

    // double e{3.14};
    // int    f{e};     // ← compile error: brace-init refuses narrowing
    int    f = 3.14;    // ← legal in C++ (and C) — silent narrowing

    std::cout << "a=" << a << "  b=" << b << "  c=" << c
              << "  d=" << d << "  f(narrowed)=" << f << "\n";
}
