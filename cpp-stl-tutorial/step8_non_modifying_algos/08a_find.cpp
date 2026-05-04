// Concept: searching with std::find / std::find_if / std::find_if_not.
//
// vs C: linear scan you wrote yourself, or 'bsearch' on sorted arrays.
// STL searches accept ANY iterator pair — same code works on vector, list,
// map, even raw arrays.
//
//   std::find(b, e, v)      — first iterator with *it == v, else e
//   std::find_if(b, e, p)   — first iterator with p(*it) true, else e
//   std::find_if_not(b, e, p) — first with p(*it) false
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 3, 5, 8, 13, 21, 34};

    auto it = std::find(v.begin(), v.end(), 13);
    if (it != v.end())
        std::cout << "13 found at index "
                  << std::distance(v.begin(), it) << "\n";

    auto big = std::find_if(v.begin(), v.end(),
                            [](int x){ return x > 10; });
    std::cout << "first > 10  : " << *big << "\n";

    auto small = std::find_if_not(v.begin(), v.end(),
                                  [](int x){ return x < 10; });
    std::cout << "first not<10: " << *small << "\n";
}
