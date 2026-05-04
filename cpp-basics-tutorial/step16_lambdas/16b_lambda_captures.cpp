// Concept: lambda CAPTURE clauses — what surrounding state the lambda sees.
//
//   []        capture nothing
//   [=]       capture every used local BY VALUE
//   [&]       capture every used local BY REFERENCE
//   [x]       capture x by value
//   [&x]      capture x by reference
//   [=, &x]   default by value, but x by reference
//   [x = expr]  init capture (C++14) — store a fresh member with a value
//
// 'mutable' (after the parameter list) lets the body modify by-value captures.
// Without 'mutable', the lambda's operator() is implicitly const — so you
// can't write through copy captures.
#include <iostream>

int main() {
    int factor = 10;

    // Capture by value — the lambda holds its own copy of 'factor'.
    auto by_value = [factor](int x){ return x * factor; };
    factor = 999;                       // doesn't affect the captured copy
    std::cout << "  by value (factor was 10): " << by_value(3) << "\n";

    // Capture by reference — the lambda sees the LIVE 'factor'.
    int total = 0;
    auto add_to_total = [&total](int x){ total += x; };
    add_to_total(7); add_to_total(8);
    std::cout << "  by reference total      : " << total << "\n";

    // Mutable + by-value capture — copy is mutable inside the body
    auto counter = [n = 0]() mutable { return ++n; };
    std::cout << "  counter: " << counter()
              << ", " << counter()
              << ", " << counter() << "\n";

    // Mixed: default by value, but capture 'total' by reference
    int x = 100;
    auto mix = [=, &total](int extra){ total += x + extra; };
    mix(5);
    std::cout << "  mixed: total = " << total << "\n";
}
