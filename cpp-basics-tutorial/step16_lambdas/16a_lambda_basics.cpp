// Concept: a lambda is an INLINE, ANONYMOUS function expression.
//
//   [captures](parameters) -> return_type { body }
//
// vs C: C has function pointers. To pass behaviour into a function (for
// callbacks, comparators, etc.) you wrote a separate named function and
// passed its address. C++ lambdas let you write that one-line behaviour
// EXACTLY where it's used, with access to the surrounding scope (via captures
// — see file 16b).
//
// Most parts are optional:
//   - the return type ('->' arrow) is usually deduced
//   - the parameter list can be empty: []{ ... }
//   - the captures can be empty: []
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    // Trivial lambda
    auto greet = []{ std::cout << "  hello\n"; };
    greet();

    // Lambda with parameters and an explicit return type
    auto add = [](int a, int b) -> int { return a + b; };
    std::cout << "  add(3, 4) = " << add(3, 4) << "\n";

    // The compiler usually deduces the return type — the arrow is optional:
    auto mul = [](int a, int b) { return a * b; };
    std::cout << "  mul(3, 4) = " << mul(3, 4) << "\n";

    // Lambda passed inline as an algorithm argument — the typical use:
    std::vector<int> v{5, 2, 8, 1, 9, 3};
    std::sort(v.begin(), v.end(),
              [](int a, int b){ return a > b; });          // sort descending
    std::cout << "  sorted desc:";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";
}
