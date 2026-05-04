// Concept: algorithms that REQUIRE at least bidirectional iterators.
// They need to step backward (or both directions), so a forward-only iterator
// would be a compile error.
//
//   std::reverse(b, e)          swap pairs from both ends inward — bidi
//   std::rotate(b, mid, e)      moves [mid, e) to the front — bidi
//   std::next_permutation(b, e) walks the lex order — bidi
//   std::prev_permutation(b, e) reverse direction — bidi
//   std::stable_partition       relative order kept — bidi
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

int main() {
    // std::reverse on a bidi container (list)
    std::list<int> l{1, 2, 3, 4, 5};
    std::reverse(l.begin(), l.end());
    std::cout << "reversed list:";
    for (int x : l) std::cout << " " << x;
    std::cout << "\n";

    // std::rotate
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
    std::rotate(v.begin(), v.begin() + 3, v.end());
    std::cout << "rotate by 3 :";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";

    // std::next_permutation — needs to scan back from the end
    std::vector<int> p{1, 2, 3};
    do {
        std::cout << "  ";
        for (int x : p) std::cout << x << " ";
        std::cout << "\n";
    } while (std::next_permutation(p.begin(), p.end()));
    // None of the above would compile with a forward_list iterator.
}
