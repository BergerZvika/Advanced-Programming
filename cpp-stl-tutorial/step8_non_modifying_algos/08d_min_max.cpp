// Concept: min / max and the *_element family.
//
//   std::min(a, b)               smaller of two values
//   std::max(a, b)               larger
//   std::minmax(a, b)            both — returns std::pair
//   std::min_element(b, e)       iterator to smallest in a range
//   std::max_element(b, e)       iterator to largest
//   std::minmax_element(b, e)    pair<min_it, max_it>
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cout << "min(7, 12) = " << std::min(7, 12) << "\n";
    std::cout << "max(7, 12) = " << std::max(7, 12) << "\n";

    auto [lo, hi] = std::minmax(7, 12);
    std::cout << "minmax(7,12) = (" << lo << ", " << hi << ")\n";

    std::vector<int> v{5, 2, 9, 1, 7, 3, 8};
    auto mn = std::min_element(v.begin(), v.end());
    auto mx = std::max_element(v.begin(), v.end());
    std::cout << "min_element = " << *mn
              << " at index " << std::distance(v.begin(), mn) << "\n";
    std::cout << "max_element = " << *mx
              << " at index " << std::distance(v.begin(), mx) << "\n";

    auto [mnit, mxit] = std::minmax_element(v.begin(), v.end());
    std::cout << "minmax_element = (" << *mnit << ", " << *mxit << ")\n";
}
