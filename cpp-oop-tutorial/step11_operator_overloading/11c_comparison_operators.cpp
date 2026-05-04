// Concept: comparison operators — ==, !=, <, >, <=, >=.
//
// Conventions (pre-C++20):
//   - implement '==' and '<' (the "primitives")
//   - express the rest in terms of those
//   - prefer non-member symmetric forms; mark them 'const' if members
//
// C++20 added the SPACESHIP operator '<=>' which lets you write ONE function
// and the compiler synthesises ==, !=, <, <=, >, >=. (Brief mention; we stick
// to C++17-compatible code here.)
#include <iostream>
#include <string>

class Version {
public:
    Version(int major, int minor, int patch)
        : a_(major), b_(minor), c_(patch) {}

    // Primitives
    friend bool operator==(const Version& l, const Version& r) {
        return l.a_ == r.a_ && l.b_ == r.b_ && l.c_ == r.c_;
    }
    friend bool operator<(const Version& l, const Version& r) {
        if (l.a_ != r.a_) return l.a_ < r.a_;
        if (l.b_ != r.b_) return l.b_ < r.b_;
        return l.c_ < r.c_;
    }

    // Derived — implement once in terms of the primitives.
    friend bool operator!=(const Version& l, const Version& r) { return !(l == r); }
    friend bool operator>(const Version& l, const Version& r)  { return r < l;     }
    friend bool operator<=(const Version& l, const Version& r) { return !(r < l);  }
    friend bool operator>=(const Version& l, const Version& r) { return !(l < r);  }

    std::string str() const {
        return std::to_string(a_) + "." + std::to_string(b_) + "." + std::to_string(c_);
    }

private:
    int a_, b_, c_;
};

int main() {
    Version v1(1, 2, 3), v2(1, 2, 3), v3(1, 3, 0);

    std::cout << v1.str() << " == " << v2.str() << " ? " << (v1 == v2) << "\n";
    std::cout << v1.str() << " == " << v3.str() << " ? " << (v1 == v3) << "\n";
    std::cout << v1.str() << " <  " << v3.str() << " ? " << (v1 <  v3) << "\n";
    std::cout << v3.str() << " >= " << v1.str() << " ? " << (v3 >= v1) << "\n";

    // Now any STL algorithm or container that needs <, == works:
    //   std::sort(versions...)            uses <
    //   std::set<Version>                 uses <
    //   std::find(... , v1)               uses ==
}
