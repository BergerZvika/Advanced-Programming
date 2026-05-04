// Concept: a LAMBDA is just sugar for an anonymous functor class.
//
//   [factor](int x){ return x * factor; }
//   ────────────────────────────────────
//   The compiler generates an unnamed class, roughly:
//     class __lambda {
//         int factor_;
//     public:
//         __lambda(int f) : factor_(f) {}
//         auto operator()(int x) const { return x * factor_; }
//     };
//
// Capture clauses control the data members:
//   []        capture nothing
//   [=]       capture every used variable BY VALUE
//   [&]       capture every used variable BY REFERENCE
//   [x]       capture x by value
//   [&x]      capture x by reference
//   [=, &x]   default by value, but x by reference
//   [x = expr]  init capture (C++14) — name a fresh member with a value
//
// Add 'mutable' to allow modifying the by-value captures inside the lambda.
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};

    // [factor] → a member named factor stored by value
    int factor = 10;
    std::vector<int> scaled(v.size());
    std::transform(v.begin(), v.end(), scaled.begin(),
                   [factor](int x){ return x * factor; });
    std::cout << "factor*v:";
    for (int x : scaled) std::cout << " " << x;
    std::cout << "\n";

    // [&] capture by reference — let the lambda mutate caller-side state
    int sum = 0;
    std::for_each(v.begin(), v.end(), [&sum](int x){ sum += x; });
    std::cout << "sum via &capture: " << sum << "\n";

    // mutable + by-value capture — counter lives inside each call invocation
    int call = 0;
    auto numbered = [call](int x) mutable {
        ++call;
        return std::pair{call, x};
    };
    auto [c1, x1] = numbered(7);
    auto [c2, x2] = numbered(8);
    std::cout << "numbered(7)=(" << c1 << "," << x1 << ")  "
              << "numbered(8)=(" << c2 << "," << x2 << ")\n";
    // Note: each lambda VALUE has its own call counter — copies don't share state.
}
