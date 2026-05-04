// Concept: when you don't need a FULL sort.
//
//   std::partial_sort(b, mid, e)
//       The first (mid-b) elements are sorted into final order;
//       the rest is unspecified. Cost: O(n log k) for k = mid-b.
//
//   std::nth_element(b, nth, e)
//       After the call, *nth is the element that would be there if the
//       range were fully sorted; everything before is ≤ *nth, after is ≥.
//       Cost: O(n) on average. Useful for medians and "top-k".
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{9, 3, 7, 1, 8, 2, 5, 4, 6};

    // Find the 3 smallest in sorted order, leave the rest alone
    std::vector<int> a = v;
    std::partial_sort(a.begin(), a.begin() + 3, a.end());
    std::cout << "partial_sort first 3:";
    for (int x : a) std::cout << " " << x;
    std::cout << "  (the 3 smallest are at the front, sorted; tail unspecified)\n";

    // Median of v in O(n)
    std::vector<int> b = v;
    auto mid = b.begin() + b.size()/2;
    std::nth_element(b.begin(), mid, b.end());
    std::cout << "median = " << *mid << "  (after nth_element)\n";

    // Top-3 LARGEST values — partial_sort + greater<>
    std::vector<int> c = v;
    std::partial_sort(c.begin(), c.begin() + 3, c.end(), std::greater<int>{});
    std::cout << "top-3 largest:";
    for (int i = 0; i < 3; ++i) std::cout << " " << c[i];
    std::cout << "\n";
}
