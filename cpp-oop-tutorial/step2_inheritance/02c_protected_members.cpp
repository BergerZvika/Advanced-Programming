// Concept: protected members — accessible in the class AND in derived classes,
// but NOT from outside the hierarchy.
#include <iostream>
#include <string>

class Animal {
public:
    Animal(const std::string& name) : name_(name) {}
protected:
    std::string name_;     // derived classes can read/write this directly
};

class Dog : public Animal {
public:
    Dog(const std::string& name) : Animal(name) {}
    void rename(const std::string& new_name) {
        name_ = new_name;       // OK — protected access from derived class
        std::cout << "  Dog renamed to " << name_ << "\n";
    }
};

int main() {
    Dog d("Buddy");
    d.rename("Max");
    // d.name_ = "Rex";   // ← compile error: name_ is protected
    std::cout << "(d.name_ is protected — direct access from outside is illegal)\n";
}
