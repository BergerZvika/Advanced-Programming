// Concept: std::vector — the workhorse dynamic array (contiguous heap storage).
//
// vs C: in C you'd write your own malloc + realloc + size/capacity tracking.
// vector does all of that, frees its memory in its destructor (RAII), and
// supports element types with constructors/destructors.
//
// Big-O:
//   push_back / pop_back  → amortised O(1)
//   index access [i]      → O(1)
//   insert/erase middle   → O(n)
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    v.push_back(4);
    v.push_back(5);

    std::cout << "size=" << v.size()
              << "  capacity=" << v.capacity()
              << "  v[0]=" << v[0] << "\n";

    std::cout << "elements:";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";

    // Reserve avoids reallocations when you know the final size:
    std::vector<int> big;
    big.reserve(1000);

    v.erase(v.begin() + 1);
    std::cout << "after erase v[1]:";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";

    // .data() yields a raw pointer to use with C APIs:
    int* raw = v.data();
    std::cout << "raw[0] = " << raw[0] << "\n";
}
