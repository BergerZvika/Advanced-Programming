// Concept: a STATEFUL functor — data members persist across calls.
//
// Useful when you need an algorithm to remember something between elements:
// a running sum, a counter, a "have I seen this before?" flag.
//
// vs C: with a function pointer you'd need a global variable or thread-local
// state. A functor instance is the per-call state, cleanly scoped.
#include <algorithm>
#include <iostream>
#include <vector>

class Multiplier {
public:
    explicit Multiplier(int factor) : factor_(factor), calls_(0) {}

    int operator()(int x) {
        ++calls_;
        return x * factor_;
    }

    int calls() const { return calls_; }

private:
    int factor_;
    int calls_;     // mutable state across calls
};

int main() {
    std::vector<int> in{1, 2, 3, 4, 5};
    std::vector<int> out(in.size());

    Multiplier times3(3);
    std::transform(in.begin(), in.end(), out.begin(), std::ref(times3));
    // ↑ std::ref to keep ONE shared instance — by default std::transform
    //   would COPY the functor and we'd lose the call count.

    std::cout << "out:";
    for (int x : out) std::cout << " " << x;
    std::cout << "\n";
    std::cout << "operator() was invoked " << times3.calls() << " times\n";
}
