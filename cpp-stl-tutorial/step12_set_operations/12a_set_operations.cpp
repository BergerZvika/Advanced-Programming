// Concept: set operations on SORTED ranges.
//
// All four require both inputs to be sorted (ascending). They write the
// result into an output iterator (back_inserter / ostream_iterator / a
// pre-allocated container).
//
//   std::set_union               in either A or B
//   std::set_intersection        in both A and B
//   std::set_difference          in A but not in B
//   std::set_symmetric_difference   in exactly one of A, B
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

void show(const char* tag, const std::vector<int>& v) {
    std::cout << tag;
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";
}

int main() {
    std::vector<int> a{1, 2, 3, 4, 5};
    std::vector<int> b{3, 4, 5, 6, 7};
    std::vector<int> out;

    out.clear();
    std::set_union(a.begin(), a.end(), b.begin(), b.end(),
                   std::back_inserter(out));
    show("union               :", out);

    out.clear();
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(),
                          std::back_inserter(out));
    show("intersection        :", out);

    out.clear();
    std::set_difference(a.begin(), a.end(), b.begin(), b.end(),
                        std::back_inserter(out));
    show("difference (a - b)  :", out);

    out.clear();
    std::set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(),
                                  std::back_inserter(out));
    show("symmetric_difference:", out);
}
