// Concept: structured exception handling — throw / try / catch.
//
// vs C: in C, errors flow through return codes, errno, or longjmp.
//   - Every caller has to remember to check the return value.
//   - Cleanup of allocated resources between the failure site and the
//     handler is your responsibility.
// In C++ the language unwinds the stack for you between 'throw' and 'catch',
// running destructors as it goes (this is what makes RAII work — see file 15c).
//
// Throw any object you like; usually a class derived from std::exception.
#include <iostream>
#include <stdexcept>     // std::runtime_error, std::out_of_range, std::logic_error
#include <string>

double safe_divide(double a, double b) {
    if (b == 0) throw std::runtime_error("division by zero");
    return a / b;
}

int main() {
    // ── one try, multiple catch handlers ────────────────────
    try {
        std::cout << "  10 / 2 = " << safe_divide(10, 2) << "\n";
        std::cout << "  10 / 0 = " << safe_divide(10, 0) << "\n";   // throws here
        std::cout << "  this line never runs\n";
    } catch (const std::runtime_error& e) {
        std::cout << "  caught runtime_error: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "  caught any std::exception: " << e.what() << "\n";
    } catch (...) {
        std::cout << "  caught anything else\n";
    }

    // ── catch by const reference to avoid slicing the exception ──
    // Catching by VALUE would slice an std::out_of_range down to std::exception.
    try {
        throw std::out_of_range("oob");
    } catch (const std::exception& e) {
        std::cout << "  caught: " << e.what() << "\n";
    }

    std::cout << "  program continues normally after a handled exception\n";
}
