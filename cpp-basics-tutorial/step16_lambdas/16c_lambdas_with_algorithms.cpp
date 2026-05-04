// Concept: lambdas + STL algorithms — the canonical pairing.
//
// Most STL algorithms accept any "callable" as their predicate or transform
// argument: free functions, function objects, std::function, OR lambdas.
// Lambdas win for ad-hoc one-liners that don't deserve a name.
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // count_if + lambda
    int evens = std::count_if(v.begin(), v.end(),
                              [](int x){ return x % 2 == 0; });
    std::cout << "  even count          : " << evens << "\n";

    // find_if + lambda
    auto big = std::find_if(v.begin(), v.end(),
                            [](int x){ return x > 7; });
    std::cout << "  first > 7           : " << *big << "\n";

    // transform — square each element into a new vector
    std::vector<int> squared;
    std::transform(v.begin(), v.end(), std::back_inserter(squared),
                   [](int x){ return x * x; });
    std::cout << "  squared             :";
    for (int x : squared) std::cout << " " << x;
    std::cout << "\n";

    // accumulate with a custom binary op (here: product)
    int product = std::accumulate(v.begin(), v.end(), 1,
                                  [](int acc, int x){ return acc * x; });
    std::cout << "  10! via accumulate  : " << product << "\n";

    // sort by absolute distance to a target
    int target = 5;
    std::sort(v.begin(), v.end(),
              [target](int a, int b){
                  return std::abs(a - target) < std::abs(b - target);
              });
    std::cout << "  sorted by |x - 5|   :";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";
}
