// Concept: arithmetic operators — binary +, -, *, /.
//
// Two ways to overload an arithmetic operator:
//   - As a NON-MEMBER (free) function       T operator+(const T&, const T&);
//   - As a MEMBER function                  T T::operator+(const T&) const;
//
// Prefer NON-MEMBER for binary operators where both sides should symmetrically
// participate in implicit conversions (e.g. 2 + v works as well as v + 2).
//
// Conventions:
//   - take operands by const reference
//   - return BY VALUE (a fresh result)
//   - mark as 'const' if a member
//
// We use the well-known idiom of implementing '+' in terms of '+=' (next file)
// to avoid duplicating logic.
#include <iostream>

class Vec2 {
public:
    Vec2(double x, double y) : x_(x), y_(y) {}

    Vec2& operator+=(const Vec2& r) { x_ += r.x_; y_ += r.y_; return *this; }
    Vec2& operator-=(const Vec2& r) { x_ -= r.x_; y_ -= r.y_; return *this; }
    Vec2& operator*=(double k)      { x_ *= k;    y_ *= k;    return *this; }

    double x() const { return x_; }
    double y() const { return y_; }
private:
    double x_, y_;
};

// Non-member binary operators implemented in terms of the compound forms.
// Note: take 'lhs' by VALUE so we already have a local copy to mutate.
Vec2 operator+(Vec2 lhs, const Vec2& rhs) { lhs += rhs; return lhs; }
Vec2 operator-(Vec2 lhs, const Vec2& rhs) { lhs -= rhs; return lhs; }

// Allow both 'v * 2' and '2 * v' by providing two non-member overloads.
Vec2 operator*(Vec2 lhs, double k)        { lhs *= k; return lhs; }
Vec2 operator*(double k, Vec2 rhs)        { rhs *= k; return rhs; }

void show(const char* tag, const Vec2& v) {
    std::cout << "  " << tag << " = (" << v.x() << ", " << v.y() << ")\n";
}

int main() {
    Vec2 a(3, 4), b(1, 2);
    show("a", a);
    show("b", b);
    show("a + b   ", a + b);
    show("a - b   ", a - b);
    show("a * 2   ", a * 2);
    show("3 * b   ", 3 * b);     // works because of the symmetric overload
    show("a + b - b", a + b - b);  // chained — operator+/- compose left-to-right
}
