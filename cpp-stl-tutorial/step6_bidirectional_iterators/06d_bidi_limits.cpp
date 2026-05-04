// Concept: what bidirectional iterators CANNOT do.
//
// Bidi only adds  --it  on top of forward. It does NOT add:
//   it + n         (jump by n)
//   it - n         (jump back by n)
//   it[n]          (subscript)
//   it1 - it2      (distance arithmetic)
//   it1 < it2      (ordering)
//
// You can simulate these with std::advance / std::distance — but the cost
// is O(n) hops, NOT O(1). If you need O(1) jumps, you need RANDOM ACCESS
// iterators (see step 7).
#include <iostream>
#include <iterator>
#include <list>

int main() {
    std::list<int> l{10, 20, 30, 40, 50};
    auto it = l.begin();

    // it += 3;            // ← compile error: list iterators are bidi, not random access
    // it[3]               // ← compile error
    // bool b = it < l.end();  // ← compile error: '<' not defined

    // The portable way is std::advance / std::distance — they walk one node
    // at a time on bidi (O(n)) but compile fine.
    std::advance(it, 3);
    std::cout << "after std::advance(it, 3): *it = " << *it << "\n";

    auto end = l.end();
    std::cout << "distance(begin, end) = "
              << std::distance(l.begin(), end) << "  (O(n) for list — must walk)\n";

    // std::next / std::prev work too:
    auto it2 = std::next(l.begin(), 2);
    std::cout << "next(begin, 2) = " << *it2 << "\n";
    auto it3 = std::prev(l.end(), 2);
    std::cout << "prev(end, 2)   = " << *it3 << "\n";
}
