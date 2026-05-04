// Concept: static_cast<T>(x) — explicit, compile-time conversion.
//
// vs C: in C you wrote (T)x, which silently does ANY conversion the compiler
// can think of: numeric, pointer, dropping const, … all in one. C++ splits
// that into FOUR named casts so the intent is reviewable:
//
//   static_cast      explicit but reasonable conversions
//   dynamic_cast     runtime-checked downcast (this lab's 17b)
//   const_cast       strip const / volatile         (this lab's 17c)
//   reinterpret_cast bit-level reinterpretation     (this lab's 17d, dangerous)
//
// Use static_cast for: numeric narrowing, void* ↔ T*, base→derived (when you
// already know the dynamic type), enum ↔ integer, etc.
#include <iostream>

int main() {
    // 1) Numeric — replaces the C-style (int)x
    double d = 3.99;
    int i = static_cast<int>(d);            // truncation
    std::cout << "  int(3.99)   = " << i << "\n";

    // 2) void* → T* — explicit, type-safe form of the C cast you'd write
    //    after malloc.
    int n = 42;
    void* vp = &n;
    int* ip = static_cast<int*>(vp);
    std::cout << "  via void*  *ip = " << *ip << "\n";

    // 3) enum ↔ int — strongly-typed enums need an explicit cast either way
    enum class Color { Red, Green, Blue };
    int code = static_cast<int>(Color::Green);
    Color c  = static_cast<Color>(2);        // back to Color::Blue
    std::cout << "  Color::Green code = " << code
              << ", roundtrip = " << static_cast<int>(c) << "\n";

    // 4) static_cast WILL refuse meaningless conversions at compile time.
    //    e.g. int* → double* is illegal — for that you'd need reinterpret_cast.
    // double* dp = static_cast<double*>(ip);   // ← compile error
}
