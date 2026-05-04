// Concept: std::shared_ptr — shared ownership via reference counting.
//
//   Each copy increments a use-count; destruction decrements it; the pointee
//   is deleted when the count hits zero. Use std::make_shared<T>(args...).
//
// Trade-offs vs unique_ptr:
//   + Multiple owners; the resource lives as long as ANY owner exists.
//   - Atomic reference count is more expensive than nothing (unique_ptr).
//   - Cycles of shared_ptrs leak — break with weak_ptr (next file).
#include <iostream>
#include <memory>
#include <string>

struct Resource {
    Resource(std::string n) : name_(std::move(n)) {
        std::cout << "  Resource ctor " << name_ << "\n";
    }
    ~Resource() { std::cout << "  Resource dtor " << name_ << "\n"; }
    std::string name_;
};

int main() {
    auto a = std::make_shared<Resource>("conn");
    std::cout << "  use_count after make_shared: " << a.use_count() << "\n";
    {
        auto b = a;          // copy — both 'a' and 'b' own the resource
        auto c = a;
        std::cout << "  use_count with 3 owners:    " << a.use_count() << "\n";
    }   // b, c destroyed here → count back to 1
    std::cout << "  use_count after inner scope: " << a.use_count() << "\n";
}   // a destroyed here → count = 0 → Resource dtor runs
