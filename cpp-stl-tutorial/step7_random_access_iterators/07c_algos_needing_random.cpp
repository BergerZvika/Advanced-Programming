// Concept: algorithms that REQUIRE random-access iterators.
//
//   std::sort, std::stable_sort, std::partial_sort, std::nth_element
//   std::shuffle
//   std::push_heap / std::pop_heap / std::make_heap / std::sort_heap
//   std::rotate (works with bidi too, but RA gives O(1) per element)
//
// Trying to sort a std::list with std::sort is a COMPILE ERROR — list's
// iterators are bidirectional. (Use list's own .sort() member instead, which
// is implemented as a merge sort over the linked structure.)
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int main() {
    std::vector<int> v{4, 2, 5, 2, 1, 3, 5, 4};

    std::sort(v.begin(), v.end());
    std::cout << "sorted        :";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";

    // nth_element — quickselect-style, requires random access for O(n) average
    std::vector<int> w{9, 3, 7, 1, 8, 2, 5};
    auto mid = w.begin() + w.size()/2;
    std::nth_element(w.begin(), mid, w.end());
    std::cout << "median (nth)  : " << *mid << "\n";

    // shuffle (deterministic seed for repeatable output)
    std::vector<int> s{1, 2, 3, 4, 5, 6, 7, 8};
    std::mt19937 rng(42);
    std::shuffle(s.begin(), s.end(), rng);
    std::cout << "shuffled      :";
    for (int x : s) std::cout << " " << x;
    std::cout << "\n";

    // std::list<int> ll{3,1,2};
    // std::sort(ll.begin(), ll.end());   // ← compile error: list iterators are bidi
    // ll.sort();                          // ← list provides its own sort
}
