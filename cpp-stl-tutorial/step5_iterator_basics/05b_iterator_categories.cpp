// Concept: iterator CATEGORIES.
// Every container's iterator falls in one of these tiers, ordered from
// least to most powerful. Algorithms specify the minimum category they need.
//
//   InputIterator         single-pass read,  ++it,  *it
//   OutputIterator        single-pass write, ++it,  *it = v
//   ForwardIterator       multi-pass, ++ only
//   BidirectionalIterator adds --it     (list, set, map)
//   RandomAccessIterator  adds it+n, it[n], <  (vector, deque, array)
//
// vs C: a C pointer behaves like a RandomAccessIterator into an array.
// STL generalises so the SAME algorithms work on lists, sets, files, …
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    std::list<int>   l{1, 2, 3};

    using vit = decltype(v.begin());
    using lit = decltype(l.begin());
    using vcat = std::iterator_traits<vit>::iterator_category;
    using lcat = std::iterator_traits<lit>::iterator_category;

    std::cout << "vector::iterator → "
              << (std::is_same_v<vcat, std::random_access_iterator_tag>
                  ? "RandomAccess" : "other") << "\n";
    std::cout << "list::iterator   → "
              << (std::is_same_v<lcat, std::bidirectional_iterator_tag>
                  ? "Bidirectional" : "other") << "\n";

    // The category determines what operations are valid:
    auto vit2 = v.begin();
    vit2 += 2;                   // OK on RandomAccess
    auto lit2 = l.begin();
    // lit2 += 2;                // ← compile error
    std::advance(lit2, 2);       // works for any forward+ iterator
    std::cout << "*vit2=" << *vit2 << "  *lit2=" << *lit2 << "\n";
}
