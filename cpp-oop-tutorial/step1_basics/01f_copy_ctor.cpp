// Concept: copy constructor — builds a new object as a copy of an existing one.
// Signature: ClassName(const ClassName& other);
#include <iostream>
#include <string>

class Account {
public:
    Account(const std::string& owner, double balance)
        : owner_(owner), balance_(balance)
    {
        std::cout << "  ctor       → " << owner_ << " $" << balance_ << "\n";
    }

    // Copy constructor — note the const reference parameter.
    Account(const Account& other)
        : owner_(other.owner_ + " (copy)"), balance_(other.balance_)
    {
        std::cout << "  copy ctor  → cloned to " << owner_ << "\n";
    }

    void show() const {
        std::cout << "  Account[" << owner_ << "] $" << balance_ << "\n";
    }

private:
    std::string owner_;
    double      balance_;
};

int main() {
    Account a("Alice", 1000.0);
    Account b = a;       // copy ctor (NOT operator=) — same as Account b(a);
    Account c(a);        // explicit copy
    a.show(); b.show(); c.show();
}
