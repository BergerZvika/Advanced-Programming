// Concept: friend function — a free function granted access to a class's
// private/protected members. The friendship is declared INSIDE the class.
#include <iostream>

class Vector2D {
public:
    Vector2D(double x, double y) : x_(x), y_(y) {}

    // Free function gets private access — declared as a friend.
    friend double dot(const Vector2D& a, const Vector2D& b);

private:
    double x_, y_;
};

// Definition is OUTSIDE the class — it is NOT a member function.
// But because of the friend declaration, it may read private fields directly.
double dot(const Vector2D& a, const Vector2D& b) {
    return a.x_ * b.x_ + a.y_ * b.y_;
}

int main() {
    Vector2D a(3, 0), b(0, 4);
    std::cout << "dot(a, b) = " << dot(a, b) << "  (read private x_/y_ directly)\n";
}
