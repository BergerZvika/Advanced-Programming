// Concept: function overloading — same name, different parameter list.
//
// vs C:
//   C does NOT allow two functions with the same name. Every external
//   identifier is unique. Standard library writers had to invent names like
//   abs / labs / fabsf / fabsl just to differentiate by argument type.
//   In C++ the COMPILER picks the right overload by looking at argument types
//   ('overload resolution'), and the linker sees the mangled (decorated)
//   names that include those types.
#include <iostream>
#include <string>

void print(int n)               { std::cout << "  print(int)    " << n << "\n"; }
void print(double d)            { std::cout << "  print(double) " << d << "\n"; }
void print(const std::string& s){ std::cout << "  print(string) " << s << "\n"; }

// Overloads can also differ by const-ness or reference / pointer:
void mark(int& x)               { x = 1; std::cout << "  mark(int&)\n"; }
void mark(const int& x)         { (void)x; std::cout << "  mark(const int&)\n"; }

int main() {
    print(7);
    print(3.14);
    print(std::string("hello"));

    int a = 0;
    const int b = 0;
    mark(a);   // → mark(int&)
    mark(b);   // → mark(const int&)
}
