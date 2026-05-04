// Concept: const member function + the 'this' pointer.
//   const after the parameter list  → method promises not to modify the object
//   'this' is a pointer to the current object; *this can be returned for chaining
#include <iostream>
#include <string>

class Builder {
public:
    Builder& set_name(const std::string& s) { name_  = s; return *this; }
    Builder& set_size(int n)                { size_  = n; return *this; }
    Builder& set_color(const std::string& c){ color_ = c; return *this; }

    // const method — cannot modify member variables; safe on const objects.
    void show() const {
        std::cout << "  Builder{" << name_ << ", " << size_ << ", " << color_ << "}\n";
    }

private:
    std::string name_;
    int         size_  = 0;
    std::string color_;
};

int main() {
    Builder b;
    // method chaining — each setter returns *this, so calls flow left → right
    b.set_name("widget").set_size(42).set_color("blue").show();

    const Builder cb;
    cb.show();   // OK — show() is const
    // cb.set_name("x");  // ← compile error: setters are non-const
}
