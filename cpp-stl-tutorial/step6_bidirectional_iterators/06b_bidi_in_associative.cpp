// Concept: associative containers (map, set, multimap, multiset) expose
// BIDIRECTIONAL iterators, so you can walk them in BOTH directions in
// key-sorted order.
//
// Note: for std::set and std::multiset, dereferencing the iterator yields a
// CONST reference — keys cannot be mutated in place (that would break the
// sort invariant). For std::map, *it is a pair where first is const and
// second is mutable.
#include <iostream>
#include <map>
#include <set>
#include <string>

int main() {
    std::set<int> s{5, 1, 3, 7, 2};
    std::cout << "set ascending :";
    for (auto it = s.begin(); it != s.end(); ++it) std::cout << " " << *it;
    std::cout << "\n";

    std::cout << "set descending:";
    auto p = s.end();
    do { --p; std::cout << " " << *p; } while (p != s.begin());
    std::cout << "\n";

    // map iteration: it->first (const) and it->second (mutable)
    std::map<std::string, int> ages{{"alice",30}, {"bob",25}, {"carol",35}};
    std::cout << "map ascending:\n";
    for (auto it = ages.begin(); it != ages.end(); ++it) {
        std::cout << "  " << it->first << " -> " << it->second << "\n";
        // it->first = "X";    // ← compile error: keys are const
        it->second += 1;       // ← values are mutable
    }
    std::cout << "after walk-and-bump:\n";
    for (const auto& [k, v] : ages)
        std::cout << "  " << k << " -> " << v << "\n";
}
