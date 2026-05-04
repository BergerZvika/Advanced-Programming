// Pitfall 5: virtual calls from a constructor (or destructor) do NOT dispatch
// to the derived override. The derived part isn't (or no longer is) valid at
// that point, so the BASE version runs.
#include <iostream>
#include <string>

class Parent {
public:
    Parent() {
        std::cout << "  Parent ctor — calling virtual greet()\n";
        greet();           // dispatches to Parent::greet
    }
    virtual ~Parent() = default;
    virtual void greet() const { std::cout << "  Parent::greet\n"; }
};

class Child : public Parent {
public:
    Child() : data_("child_data") {
        std::cout << "  Child ctor — now calling greet()\n";
        greet();           // dispatches to Child::greet (data_ is now valid)
    }
    void greet() const override {
        std::cout << "  Child::greet (data=" << data_ << ")\n";
    }
private:
    std::string data_;
};

int main() {
    Child c;
    std::cout << "── after construction ──\n";
    c.greet();
    std::cout << "Rule: never call virtual functions from a constructor or destructor.\n";
}
