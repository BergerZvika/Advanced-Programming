// Concept: std::pair — bundle two heterogeneous values.
//
// vs C: a one-off struct for every (a, b) you need. std::pair gives you
// .first / .second, comparison, and structured bindings (C++17) for free.
// It is the building block of std::map (each entry is a pair<const K, V>).
#include <iostream>
#include <string>
#include <utility>     // std::pair, std::make_pair

int main() {
    std::pair<int, std::string> p{42, "answer"};
    std::cout << "p.first=" << p.first << "  p.second=" << p.second << "\n";

    auto q = std::make_pair(3.14, true);   // template argument deduction

    auto [num, ok] = q;                    // C++17 structured bindings
    std::cout << "num=" << num << "  ok=" << ok << "\n";

    // Pairs compare lexicographically (first then second):
    std::pair<int,int> a{1,2}, b{1,3};
    std::cout << "a < b ? " << (a < b ? "yes" : "no") << "\n";
}
