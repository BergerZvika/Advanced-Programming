// Concept: where the 'const' keyword goes determines what is read-only.
//   const T*      — pointer to const data        (cannot modify *p, can reseat p)
//   T* const      — const pointer to data        (cannot reseat p, can modify *p)
//   const T* const — const pointer to const data (neither)
#include <iostream>

int main() {
    int x = 10, y = 20;

    const int* pc = &x;          // pointer-to-const
    pc = &y;                     // OK — reseating allowed
    // *pc = 30;                 // ← error: target is read-only
    std::cout << "pc points to " << *pc << "\n";

    int* const cp = &x;          // const pointer
    *cp = 42;                    // OK — value mutable
    // cp = &y;                  // ← error: pointer is fixed
    std::cout << "x via cp = " << *cp << "\n";

    const int* const cpc = &x;   // const pointer to const
    // *cpc = 0;  // error
    // cpc = &y; // error
    std::cout << "*cpc = " << *cpc << "\n";
}
