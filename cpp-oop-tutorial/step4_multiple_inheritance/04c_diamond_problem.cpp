// Concept: the diamond problem (without virtual inheritance).
//
//        Device
//        /    \
//   Printer  Scanner
//        \    /
//        AllInOne
//
// AllInOne ends up with TWO copies of Device — wasted memory AND ambiguous
// access. The fix is virtual inheritance (see step 5).
#include <iostream>

class Device {
public:
    Device()  { std::cout << "  Device ctor @ " << this << "\n"; }
    ~Device() { std::cout << "  Device dtor @ " << this << "\n"; }
    void powerOn() const { std::cout << "  Device@" << this << " on\n"; }
};

class Printer : public Device {};
class Scanner : public Device {};
class AllInOne : public Printer, public Scanner {};

int main() {
    AllInOne aio;     // TWO Device sub-objects — watch the addresses
    std::cout << "sizeof(Device)   = " << sizeof(Device)   << "\n";
    std::cout << "sizeof(AllInOne) = " << sizeof(AllInOne) << "  ← contains 2 Device sub-objects\n";

    // aio.powerOn();           // ← ambiguous (which Device?)
    aio.Printer::powerOn();
    aio.Scanner::powerOn();

    Device* via_p = static_cast<Printer*>(&aio);
    Device* via_s = static_cast<Scanner*>(&aio);
    std::cout << "Device via Printer @ " << via_p << "\n";
    std::cout << "Device via Scanner @ " << via_s << "\n";
    std::cout << "Same object? " << (via_p == via_s ? "YES" : "NO — TWO COPIES") << "\n";
}
