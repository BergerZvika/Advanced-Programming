// Concept: brace (uniform) initialisation of aggregates.
//
// vs C:
//   C99 designated initialisers:  struct Point p = { .x = 1, .y = 2 };
//   In C++ since C++11, brace init works for aggregates AND many other types
//   uniformly — same syntax for ints, structs, arrays, std::vector, etc.
#include <iostream>
#include <string>
#include <vector>

struct Point { int x, y; };

int main() {
    // Aggregate brace init — like C, but no '.x =' designator before C++20:
    Point p{3, 4};

    // Array brace init:
    int arr[4]{1, 2, 3, 4};

    // STL containers — brace init is uniform:
    std::vector<int>         v{10, 20, 30};
    std::vector<std::string> names{"Ada", "Linus", "Bjarne"};

    std::cout << "p=(" << p.x << "," << p.y << ")  arr[2]=" << arr[2]
              << "  v.size=" << v.size() << "  names[2]=" << names[2] << "\n";
}
