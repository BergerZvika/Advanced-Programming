// Concept: const_cast strips constness. Useful only for legacy interfaces
// that take T* but don't actually mutate.
// ⚠ WARNING — modifying a truly const object via const_cast is UNDEFINED BEHAVIOUR.
#include <iostream>
#include <string>

// Imagine a legacy C function that takes char*; in practice it only reads.
void legacy_print(char* msg) { std::cout << "  legacy_print: " << msg << "\n"; }

int main() {
    std::string s = "Hello";
    // legacy_print(s.data());     // OK in C++17+, but suppose we have a const char*:
    const char* msg = s.c_str();
    legacy_print(const_cast<char*>(msg));   // safe: legacy_print never writes

    // ⚠ DON'T:
    //   const int x = 5;
    //   *const_cast<int*>(&x) = 99;   // UB — x might live in read-only memory
    std::cout << "(const_cast on a truly const object = undefined behaviour — never do that)\n";
}
