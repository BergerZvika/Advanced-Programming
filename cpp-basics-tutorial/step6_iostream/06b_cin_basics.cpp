// Concept: std::cin — type-safe stream input.
//
// vs C:
//   scanf needs format strings + the address of every output, and silently
//   misbehaves on type mismatch.
//   cin >> x parses according to x's type and sets a 'fail' flag if parsing
//   fails. Always check the stream state — if the user types garbage where
//   you expect a number, cin goes into a failed state until you clear it.
//
// Pipe input for testing:  echo "42 3.14 hello" | ./build/06b_cin_basics
#include <iostream>
#include <string>

int main() {
    int    n;
    double d;
    std::string word;

    std::cout << "Reading: int double word ...\n";

    if (std::cin >> n >> d >> word) {
        std::cout << "  n=" << n << "  d=" << d << "  word='" << word << "'\n";
    } else {
        std::cout << "  parse failed (set badbit/failbit)\n";
    }

    // To read a WHOLE line (including spaces) use std::getline:
    // std::string line;
    // std::getline(std::cin, line);
}
