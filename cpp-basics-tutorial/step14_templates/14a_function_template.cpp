// Concept: a FUNCTION TEMPLATE generates a family of functions, one per type.
//
// vs C: in C the closest tool is a macro:
//     #define MAX(a,b) ((a) > (b) ? (a) : (b))
//   Macros do textual substitution → no type checking, weird precedence,
//   double evaluation of arguments, no overloading.
//   A C++ template is type-checked, has the right precedence and exactly-one
//   evaluation per argument, and the compiler INSTANTIATES one real function
//   per type used at the call site.
#include <iostream>
#include <string>

template <typename T>
T max_of(T a, T b) {
    return (a > b) ? a : b;
}

// Multiple template parameters
template <typename A, typename B>
auto plus_promoted(A a, B b) -> decltype(a + b) {
    return a + b;
}

int main() {
    std::cout << "max_of(3, 7)         = " << max_of(3, 7)         << "\n";
    std::cout << "max_of(2.5, 1.5)     = " << max_of(2.5, 1.5)     << "\n";
    std::cout << "max_of('a', 'z')     = " << max_of('a', 'z')     << "\n";
    std::cout << "max_of<\"hi\",\"abc\")= "
              << max_of<std::string>("hi", "abc") << "\n";

    // The compiler can usually deduce T from the arguments.
    // If you want to force the type, write it explicitly: max_of<double>(3, 4.5).
    std::cout << "max_of<double>(3, 4.5) = " << max_of<double>(3, 4.5) << "\n";

    // Mixed types — the deduced return type is whatever 'a + b' would be.
    auto x = plus_promoted(1, 2.5);   // int + double → double
    std::cout << "plus_promoted(1, 2.5) = " << x << "  (auto deduced double)\n";
}
