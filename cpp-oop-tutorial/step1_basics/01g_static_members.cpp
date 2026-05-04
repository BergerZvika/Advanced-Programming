// Concept: static data members — one shared variable across ALL instances.
// Lives in static storage (NOT inside any object). Must be defined at file scope.
#include <iostream>

class Counter {
public:
    Counter()  { ++count_; std::cout << "  ctor (live=" << count_ << ")\n"; }
    ~Counter() { --count_; std::cout << "  dtor (live=" << count_ << ")\n"; }

    // Static member function — no 'this' pointer; can only touch static data.
    static int live() { return count_; }

private:
    static int count_;     // declaration
};
int Counter::count_ = 0;   // definition — allocates the actual storage

int main() {
    std::cout << "live before: " << Counter::live() << "\n";
    {
        Counter a;
        Counter b;
        {
            Counter c;
            std::cout << "live inside inner scope: " << Counter::live() << "\n";
        }
        std::cout << "live after inner scope:  " << Counter::live() << "\n";
    }
    std::cout << "live after all scopes:    " << Counter::live() << "\n";
}
