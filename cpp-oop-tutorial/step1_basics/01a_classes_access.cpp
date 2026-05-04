// Concept: class with public / private / protected access modifiers.
//   public    — accessible from anywhere
//   protected — accessible inside the class and its derived classes
//   private   — accessible only inside the class
#include <iostream>
#include <string>

class BankAccount {
public:
    BankAccount(const std::string& owner, double balance)
        : owner_(owner), balance_(balance) {}

    double get_balance() const { return balance_; }
    const std::string& owner() const { return owner_; }

private:
    std::string owner_;
    double      balance_;   // private — outside code cannot do account.balance_ = 9999
};

int main() {
    BankAccount acc("Alice", 1000.0);
    std::cout << "owner   = " << acc.owner()       << "\n";
    std::cout << "balance = " << acc.get_balance() << "\n";

    // acc.balance_ = 9999;  // ← compile error: 'balance_' is private
    std::cout << "(balance_ is private — direct assignment from outside would not compile)\n";
}
