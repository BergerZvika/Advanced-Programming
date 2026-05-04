// Concept: when to use a pointer vs a reference.
//
//   Use a REFERENCE when:
//     - The thing always exists (no "no value" case).
//     - You will not reseat to a different object.
//     - You want the call site to look like 'f(x)' instead of 'f(&x)'.
//
//   Use a POINTER when:
//     - "No value" is meaningful → nullptr.
//     - You may want to reseat or do pointer arithmetic.
//     - You manage ownership manually (or via smart pointers — step 13).
//
//   Behaviour comparison:
#include <iostream>

void via_pointer(int* p) {
    if (p) ++*p;        // must check null!
}
void via_reference(int& r) {
    ++r;                // can never be null — no check needed
}

int main() {
    int n = 10;
    via_pointer(&n);    // address-of at the call site
    via_reference(n);   // looks like a normal value pass
    std::cout << "n after both = " << n << "  (started at 10)\n";

    int* p = nullptr;
    via_pointer(p);     // safe — function checked for null
    std::cout << "via_pointer(nullptr) returned safely\n";
    // via_reference(*p);  // ← UB: dereferencing null
}
