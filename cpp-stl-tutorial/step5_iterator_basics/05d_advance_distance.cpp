// Concept: iterator helpers from <iterator>.
//
//   std::advance(it, n)    move iterator forward (or back) by n
//   std::distance(a, b)    count steps from a to b
//   std::next(it [, n])    return it advanced (without modifying it)
//   std::prev(it [, n])    return it stepped back
//
// These pick the most efficient implementation for the iterator category:
//   - random-access  → O(1) using +/-
//   - bidirectional  → O(n) walking step by step
//   - forward only   → only positive n
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

int main() {
    std::vector<int> v{10, 20, 30, 40, 50};

    auto it = v.begin();
    std::advance(it, 3);                       // points at 40
    std::cout << "after advance(it, 3): *it=" << *it << "\n";

    std::cout << "distance(begin, end) = "
              << std::distance(v.begin(), v.end()) << "  (== size)\n";

    auto first = v.begin();
    auto third = std::next(first, 2);
    std::cout << "*first=" << *first
              << "  *next(first,2)=" << *third << "\n";

    std::list<int> l{1, 2, 3, 4, 5};
    auto lit = std::next(l.begin(), 2);
    std::cout << "list[2] via std::next = " << *lit << "\n";
}
