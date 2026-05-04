// Concept: default values for template parameters.
//
// Like default function arguments, but at the type level. Saves callers from
// spelling out the boilerplate type when the default is what they want.
//
// std::vector<T, Alloc = std::allocator<T>> is a real example — the second
// parameter has a default, which is why we just write std::vector<int>.
#include <functional>     // std::less, std::greater
#include <iostream>
#include <set>

// MyVec<T, Cap=16> — capacity defaults to 16 if not specified.
template <typename T, size_t Cap = 16>
class MyVec {
public:
    constexpr size_t capacity() const { return Cap; }
};

int main() {
    MyVec<int>      a;          // T=int, Cap=16 (default)
    MyVec<int, 64>  b;          // T=int, Cap=64
    std::cout << "default cap = " << a.capacity() << "\n";
    std::cout << "custom  cap = " << b.capacity() << "\n";

    // std::set takes <Key, Compare = std::less<Key>>:
    std::set<int> ascending{3, 1, 2};                       // default less
    std::set<int, std::greater<int>> descending{3, 1, 2};   // override

    std::cout << "asc :";  for (int x : ascending)  std::cout << " " << x; std::cout << "\n";
    std::cout << "desc:";  for (int x : descending) std::cout << " " << x; std::cout << "\n";
}
