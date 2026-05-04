// Concept: std::array<T, N> — fixed-size array with the type's full power.
//
// vs C: a C array (int a[5]) decays to a pointer when passed to a function
// and forgets its size. std::array is a real type that remembers its size,
// supports begin()/end(), is copyable/assignable, and can be returned by value.
#include <array>
#include <iostream>

int main() {
    std::array<int, 5> a{10, 20, 30, 40, 50};

    std::cout << "size       = " << a.size()  << "\n";
    std::cout << "front/back = " << a.front() << " / " << a.back() << "\n";
    std::cout << "a.at(2)    = " << a.at(2)   << "  (bounds-checked, throws on bad index)\n";

    int sum = 0;
    for (int x : a) sum += x;
    std::cout << "sum        = " << sum << "\n";

    std::array<int, 5> b = a;     // copy
    b[0] = 999;
    std::cout << "a[0]=" << a[0] << "  b[0]=" << b[0] << "  (independent copies)\n";
}
