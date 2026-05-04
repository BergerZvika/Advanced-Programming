// Concept: std::unique_ptr — exclusive ownership.
//
//   - Owns the pointee. When the unique_ptr is destroyed, it deletes it.
//   - NOT copyable. ONLY movable. Two unique_ptrs cannot share the resource.
//   - Use std::make_unique<T>(args...) — preferred over 'new'.
//
// vs C:
//   In C you'd manage a resource with malloc + a paired free. Forget once,
//   leak forever. unique_ptr is automatic ('RAII'): the destructor frees
//   the resource on every exit path — early return, exception, anything.
#include <iostream>
#include <memory>
#include <string>

class Connection {
public:
    Connection(std::string url) : url_(std::move(url)) {
        std::cout << "  open  " << url_ << "\n";
    }
    ~Connection() { std::cout << "  close " << url_ << "\n"; }
private:
    std::string url_;
};

int main() {
    {
        std::unique_ptr<Connection> p = std::make_unique<Connection>("db://main");
        // No 'delete' anywhere — ~Connection runs automatically at end of scope.
    }   // ← Connection closed here, even if an exception had been thrown above.

    // Move ownership, do not copy:
    auto q = std::make_unique<Connection>("db://aux");
    auto r = std::move(q);             // q is now empty, r owns the connection
    std::cout << "  q is " << (q ? "non-null" : "null (moved)") << "\n";
    std::cout << "  r is " << (r ? "non-null" : "null") << "\n";
}
