// Concept: predefined functor templates in <functional>.
//
// You don't have to write your own — the standard library supplies the
// common ones as TEMPLATES.
//
//   std::plus<T>        a + b
//   std::minus<T>       a - b
//   std::multiplies<T>  a * b
//   std::divides<T>     a / b
//   std::negate<T>      -a              (unary)
//   std::less<T>        a <  b
//   std::greater<T>     a >  b
//   std::less_equal<T>      a <= b
//   std::equal_to<T>    a == b
//   std::logical_and<T> a && b
//   std::logical_not<T> !a              (unary)
//
// Pass them to std::sort, std::accumulate, std::transform, priority_queue, …
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> v{5, 2, 8, 1, 4};

    // Sort descending using std::greater
    std::sort(v.begin(), v.end(), std::greater<int>{});
    std::cout << "sorted desc:";
    for (int x : v) std::cout << " " << x;
    std::cout << "\n";

    // Product = accumulate with std::multiplies as the binary op
    std::vector<int> nums{1, 2, 3, 4};
    int product = std::accumulate(nums.begin(), nums.end(), 1, std::multiplies<int>{});
    std::cout << "product 1·2·3·4 = " << product << "\n";

    // Element-wise sum of two ranges via std::transform + std::plus
    std::vector<int> a{10, 20, 30}, b{1, 2, 3}, sum(3);
    std::transform(a.begin(), a.end(), b.begin(), sum.begin(), std::plus<int>{});
    std::cout << "a + b      :";
    for (int x : sum) std::cout << " " << x;
    std::cout << "\n";

    // Negate — unary functor
    std::vector<int> neg(a.size());
    std::transform(a.begin(), a.end(), neg.begin(), std::negate<int>{});
    std::cout << "negate(a)  :";
    for (int x : neg) std::cout << " " << x;
    std::cout << "\n";
}
