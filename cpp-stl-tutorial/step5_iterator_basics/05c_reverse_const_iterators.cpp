// Concept: reverse iterators and const iterators.
//
//   .rbegin() / .rend()   iterate from END toward BEGINNING
//   .cbegin() / .cend()   const iterators (you cannot write through them)
//   .crbegin() / .crend() both
//
// Reverse iterators let any algorithm run "backwards" without rewriting it:
// std::find, std::sort, std::copy, etc. all work on rbegin/rend.
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};

    std::cout << "forward: ";
    for (auto it = v.begin(); it != v.end(); ++it) std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "reverse: ";
    for (auto it = v.rbegin(); it != v.rend(); ++it) std::cout << *it << " ";
    std::cout << "\n";

    // const iterators — promise read-only access:
    for (auto it = v.cbegin(); it != v.cend(); ++it) {
        // *it = 99;   // ← compile error
        (void)it;
    }
    std::cout << "(cbegin/cend → read-only view)\n";

    // Modern style: 'const auto&' in a range-for replaces explicit cbegin/cend.
    int sum = 0;
    for (const auto& x : v) sum += x;
    std::cout << "sum = " << sum << "\n";
}
