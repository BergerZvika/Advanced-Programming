// Concept: comparing two ranges element-wise.
//
//   std::equal(b1, e1, b2)            — true if every element pair matches
//   std::equal(b1, e1, b2, e2)        — same, with both end iterators (C++14)
//   std::mismatch(b1, e1, b2)         — pair of iterators at the first diff
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> a{1, 2, 3, 4, 5};
    std::vector<int> b{1, 2, 3, 4, 5};
    std::vector<int> c{1, 2, 9, 4, 5};

    std::cout << "a == b ? " << std::equal(a.begin(), a.end(), b.begin()) << "\n";
    std::cout << "a == c ? " << std::equal(a.begin(), a.end(), c.begin()) << "\n";

    auto [ait, cit] = std::mismatch(a.begin(), a.end(), c.begin());
    if (ait != a.end())
        std::cout << "first mismatch at index "
                  << std::distance(a.begin(), ait)
                  << " : a=" << *ait << "  c=" << *cit << "\n";

    // Custom comparator — case-insensitive equality of strings would go here
    std::vector<int> evens_doubled{2, 4, 6, 8, 10};
    bool b_is_double_a = std::equal(a.begin(), a.end(), evens_doubled.begin(),
        [](int x, int y){ return 2*x == y; });
    std::cout << "evens_doubled is 2*a ? " << b_is_double_a << "\n";
}
