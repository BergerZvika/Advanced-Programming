// Concept: const_cast<T>(x) — add or strip 'const' / 'volatile'.
//
// Use cases (rare):
//   - Calling a legacy C API that takes T* but doesn't actually modify it.
//   - Implementing a non-const member function in terms of the const one
//     (the "Meyers trick").
//
// ⚠ Modifying a TRULY const object via const_cast is undefined behaviour.
//    The cast is for cases where the object is non-const but is REACHED
//    through a const handle.
#include <iostream>
#include <string>

// Imagine a legacy C function that takes char* but only reads from it.
void legacy_print(char* msg) {
    std::cout << "  legacy_print: " << msg << "\n";
}

// Meyers idiom: implement non-const operator[] in terms of the const one.
class StringView {
public:
    explicit StringView(const std::string& s) : s_(s) {}

    const char& operator[](size_t i) const { return s_[i]; }

    // Cast away const ON THE RESULT, not on the underlying data.
    char& operator[](size_t i) {
        const auto& self = *this;
        return const_cast<char&>(self[i]);
    }

private:
    std::string s_;
};

int main() {
    // 1) legacy C API
    std::string s = "Hello";
    legacy_print(const_cast<char*>(s.c_str()));   // safe: legacy_print never writes

    // 2) Meyers idiom — one operator[] body shared between const and non-const
    StringView sv(std::string("World"));
    sv[0] = 'M';                                  // calls non-const operator[]
    std::cout << "  sv[0] after write = " << sv[0] << "\n";

    // 3) The dangerous case — DON'T do this:
    //    const int x = 5;
    //    *const_cast<int*>(&x) = 99;   // ← undefined behaviour
    std::cout << "  (writing to a truly-const object via const_cast = UB)\n";
}
