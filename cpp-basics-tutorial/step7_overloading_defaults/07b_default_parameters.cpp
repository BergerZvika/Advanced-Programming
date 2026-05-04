// Concept: default parameters — a parameter with a default value can be
// omitted at the call site.
//
// vs C:
//   C has NO default parameters. You either pass every argument or write
//   a wrapper function. C++ lets the function declare its own fallbacks.
//
// Rules:
//   - Defaults must be at the END of the parameter list.
//   - They are part of the DECLARATION, not the definition — so headers
//     normally carry them, and the body should not repeat them.
#include <iostream>
#include <string>

void greet(const std::string& name = "World", int times = 1) {
    for (int i = 0; i < times; ++i)
        std::cout << "  Hello, " << name << "!\n";
}

int main() {
    greet();                  // → "Hello, World!" once
    greet("Alice");           // → "Hello, Alice!" once
    greet("Bob", 3);          // → 3 times
    // greet(, 5);            // ← compile error: cannot skip a non-trailing argument
}
