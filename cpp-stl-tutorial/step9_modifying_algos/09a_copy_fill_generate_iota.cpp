// Concept: producing values into an output range.
//
//   std::copy(b, e, dst)            copy each element to dst
//   std::fill(b, e, v)              set every element to v
//   std::fill_n(dst, n, v)          same, given a count
//   std::generate(b, e, fn)         set each element to fn()
//   std::iota(b, e, start)          0,1,2,…  in <numeric>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>     // iota
#include <vector>

int main() {
    std::vector<int> src{10, 20, 30, 40};
    std::vector<int> dst;
    std::copy(src.begin(), src.end(), std::back_inserter(dst));
    std::cout << "copy:";
    for (int x : dst) std::cout << " " << x;
    std::cout << "\n";

    std::vector<int> z(5);
    std::fill(z.begin(), z.end(), 7);
    std::cout << "fill(7):";
    for (int x : z) std::cout << " " << x;
    std::cout << "\n";

    int counter = 0;
    std::vector<int> g(5);
    std::generate(g.begin(), g.end(), [&]{
        int i = counter++;
        return i * i;
    });
    std::cout << "generate (i*i):";
    for (int x : g) std::cout << " " << x;
    std::cout << "\n";

    std::vector<int> seq(8);
    std::iota(seq.begin(), seq.end(), 100);    // 100, 101, 102, …
    std::cout << "iota(100):";
    for (int x : seq) std::cout << " " << x;
    std::cout << "\n";
}
