// Concept: sorting.
//
// vs C: qsort takes a void-pointer comparator returning int — slow and
// type-unsafe. std::sort takes ANY callable (free function, lambda,
// function object), is type-safe, and often faster.
//
//   std::sort        O(n log n) — order of equals NOT preserved
//   std::stable_sort O(n log n) — preserves original order of equal elements
//   std::is_sorted   bool — is the range non-decreasing?
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<int> v{4, 2, 5, 2, 1, 3, 5, 4};

    std::sort(v.begin(), v.end());
    std::cout << "asc :";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";

    std::sort(v.begin(), v.end(), std::greater<int>{});
    std::cout << "desc:";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";

    // Lambda comparator — sort strings by length, ties alphabetical
    std::vector<std::string> words{"the", "quick", "brown", "fox", "jumps"};
    std::stable_sort(words.begin(), words.end(),
                     [](const std::string& a, const std::string& b){
                         if (a.size() != b.size()) return a.size() < b.size();
                         return a < b;
                     });
    std::cout << "stable by len:";
    for (const auto& w : words) std::cout << " " << w;
    std::cout << "\n";

    std::cout << "is_sorted? " << std::is_sorted(v.begin(), v.end()) << "\n";
}
