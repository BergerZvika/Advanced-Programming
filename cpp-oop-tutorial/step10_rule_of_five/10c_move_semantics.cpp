// Concept: lvalue vs rvalue, std::move, and why move semantics exist.
//   lvalue — has a name, has an address (e.g. a variable)
//   rvalue — temporary / about to die (e.g. function return value)
// std::move is just a CAST: it converts an lvalue to an rvalue reference,
// telling the next operation "feel free to STEAL the resources from this".
// It does not move anything by itself.
#include <iostream>
#include <string>
#include <utility>     // std::move

void take_lvalue(const std::string& s) { std::cout << "  by lvalue ref: " << s << "\n"; }
void take_rvalue(std::string&& s)      { std::cout << "  by rvalue ref: " << s << " (about to be moved)\n"; }

int main() {
    std::string a = "Hello";

    take_lvalue(a);                       // a is an lvalue → bound to const&
    take_rvalue(std::string("World"));    // unnamed temporary → bound to &&

    // std::move is JUST A CAST — by itself it doesn't move anything.
    // Passing the result to a function that expects && does not consume 'a'.
    take_rvalue(std::move(a));
    std::cout << "  after take_rvalue(std::move(a)), a = '" << a
              << "'   ← std::move alone does NOT move\n";

    // The move actually happens here: std::string's MOVE CONSTRUCTOR is invoked.
    // It steals 'a's heap buffer and leaves 'a' in a valid-but-unspecified state.
    std::string b = std::move(a);
    std::cout << "  after string b = std::move(a):\n"
              << "    a = '" << a << "'   ← moved-from (typically empty)\n"
              << "    b = '" << b << "'   ← stole the buffer\n";
}
