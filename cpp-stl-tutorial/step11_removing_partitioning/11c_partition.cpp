// Concept: partitioning — split a range by a predicate without sorting.
//
//   std::partition(b, e, p)         elements with p(*it)==true go to the
//                                    front, false to the back. Order within
//                                    each side is unspecified. O(n).
//   std::stable_partition(b, e, p)  same, but original relative order kept.
//   std::partition_point(b, e, p)   on a partitioned range, returns the
//                                    boundary in O(log n).
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto is_even = [](int x){ return x % 2 == 0; };

    // unstable
    auto mid = std::partition(v.begin(), v.end(), is_even);
    std::cout << "partition (evens first):";
    for (int x : v) std::cout << " " << x;
    std::cout << "  (boundary at index "
              << std::distance(v.begin(), mid) << ")\n";

    // stable
    std::vector<int> w{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::stable_partition(w.begin(), w.end(), is_even);
    std::cout << "stable_partition       :";
    for (int x : w) std::cout << " " << x;
    std::cout << "  (relative order preserved)\n";

    // partition_point — once partitioned, find the boundary in O(log n)
    auto p = std::partition_point(v.begin(), v.end(), is_even);
    std::cout << "partition_point at index "
              << std::distance(v.begin(), p) << "\n";
}
