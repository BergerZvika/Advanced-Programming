// Concept: reductions — fold a range into a single value.
//
// Header: <numeric>
//
//   std::accumulate(b, e, init [, op])
//       Left-fold: ((init op v0) op v1) op v2 …  (sequential)
//
//   std::reduce(b, e, init [, op])             [C++17]
//       Same idea but the op MUST be associative & commutative; that lets
//       implementations parallelise. Use it for sums on big ranges.
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};

    int sum     = std::accumulate(v.begin(), v.end(), 0);
    int product = std::accumulate(v.begin(), v.end(), 1,
                                  [](int acc, int x){ return acc * x; });
    std::cout << "sum     = " << sum     << "\n";
    std::cout << "product = " << product << "\n";

    // reduce — order is unspecified; only valid for ass+comm ops
    int rsum = std::reduce(v.begin(), v.end(), 0);
    std::cout << "reduce  = " << rsum << "  (same answer, possibly faster)\n";

    // String concatenation with accumulate (NOT reduce — concat is non-commutative)
    std::vector<std::string> words{"the", "quick", "fox"};
    std::string joined = std::accumulate(
        words.begin(), words.end(), std::string{},
        [](const std::string& acc, const std::string& w){
            return acc.empty() ? w : acc + " " + w;
        });
    std::cout << "joined  = " << joined << "\n";
}
