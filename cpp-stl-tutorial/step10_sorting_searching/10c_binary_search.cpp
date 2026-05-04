// Concept: binary search on SORTED ranges.
//
//   std::binary_search(b, e, v)   bool — present?
//   std::lower_bound(b, e, v)     first iterator with *it ≥ v
//   std::upper_bound(b, e, v)     first iterator with *it >  v
//   std::equal_range(b, e, v)     pair (lower, upper)
//
// All four cost O(log n) on random-access iterators, O(n) hops on
// bidirectional iterators (the same call still works).
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 3, 5, 7, 7, 7, 9, 11};   // must be sorted

    std::cout << "contains 7  ? "
              << std::binary_search(v.begin(), v.end(), 7) << "\n";
    std::cout << "contains 8  ? "
              << std::binary_search(v.begin(), v.end(), 8) << "\n";

    auto lo = std::lower_bound(v.begin(), v.end(), 7);
    auto hi = std::upper_bound(v.begin(), v.end(), 7);
    std::cout << "lower_bound(7) at index "
              << std::distance(v.begin(), lo) << "\n";
    std::cout << "upper_bound(7) at index "
              << std::distance(v.begin(), hi) << "\n";
    std::cout << "count of 7   = " << std::distance(lo, hi) << "\n";

    // equal_range packs the two
    auto [a, b] = std::equal_range(v.begin(), v.end(), 7);
    std::cout << "equal_range(7) range size = " << std::distance(a, b) << "\n";
}
