// Concept: TEMPLATE SPECIALISATION — provide a custom implementation for a
// specific type (FULL specialisation) or a narrower family of types (PARTIAL).
//
// The general template is the fallback; specialisations win when they match.
//
// Common use: optimise / customise behaviour for a particular T (e.g. give
// a different printer for bool to write "true"/"false" instead of 1/0).
#include <iostream>
#include <string>

// ── Primary template ───────────────────────────────────────
template <typename T>
struct Printer {
    static void print(const T& v) {
        std::cout << "  generic: " << v << "\n";
    }
};

// ── Full specialisation for bool ──────────────────────────
template <>
struct Printer<bool> {
    static void print(bool v) {
        std::cout << "  bool   : " << (v ? "true" : "false") << "\n";
    }
};

// ── Full specialisation for std::string ───────────────────
template <>
struct Printer<std::string> {
    static void print(const std::string& v) {
        std::cout << "  string : \"" << v << "\"\n";
    }
};

// ── Partial specialisation: T* (any pointer) ──────────────
template <typename T>
struct Printer<T*> {
    static void print(const T* p) {
        if (!p) {
            std::cout << "  pointer: nullptr\n";
            return;
        }
        std::cout << "  pointer →";
        Printer<T>::print(*p);
    }
};

int main() {
    int n = 42;
    Printer<int>::print(n);
    Printer<bool>::print(true);
    Printer<std::string>::print(std::string("hi"));
    Printer<int*>::print(&n);          // partial specialisation T*
    Printer<double>::print(3.14);      // falls through to the primary
}
