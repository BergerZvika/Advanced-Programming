// Concept: friendship is NOT inherited. A friend of Base is NOT automatically
// a friend of Derived — the derived class must grant friendship explicitly.
#include <iostream>

class SecretBase {
public:
    SecretBase() : secret_(42) {}
    friend class Inspector;     // Inspector is friend of SecretBase only
private:
    int secret_;
};

class SecretDerived : public SecretBase {
public:
    SecretDerived() : derived_secret_(99) {}
private:
    int derived_secret_;        // Inspector is NOT a friend of SecretDerived
};

class Inspector {
public:
    void peek(const SecretBase& b) {
        std::cout << "  SecretBase::secret_ = " << b.secret_ << "\n";
    }
    void peek_derived(const SecretDerived& d) {
        // Inspector still sees the inherited Base part:
        std::cout << "  SecretBase part of SecretDerived, secret_ = " << d.secret_ << "\n";
        // ❌ d.derived_secret_  ← would not compile: friendship not inherited
    }
};

int main() {
    Inspector i;
    SecretBase    b;       i.peek(b);
    SecretDerived d;       i.peek_derived(d);
    std::cout << "(d.derived_secret_ is NOT visible to Inspector)\n";
}
