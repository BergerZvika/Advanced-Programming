// Concept: friendship is NOT transitive. If A is friend of B and B is friend
// of C, A still cannot see C's privates.
#include <iostream>

class C {
public:
    C() : data_(7) {}
    friend class B;     // only B can see C's privates
private:
    int data_;
};

class B {
public:
    B() : b_data_(3) {}
    int read_C(const C& c) { return c.data_; }   // OK — B is friend of C
    friend class A;
private:
    int b_data_;
};

class A {
public:
    int read_B(B& b)       { return b.b_data_; }     // OK — A is friend of B
    // int read_C(const C& c) { return c.data_; }    // ← compile error:
    //   friendship not transitive — A is NOT a friend of C
};

int main() {
    A a;  B b;  C c;
    std::cout << "B reads C::data_   = " << b.read_C(c) << "\n";
    std::cout << "A reads B::b_data_ = " << a.read_B(b) << "\n";
    std::cout << "A CANNOT read C::data_ directly (friend not transitive)\n";
}
