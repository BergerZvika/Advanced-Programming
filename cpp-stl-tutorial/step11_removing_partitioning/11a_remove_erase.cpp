// Concept: the erase-remove idiom.
//
// vs C: in C you'd shift elements down by hand. STL splits the work:
//
//   std::remove(b, e, value)        moves keepers to the front, returns
//                                    new_end. Container size does NOT change.
//   container.erase(new_end, end()) actually drops the tail.
//
// C++20 added std::erase / std::erase_if as one-liners.
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 2, 4, 2, 5};

    auto new_end = std::remove(v.begin(), v.end(), 2);
    v.erase(new_end, v.end());
    std::cout << "after removing 2s:";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";

    // remove_if + erase — drop with a predicate
    std::vector<std::string> tags{"keep", "drop_me", "ok", "drop_me"};
    tags.erase(
        std::remove_if(tags.begin(), tags.end(),
                       [](const std::string& s){
                           return s.rfind("drop", 0) == 0;
                       }),
        tags.end());
    std::cout << "tags after drop_*:";
    for (const auto& t : tags) std::cout << " " << t;
    std::cout << "\n";
}
