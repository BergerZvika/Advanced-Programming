// Concept: more numeric algorithms (header <numeric>).
//
//   std::inner_product(b1, e1, b2, init)        Σ a_i * b_i  (dot product)
//   std::partial_sum(b, e, dst)                 prefix sums  s_k = Σ_{i≤k} a_i
//   std::adjacent_difference(b, e, dst)         differences  d_0=a_0, d_k=a_k-a_{k-1}
//
// All three accept a custom binary op as a final argument, so you can build
// running products, ratios, etc.
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> a{1, 2, 3, 4};
    std::vector<int> b{10, 20, 30, 40};

    int dot = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    std::cout << "dot(a, b) = " << dot << "  (1·10 + 2·20 + 3·30 + 4·40)\n";

    std::vector<int> ps;
    std::partial_sum(a.begin(), a.end(), std::back_inserter(ps));
    std::cout << "partial_sum(a):";
    for (int x : ps) std::cout << " " << x;
    std::cout << "\n";

    std::vector<int> ad;
    std::adjacent_difference(ps.begin(), ps.end(), std::back_inserter(ad));
    std::cout << "adjacent_difference(prefix sums):";
    for (int x : ad) std::cout << " " << x;
    std::cout << "  (recovers the original a)\n";
}
