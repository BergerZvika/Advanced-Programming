// Concept: auto caveats — auto strips reference/const by default.
// Use 'auto&' or 'const auto&' to keep them.
//
//   auto x        = expr;   →  copy, drops const & reference
//   auto& x       = expr;   →  reference, may be const-ref or non-const ref
//   const auto& x = expr;   →  always a const reference (no copies)
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4};

    // 'auto x' COPIES each element — modifying x does NOT change v.
    for (auto x : v) x *= 10;
    std::cout << "after 'auto x':       v[0]=" << v[0] << "  (unchanged)\n";

    // 'auto&' takes a reference — modifying x DOES change v.
    for (auto& x : v) x *= 10;
    std::cout << "after 'auto& x':      v[0]=" << v[0] << "  (multiplied)\n";

    // 'const auto&' — read-only view, no copies. Best default for read access.
    int sum = 0;
    for (const auto& x : v) sum += x;
    std::cout << "sum via const auto&:  " << sum << "\n";

    // Returns of auto: same trap. 'auto' on a function returning T& gives T (a copy).
    int n = 5;
    int& nref = n;
    auto  x = nref;     // x is int (copy)  — independent of n
    auto& y = nref;     // y is int&        — alias for n
    x = 99; y = 77;
    std::cout << "x=" << x << "  y=" << y << "  n=" << n
              << "   (only y reached n)\n";
}
