// Concept: how the iterator category affects the COST of an algorithm.
//
//   std::binary_search / std::lower_bound / std::upper_bound
//
// These work on ANY forward iterator pair, but the cost differs:
//   - Random access (vector, deque, array) → O(log n) jumps, true O(log n) total
//   - Bidirectional / forward (list, set, map) → still O(log n) COMPARISONS,
//     but O(n) HOPS to advance the iterator → not really faster than linear scan
//
// In practice: only call binary search on random-access containers.
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

int main() {
    std::vector<int> v{1, 3, 5, 7, 9, 11, 13, 15};   // sorted, random access
    std::list<int>   l(v.begin(), v.end());           // sorted, bidi

    std::cout << "vector binary_search(7) = "
              << std::binary_search(v.begin(), v.end(), 7) << "  (true O(log n))\n";

    std::cout << "list   binary_search(7) = "
              << std::binary_search(l.begin(), l.end(), 7)
              << "  (compiles, O(log n) compares but O(n) hops)\n";

    // lower_bound — same story
    auto vit = std::lower_bound(v.begin(), v.end(), 6);
    std::cout << "vector lower_bound(6) → " << *vit
              << "  at index " << (vit - v.begin()) << "\n";

    // It's the it+n / it-n that random access provides which makes the binary
    // search jump efficiently. Every other category falls back to walking.
}
