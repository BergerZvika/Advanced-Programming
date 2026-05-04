// Concept: iterators — STL's generalisation of "pointer into a container".
//
// vs C: in C you traversed an array with a pointer or an index. STL containers
// expose iterators via .begin() and .end(). Together they form a HALF-OPEN
// RANGE [begin, end): begin points at the first element, end one PAST the last.
//
// *it dereferences, ++it advances. Range-for is sugar for an iterator loop.
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{10, 20, 30, 40};

    std::cout << "manual loop:";
    for (auto it = v.begin(); it != v.end(); ++it) std::cout << " " << *it;
    std::cout << "\n";

    std::cout << "range-for: ";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";

    auto it = v.begin();
    std::cout << "*it    = " << *it       << "\n";
    std::cout << "*(it+2)= " << *(it + 2) << "\n";
    std::cout << "it[3]  = " << it[3]     << "  (random-access iterator)\n";

    std::cout << "v.end() - v.begin() = "
              << (v.end() - v.begin()) << "  (size as a difference)\n";
}
