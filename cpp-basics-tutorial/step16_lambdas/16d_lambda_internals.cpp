// Concept: a lambda is SUGAR for an anonymous functor class.
//
// The compiler turns
//   auto add = [factor](int x){ return x * factor; };
// into roughly
//   class __lambda {
//       int factor_;
//   public:
//       __lambda(int f) : factor_(f) {}
//       auto operator()(int x) const { return x * factor_; }
//   };
//   __lambda add{factor};
//
// Because each lambda has its OWN unique unnamed type, you usually store it
// in `auto`. To hold any compatible callable in a single variable, use
// std::function<R(Args...)> — but that pays a small heap cost.
#include <functional>
#include <iostream>

int main() {
    // Each lambda has a unique anonymous type — the compiler lets you see
    // them via decltype, but you cannot spell the type name.
    auto a = [](int x){ return x + 1; };
    auto b = [](int x){ return x + 1; };   // SAME body, but different TYPE.
    static_assert(!std::is_same_v<decltype(a), decltype(b)>,
                  "every lambda has a unique type");

    std::cout << "  a(10) = " << a(10) << "  b(10) = " << b(10) << "\n";

    // std::function erases the type so you can store ANY compatible callable:
    std::function<int(int)> any_callable = a;
    any_callable = b;                                // works
    any_callable = [](int x){ return x * x; };        // also works
    std::cout << "  via std::function:    " << any_callable(5) << "\n";

    // Captureless lambdas decay to a plain function pointer — useful for
    // legacy C APIs that take a function-pointer callback:
    int (*fp)(int) = [](int x){ return x + 100; };
    std::cout << "  via function pointer: " << fp(5) << "\n";

    // (A lambda WITH captures cannot decay to a function pointer — the closure
    // has state that a bare function pointer cannot represent.)
}
