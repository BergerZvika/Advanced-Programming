// Concept: number ↔ string conversions in C++.
//
// vs C:
//   number → string :  snprintf(buf, ..., "%d", n)
//   string → number :  atoi / atof / strtol (no error on bad input)
//   In C++ you have:
//     std::to_string(n)   safe number → string
//     std::stoi / stod    string → number, throws on garbage, sets endpos
#include <iostream>
#include <stdexcept>
#include <string>

int main() {
    int    n = 42;
    double d = 3.14;

    std::string s1 = std::to_string(n);            // "42"
    std::string s2 = std::to_string(d);            // "3.140000"
    std::cout << "to_string(int)    = '" << s1 << "'\n";
    std::cout << "to_string(double) = '" << s2 << "'\n";

    // string → number
    int    parsed_int    = std::stoi("123abc");    // stops at 'a' → 123
    double parsed_double = std::stod("2.71xyz");   // stops at 'x' → 2.71
    std::cout << "stoi('123abc')    = " << parsed_int    << "\n";
    std::cout << "stod('2.71xyz')   = " << parsed_double << "\n";

    // Garbage input → exception (atoi would silently return 0).
    try {
        int bad = std::stoi("hello");
        std::cout << "got " << bad << "\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "stoi('hello')     → invalid_argument: " << e.what() << "\n";
    }
}
