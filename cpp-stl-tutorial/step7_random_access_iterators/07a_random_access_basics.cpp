// Concept: RANDOM ACCESS ITERATORS — the most powerful tier.
// Every operation a raw pointer supports works in O(1):
//
//   it + n        jump forward by n          (O(1))
//   it - n        jump backward
//   it[n]         subscript — same as *(it + n)
//   it1 - it2     distance — an integer
//   it1 < it2     ordering: is one before the other?
//
// Containers whose iterators are random-access:
//   std::vector, std::deque, std::array, raw C arrays (via pointers)
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{10, 20, 30, 40, 50, 60, 70};
    auto it = v.begin();

    // Jumps in O(1)
    std::cout << "*(it + 0) = " << *(it + 0) << "\n";
    std::cout << "*(it + 4) = " << *(it + 4) << "\n";
    std::cout << "it[6]     = " <<   it[6]   << "  (same as *(it + 6))\n";

    // Distance via subtraction — exact opposite of advance:
    auto end = v.end();
    std::cout << "end - begin = " << (end - it) << "\n";

    // Ordering — '<' tells you which is closer to begin
    auto a = it + 2;
    auto b = it + 5;
    std::cout << "a < b ? " << (a < b ? "yes" : "no") << "\n";
}
