// Concept: std::list — doubly-linked list.
//
// vs C: in C you'd write   struct Node { int v; Node* prev, *next; };  by hand,
// plus insert/erase plumbing. std::list does it for you.
//
// Trade-offs:
//   + O(1) insert/erase given an iterator
//   + iterators NOT invalidated when others are inserted/removed
//   - no random access (no [i])
//   - poor cache locality — usually slower than vector for typical workloads
//
// Modern advice: prefer vector unless you genuinely need stable iterators
// or O(1) splice.
#include <iostream>
#include <list>

int main() {
    std::list<int> l{1, 2, 4, 5};

    auto it = std::next(l.begin(), 2);   // points at 4
    l.insert(it, 3);                      // O(1) — list is now {1,2,3,4,5}

    std::cout << "list after insert:";
    for (int x : l) std::cout << " " << x;
    std::cout << "\n";

    // splice — O(1) move of nodes from another list (no copies, no allocations)
    std::list<int> other{100, 200};
    l.splice(l.end(), other);
    std::cout << "after splice:        ";
    for (int x : l) std::cout << " " << x;
    std::cout << "  (other.size=" << other.size() << ")\n";

    // list also has its own sort() — std::sort needs random access.
    l.sort();
    std::cout << "after l.sort():      ";
    for (int x : l) std::cout << " " << x;
    std::cout << "\n";
}
