// Concept: removing CONSECUTIVE duplicates.
//
//   std::unique(b, e)        moves consecutive duplicates past new_end,
//                             returns new_end. Container size unchanged
//                             until you call erase(new_end, end()).
//
// IMPORTANT: only consecutive duplicates! To dedup the whole range, sort first.
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 1, 2, 2, 2, 3, 1, 1, 4};

    auto end1 = std::unique(v.begin(), v.end());
    v.erase(end1, v.end());
    std::cout << "unique (consecutive only):";
    for (int x : v) std::cout << " " << x;
    std::cout << "  (the second '1' run survived)\n";

    // Full dedup: sort first
    std::vector<int> w{4, 2, 5, 2, 1, 3, 5, 4, 1};
    std::sort(w.begin(), w.end());
    w.erase(std::unique(w.begin(), w.end()), w.end());
    std::cout << "sort + unique         :";
    for (int x : w) std::cout << " " << x;
    std::cout << "\n";

    // unique with a custom equivalence — collapse runs of even neighbours
    std::vector<int> z{2, 4, 6, 1, 8, 10, 3};
    auto same_parity = [](int a, int b){ return (a%2) == (b%2); };
    z.erase(std::unique(z.begin(), z.end(), same_parity), z.end());
    std::cout << "collapse same-parity  :";
    for (int x : z) std::cout << " " << x;
    std::cout << "\n";
}
