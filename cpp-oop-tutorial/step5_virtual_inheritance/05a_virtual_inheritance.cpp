// Concept: virtual inheritance solves the diamond problem.
// Each "virtual" base appears EXACTLY ONCE in the most-derived object,
// no matter how many paths point to it.
#include <iostream>

class Device {
public:
    Device()  { std::cout << "  Device ctor @ " << this << "\n"; }
    ~Device() { std::cout << "  Device dtor @ " << this << "\n"; }
    void powerOn() const { std::cout << "  Device@" << this << " on\n"; }
};

class Printer : public virtual Device {};   // virtual!
class Scanner : public virtual Device {};   // virtual!
class AllInOne : public Printer, public Scanner {};

int main() {
    AllInOne aio;     // ONE Device — note the constructor only fires once
    aio.powerOn();    // no longer ambiguous

    Device* via_p = static_cast<Printer*>(&aio);
    Device* via_s = static_cast<Scanner*>(&aio);
    std::cout << "Device via Printer @ " << via_p << "\n";
    std::cout << "Device via Scanner @ " << via_s << "\n";
    std::cout << "Same object? " << (via_p == via_s ? "YES — ONE COPY" : "NO") << "\n";
}
