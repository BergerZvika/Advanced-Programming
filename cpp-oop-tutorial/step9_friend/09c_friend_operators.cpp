// Concept: a common use of friend — defining operators that need private
// access AND can't be member functions (e.g. operator<< on std::ostream).
#include <iostream>
#include <string>

class Account {
public:
    Account(std::string owner, double balance)
        : owner_(std::move(owner)), balance_(balance) {}

    friend std::ostream& operator<<(std::ostream& os, const Account& a);
    friend bool operator<(const Account& l, const Account& r);

private:
    std::string owner_;
    double      balance_;
};

std::ostream& operator<<(std::ostream& os, const Account& a) {
    return os << "Account[" << a.owner_ << "] $" << a.balance_;
}
bool operator<(const Account& l, const Account& r) { return l.balance_ < r.balance_; }

int main() {
    Account alice("Alice", 2000), bob("Bob", 2300);
    std::cout << alice << "\n" << bob << "\n";
    std::cout << "alice < bob? " << (alice < bob ? "yes" : "no") << "\n";
}
