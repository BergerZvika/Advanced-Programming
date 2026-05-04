// Concept: rvalue references + std::move.
//
//   T&&  — an rvalue reference. Used to identify "this resource is about to
//          die — you can steal from it instead of copying it".
//   std::move — a CAST that turns an lvalue expression into an rvalue
//          expression. By itself it does not move; it merely AUTHORISES a
//          subsequent operation (e.g. a move constructor) to do so.
//
// vs C:
//   C has no concept of move semantics. Every assignment is effectively a
//   bytewise copy. C++11 move semantics turn unnecessary copies of large
//   objects (strings, vectors) into pointer-steals.
#include <iostream>
#include <string>
#include <utility>     // std::move

void show(const std::string& s) { std::cout << "  lvalue overload: " << s << "\n"; }
void show(std::string&& s)      { std::cout << "  rvalue overload: " << s << "  (about to vanish)\n"; }

int main() {
    std::string a = "alpha";

    show(a);                         // lvalue → calls const&
    show(std::string("beta"));       // unnamed temp → calls &&
    show(std::move(a));              // cast a to rvalue → calls &&

    // Where the steal actually happens — std::string's move constructor:
    std::string b = std::move(a);
    std::cout << "  after move: a='" << a    // moved-from, often empty
              << "'  b='" << b << "'\n";
}
