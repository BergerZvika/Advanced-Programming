// Concept: std::set — sorted collection of unique values.
//
// vs C: keep an ordered array and binary-search it. std::set gives
// O(log n) insert/find/erase and iterates IN ORDER. Each value appears
// at most once. Implementation is a balanced BST (red-black tree).
#include <iostream>
#include <set>

int main() {
    std::set<int> s{3, 1, 4, 1, 5, 9, 2, 6, 5};   // duplicates dropped on insert

    std::cout << "size  = " << s.size() << "  (duplicates removed)\n";
    std::cout << "values:";
    for (int x : s) std::cout << " " << x;        // sorted
    std::cout << "\n";

    std::cout << "contains 4? " << (s.count(4) ? "yes" : "no") << "\n";
    std::cout << "contains 7? " << (s.count(7) ? "yes" : "no") << "\n";

    // Range query — find every value in [3, 6]:
    std::cout << "values in [3,6]:";
    auto lo = s.lower_bound(3);     // first ≥ 3
    auto hi = s.upper_bound(6);     // first > 6
    for (auto it = lo; it != hi; ++it) std::cout << " " << *it;
    std::cout << "\n";
}
