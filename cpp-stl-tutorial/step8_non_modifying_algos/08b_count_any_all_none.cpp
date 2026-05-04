// Concept: counting and predicate quantifiers.
//
//   std::count(b, e, v)      — how many == v
//   std::count_if(b, e, p)   — how many satisfy p
//   std::any_of(b, e, p)     — does ANY element satisfy p?
//   std::all_of(b, e, p)     — do ALL elements satisfy p?
//   std::none_of(b, e, p)    — do NONE?
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 2, 4, 2, 5};

    std::cout << "count(==2)    : " << std::count(v.begin(), v.end(), 2) << "\n";
    std::cout << "count_if(odd) : "
              << std::count_if(v.begin(), v.end(), [](int x){ return x % 2; }) << "\n";

    std::cout << "any  > 4 ? "
              << std::any_of(v.begin(), v.end(), [](int x){ return x > 4; }) << "\n";
    std::cout << "all  > 0 ? "
              << std::all_of(v.begin(), v.end(), [](int x){ return x > 0; }) << "\n";
    std::cout << "none < 0 ? "
              << std::none_of(v.begin(), v.end(), [](int x){ return x < 0; }) << "\n";
}
