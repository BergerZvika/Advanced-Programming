// Concept: std::function<R(Args...)> — a TYPE-ERASED callable holder.
//
// Stores any callable that matches the signature: a free function, a
// functor instance, a member-function binding, a lambda. You can then
// pass it around or store it in a container, regardless of its actual type.
//
//   pros: uniform type for "anything callable with this signature"
//   cons: small heap allocation + indirection — slower than a template
//         that is parameterised on the callable type directly
#include <functional>
#include <iostream>
#include <vector>

int free_add(int a, int b) { return a + b; }

struct Mul { int operator()(int a, int b) const { return a * b; } };

int main() {
    using BinOp = std::function<int(int, int)>;

    std::vector<BinOp> ops;
    ops.push_back(&free_add);                        // free function
    ops.push_back(Mul{});                            // functor object
    ops.push_back([](int a, int b){ return a - b; }); // lambda
    ops.push_back([factor=10](int a, int b){
        return (a + b) * factor;                     // capturing lambda
    });

    for (const auto& op : ops) {
        std::cout << "  op(3, 4) = " << op(3, 4) << "\n";
    }

    // Empty std::function is callable-checked — operator bool tells you if it's set:
    std::function<int(int,int)> empty;
    std::cout << "empty has target? " << static_cast<bool>(empty) << "\n";
    // empty(1,2);   // ← throws std::bad_function_call at runtime
}
