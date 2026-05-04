// Concept: 'new'/'delete' vs C's 'malloc'/'free'.
//
//   malloc(n)        →  raw bytes, no constructor; returns void*.
//   free(p)          →  frees raw bytes, no destructor.
//   new T(args)      →  allocates AND calls T's constructor; returns T*.
//   delete p         →  calls T's destructor AND frees the storage.
//
// CRITICAL — the two systems do NOT interoperate:
//   - never free() a 'new'-d pointer
//   - never delete a 'malloc'-d pointer
//   - both are UB in C++.
#include <cstdlib>     // malloc / free
#include <cstring>
#include <iostream>
#include <string>

class Tag {
public:
    Tag(const std::string& n) : name_(n) { std::cout << "  Tag ctor " << name_ << "\n"; }
    ~Tag() { std::cout << "  Tag dtor " << name_ << "\n"; }
private:
    std::string name_;
};

int main() {
    // C-style: raw bytes, no constructor.
    int* m = static_cast<int*>(std::malloc(sizeof(int)));
    *m = 42;
    std::cout << "malloc'd int = " << *m << "\n";
    std::free(m);

    // C++-style: full type semantics — ctor runs at new, dtor runs at delete.
    Tag* t = new Tag("widget");
    delete t;             // ← calls ~Tag, then releases storage

    std::cout << "(if we'd called free(t) instead, ~Tag would NOT run → leak / UB)\n";
}
