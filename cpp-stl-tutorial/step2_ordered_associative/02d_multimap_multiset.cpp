// Concept: std::multimap / std::multiset — like map / set but ALLOW DUPLICATES.
//
// equal_range(key) returns the half-open range of all entries with that key.
#include <iostream>
#include <map>
#include <set>
#include <string>

int main() {
    std::multimap<std::string, std::string> phone;
    phone.insert({"alice", "111-1111"});
    phone.insert({"alice", "222-2222"});       // same key — allowed
    phone.insert({"bob",   "333-3333"});

    std::cout << "alice's numbers:\n";
    auto [lo, hi] = phone.equal_range("alice");
    for (auto it = lo; it != hi; ++it)
        std::cout << "  " << it->second << "\n";

    std::multiset<int> bag{1, 2, 2, 3, 3, 3};
    std::cout << "bag: count(2)=" << bag.count(2)
              << "  count(3)=" << bag.count(3) << "\n";
    std::cout << "bag values:";
    for (int x : bag) std::cout << " " << x;
    std::cout << "\n";
}
