// Concept: increment ++ and decrement --.
//
// Two flavours each:
//   PREFIX  ++c    — modify + return reference: T& operator++();
//   POSTFIX c++    — modify + return OLD value: T operator++(int);
//                    The 'int' parameter is a marker — never used.
//
// Prefer prefix when the old value isn't needed: it returns by reference and
// avoids a copy.
#include <iostream>

class Counter {
public:
    Counter() : n_(0) {}

    // Prefix ++   — increment, return reference to *this
    Counter& operator++() {
        ++n_;
        return *this;
    }

    // Postfix ++  — return the OLD value (a copy), then increment
    Counter operator++(int /*unused*/) {
        Counter old = *this;
        ++n_;
        return old;
    }

    // Mirror for --
    Counter& operator--()        { --n_; return *this; }
    Counter  operator--(int)     { Counter old = *this; --n_; return old; }

    int value() const { return n_; }
private:
    int n_;
};

int main() {
    Counter c;
    std::cout << "  c = " << c.value() << "\n";

    ++c;                 // prefix
    std::cout << "  ++c    → c = " << c.value() << "\n";

    Counter d = c++;     // postfix — d gets the OLD value, then c increments
    std::cout << "  c++    → c = " << c.value() << "  d = " << d.value() << "\n";

    --c;
    std::cout << "  --c    → c = " << c.value() << "\n";

    // Prefer prefix when you don't need the old value (no unnecessary copy):
    for (int i = 0; i < 3; ++i) ++c;
    std::cout << "  three ++c → c = " << c.value() << "\n";
}
