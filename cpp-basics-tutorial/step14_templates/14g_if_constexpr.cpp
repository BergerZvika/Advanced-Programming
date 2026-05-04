// Concept: 'if constexpr' (C++17) — compile-time branching INSIDE a template.
//
// Inside a template, plain 'if' would still compile both branches even if
// only one is reachable for a given T — and that "unreachable" branch can
// fail to compile if it uses operations T doesn't support.
// 'if constexpr' DISCARDS the untaken branch at compile time, so it doesn't
// need to be valid for the current T.
//
// vs C: no analogue at all — closest is preprocessor #if, but that has no
// access to types or the C++ type system.
#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
void describe(const T& v) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "  integral: " << v << "  (×2 = " << (v * 2) << ")\n";
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "  floating: " << v << "  (square = " << (v * v) << ")\n";
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "  string  : '" << v << "'  (length = " << v.size() << ")\n";
    } else {
        std::cout << "  other   : " << v << "\n";
    }
}

int main() {
    describe(42);                  // integral branch — only this branch is compiled
    describe(3.14);                // floating branch
    describe(std::string("hi"));   // string branch
    describe('A');                 // char is integral → integral branch
    // Each call instantiates one specialisation that contains ONLY the matching branch.
    // Branches that wouldn't compile for the chosen T (e.g. v.size() on int) are
    // discarded → no error.
}
