// Concept: apply a function to every element.
//
//   std::for_each(b, e, fn)            fn called on each element (side effect)
//   std::transform(b, e, dst, fn)      writes fn(*it) to dst
//   std::transform(b1, e1, b2, dst, binop)   element-wise on two ranges
//
// vs C: you'd write the loop. Pulling it into an algorithm + lambda makes
// the INTENT visible.
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};

    std::for_each(v.begin(), v.end(),
                  [](int x){ std::cout << x << " "; });
    std::cout << "\n";

    std::vector<int> sq;
    std::transform(v.begin(), v.end(), std::back_inserter(sq),
                   [](int x){ return x * x; });
    std::cout << "squared:";
    for (int x : sq) std::cout << " " << x;
    std::cout << "\n";

    std::vector<int> a{1, 2, 3}, b{10, 20, 30}, sum;
    std::transform(a.begin(), a.end(), b.begin(),
                   std::back_inserter(sum),
                   [](int x, int y){ return x + y; });
    std::cout << "a + b  :";
    for (int x : sum) std::cout << " " << x;
    std::cout << "\n";
}
