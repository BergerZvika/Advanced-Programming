// Concept: a raw C pointer satisfies the random-access iterator concept.
// Anywhere an STL algorithm wants a random-access iterator pair, you can
// pass two raw pointers (or a pointer and a length) and it will work.
//
// vs C: the operations you naturally do on T* — `*p`, `++p`, `--p`, `p+n`,
// `p-n`, `p[n]`, `p1 - p2`, `p1 < p2` — are EXACTLY the random-access
// iterator interface. STL containers expose iterators that behave the same.
#include <algorithm>
#include <iostream>
#include <numeric>     // accumulate

int main() {
    int arr[] = {5, 2, 8, 1, 4, 9, 3};
    constexpr int N = sizeof(arr) / sizeof(arr[0]);

    int sum = std::accumulate(arr, arr + N, 0);
    std::cout << "sum  = " << sum << "\n";

    auto mx = std::max_element(arr, arr + N);
    std::cout << "max  = " << *mx
              << "  at index " << (mx - arr) << "\n";

    std::sort(arr, arr + N);
    std::cout << "sorted:";
    for (int* p = arr; p != arr + N; ++p) std::cout << " " << *p;
    std::cout << "\n";

    // The same operations on std::begin / std::end (they pick the right form
    // for both raw arrays and standard containers):
    std::cout << "front element = " << *std::begin(arr)
              << "  back element = " << *(std::end(arr) - 1) << "\n";
}
