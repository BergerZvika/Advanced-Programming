// Concept: member initializer list — preferred over assignment in body.
// Required for const and reference members (they cannot be assigned later).
#include <iostream>
#include <string>

class Config {
public:
    // Initializer list runs BEFORE the body. const and reference members
    // MUST be initialised here — assigning to them in the body would be illegal.
    Config(const std::string& name, int& counter_ref)
        : name_(name),
          version_(1),       // const int — only the init list works
          counter_(counter_ref)   // int& — must bind here, can't reseat later
    {
        std::cout << "  Config '" << name_ << "' v" << version_ << " ready\n";
    }

    void show() const {
        std::cout << "  name=" << name_ << " version=" << version_
                  << " counter=" << counter_ << "\n";
    }

private:
    std::string name_;
    const int   version_;     // const member — set once, immutable
    int&        counter_;     // reference member — bound at construction
};

int main() {
    int hits = 7;
    Config cfg("prod", hits);
    cfg.show();
    hits = 42;            // changes via reference too
    cfg.show();
}
