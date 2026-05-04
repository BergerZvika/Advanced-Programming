// Concept: rearranging elements in place.
//
//   std::reverse(b, e)             reverse the range in place
//   std::rotate(b, mid, e)         move [mid, e) to the front
//   std::shuffle(b, e, rng)        randomise (C++11) — pass a random engine
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
    std::reverse(v.begin(), v.end());
    std::cout << "reverse:";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";

    std::vector<int> r{1, 2, 3, 4, 5, 6, 7};
    std::rotate(r.begin(), r.begin() + 3, r.end());
    std::cout << "rotate by 3:";
    for (int x : r) std::cout << " " << x;
    std::cout << "  (4,5,6,7,1,2,3)\n";

    // Deterministic shuffle for repeatable demo output:
    std::vector<int> s{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::mt19937 rng(42);          // fixed seed
    std::shuffle(s.begin(), s.end(), rng);
    std::cout << "shuffle:";
    for (int x : s) std::cout << " " << x;
    std::cout << "\n";
}
