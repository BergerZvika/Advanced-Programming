// Concept: lvalues and rvalues.
//
//   lvalue — has a name and an address: a variable, a returned reference.
//            You can take its address with '&'. Persists across statements.
//   rvalue — temporary / about to die: a literal, the result of x + y,
//            a function returning by value. About to be discarded.
//
// vs C:
//   C has the lvalue/rvalue concept too, but it never had the language tools
//   to BIND to an rvalue and steal its resources. C++11 introduced rvalue
//   references ('T&&') exactly for that.
#include <iostream>

int  produce()    { return 42; }       // returns by value → result is an rvalue
int& alias_to(int& x) { return x; }    // returns lvalue reference

int main() {
    int x = 5;
    int& lref = x;                     // lvalue reference — must bind to an lvalue
    // int& bad = 5;                   // ← error: 5 is an rvalue
    const int& clref = 5;              // OK: const lvalue ref CAN bind to an rvalue

    int&& rref = 5;                    // rvalue reference — binds to a temporary
    int&& rref2 = produce();           // ditto

    std::cout << "x=" << x << "  &x=" << &x << "\n";
    std::cout << "lref=" << lref << "  &lref=" << &lref << "  (same as &x)\n";
    std::cout << "clref=" << clref << "  (bound to a temporary 5)\n";
    std::cout << "rref=" << rref << "  rref2=" << rref2 << "\n";

    // alias_to(x)   is an lvalue (returns int&) → could appear on left of =:
    alias_to(x) = 99;
    std::cout << "x after alias_to(x)=99 → " << x << "\n";
}
