// Concept: VARIADIC TEMPLATES — accept any number of arguments of any types
// (a "parameter pack"). Introduced in C++11.
//
// vs C: in C you'd reach for the unsafe printf-style va_list. Variadic
// templates are TYPE-SAFE: the compiler knows each pack element's type and
// generates code accordingly.
//
// C++17 added FOLD EXPRESSIONS — a clean way to apply a binary operator
// across the pack: (args + ...), (... + args), etc.
#include <iostream>
#include <string>

// Fold expression — sum any number of values
template <typename... Ts>
auto sum(Ts... args) {
    return (args + ...);                  // unary right fold over '+'
}

// Print all arguments separated by spaces
template <typename... Ts>
void print_all(const Ts&... args) {
    ((std::cout << args << " "), ...);    // fold over the comma operator
    std::cout << "\n";
}

// sizeof... gives the pack size at compile time
template <typename... Ts>
constexpr size_t arg_count(Ts...) {
    return sizeof...(Ts);
}

int main() {
    std::cout << "sum(1,2,3,4)               = " << sum(1, 2, 3, 4) << "\n";
    std::cout << "sum(1.5, 2.5, 3.0)         = " << sum(1.5, 2.5, 3.0) << "\n";

    print_all(1, "hello", 3.14, std::string("world"));

    std::cout << "arg_count(1, 'a', 3.14)    = "
              << arg_count(1, 'a', 3.14) << "\n";
}
