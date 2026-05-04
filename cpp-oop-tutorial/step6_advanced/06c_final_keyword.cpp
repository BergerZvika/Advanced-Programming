// Concept: 'final' (C++11)
//   - on a method:  cannot be overridden in further-derived classes
//   - on a class:   cannot be derived from at all
#include <iostream>

class Base {
public:
    virtual ~Base() = default;
    virtual void go() { std::cout << "  Base::go\n"; }
};

class Middle : public Base {
public:
    void go() final { std::cout << "  Middle::go (final)\n"; }   // sealed override
};

// Anyone trying to override go() in a class derived from Middle will fail to compile.
class Child : public Middle {
public:
    // void go() override { ... }   // ← compile error: 'go' is final in Middle
};

class Sealed final {           // class itself is final → cannot be a base
public:
    void show() const { std::cout << "  Sealed::show\n"; }
};

// class TrySubclass : public Sealed {};   // ← compile error: 'Sealed' is final

int main() {
    Child c; c.go();
    Sealed s; s.show();
    std::cout << "(further override of Middle::go, or deriving from Sealed, is illegal)\n";
}
