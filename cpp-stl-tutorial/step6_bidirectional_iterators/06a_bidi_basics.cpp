// Concept: BIDIRECTIONAL ITERATORS — the next tier above forward.
// You can step forward (++it) AND backward (--it), but you cannot jump (it+n).
//
// Containers whose iterators are exactly bidirectional:
//   std::list, std::set, std::map, std::multiset, std::multimap
// (deque, vector and array offer something stronger — random access — see step 7.)
//
// vs C: a doubly-linked list in C lets you walk in either direction by
// chasing prev/next pointers; that's exactly what bidi iterators give you,
// in a uniform interface.
#include <iostream>
#include <list>

int main() {
    std::list<int> l{10, 20, 30, 40, 50};

    auto it = l.begin();
    std::cout << "*begin     = " << *it << "\n";
    ++it;                                      // walk forward
    ++it;
    std::cout << "after ++,++ = " << *it << "\n";
    --it;                                      // walk backward
    std::cout << "after  --   = " << *it << "\n";

    // The classic "loop until end()" still works exactly as for forward iterators:
    std::cout << "forward :";
    for (auto p = l.begin(); p != l.end(); ++p) std::cout << " " << *p;
    std::cout << "\n";

    // Walking backward — start at the last element, stop BEFORE begin().
    // (You cannot test 'p < l.begin()' because there is no '<' on bidi iterators.)
    std::cout << "backward:";
    auto p = l.end();
    do { --p; std::cout << " " << *p; } while (p != l.begin());
    std::cout << "\n";
}
