// Concept: compound assignment — +=, -=, *=, /=, %=.
//
// Rules:
//   - Always MEMBERS (the left side is always 'this').
//   - Mutate *this; return *this BY REFERENCE so they chain like normal '='.
//   - Signature: T& operator+=(const T& rhs);
//
// Idiom: implement the binary operator (e.g. '+') in terms of '+=' so the
// real arithmetic lives in one place. (See file 11a.)
#include <iostream>

class Money {
public:
    explicit Money(long cents) : cents_(cents) {}

    // Compound assignment — mutates self, returns self.
    Money& operator+=(const Money& rhs) { cents_ += rhs.cents_; return *this; }
    Money& operator-=(const Money& rhs) { cents_ -= rhs.cents_; return *this; }
    Money& operator*=(int k)            { cents_ *= k;          return *this; }

    long cents() const { return cents_; }
private:
    long cents_;
};

// Free '+' built on top of '+='. lhs taken BY VALUE so we already own a copy.
Money operator+(Money lhs, const Money& rhs) { return lhs += rhs; }

void show(const char* tag, const Money& m) {
    std::cout << "  " << tag << " = " << m.cents() << " cents\n";
}

int main() {
    Money a(100), b(250);
    show("a", a);
    show("b", b);

    a += b;                         // 100 → 350
    show("after a += b", a);

    Money c = a + b;                // builds on a + b → += chain
    show("c = a + b   ", c);

    a *= 2;
    show("after a *= 2", a);

    // Chain multiple compound ops in one expression — each returns *this:
    a -= Money(50);
    a -= Money(50);
    show("after two -=", a);
}
