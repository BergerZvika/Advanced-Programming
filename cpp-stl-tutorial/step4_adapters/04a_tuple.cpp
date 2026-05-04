// Concept: std::tuple — heterogeneous fixed-size pack (any number of values).
//
// vs C: a struct, or "out" pointers to return multiple values from a function.
// std::tuple lets a function return multiple values directly; C++17 structured
// bindings unpack them at the call site.
#include <iostream>
#include <string>
#include <tuple>

std::tuple<int, double, std::string> stats() {
    return {42, 3.14, "ok"};
}

int main() {
    std::tuple<int, double, std::string> t{1, 2.5, "hello"};

    // Access by index (compile-time)
    std::cout << "get<0>=" << std::get<0>(t)
              << "  get<2>='" << std::get<2>(t) << "'\n";

    // Access by type (only if the type appears exactly once)
    std::cout << "get<double>=" << std::get<double>(t) << "\n";

    // Structured bindings — preferred way to unpack:
    auto [n, pi, status] = stats();
    std::cout << "stats() → n=" << n << "  pi=" << pi
              << "  status=" << status << "\n";

    std::cout << "tuple_size = " << std::tuple_size_v<decltype(t)> << "\n";
}
