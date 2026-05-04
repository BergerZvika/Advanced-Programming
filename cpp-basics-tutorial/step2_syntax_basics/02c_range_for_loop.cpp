// Concept: range-based for loop (C++11).
//
// vs C:
//   In C you write either an index loop or a pointer loop:
//       for (int i = 0; i < n; ++i) sum += arr[i];
//   In C++ the range-for visits each element directly:
//       for (auto x : container) sum += x;
//   Works for any type with begin()/end(): arrays, vectors, maps, …
//   Use 'const auto&' to avoid copies. (See step 5 — auto.)
#include <iostream>
#include <vector>

int main() {
    int arr[] = {10, 20, 30, 40};
    std::vector<int> v{1, 2, 3, 4, 5};

    int s1 = 0;
    for (int i = 0; i < 4; ++i) s1 += arr[i];     // C-style index loop
    std::cout << "C-style sum  = " << s1 << "\n";

    int s2 = 0;
    for (int x : arr) s2 += x;                     // range-for over a C array
    std::cout << "range-for arr= " << s2 << "\n";

    int s3 = 0;
    for (const auto& x : v) s3 += x;               // const auto& — no copies
    std::cout << "range-for v  = " << s3 << "\n";
}
