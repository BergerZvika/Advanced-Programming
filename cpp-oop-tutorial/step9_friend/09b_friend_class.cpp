// Concept: friend class — every member of the friend class gets private
// access to the class declaring the friendship.
#include <iostream>

class Vector2D;     // forward declaration

class Matrix {
public:
    Matrix(double a, double b, double c, double d) : a_(a), b_(b), c_(c), d_(d) {}
    Vector2D rotate(const Vector2D& v) const;     // touches Vector2D's privates

private:
    double a_, b_, c_, d_;
};

class Vector2D {
public:
    Vector2D(double x, double y) : x_(x), y_(y) {}
    double x() const { return x_; }
    double y() const { return y_; }

    friend class Matrix;     // every Matrix method may touch Vector2D's privates

private:
    double x_, y_;
};

Vector2D Matrix::rotate(const Vector2D& v) const {
    return Vector2D(a_ * v.x_ + b_ * v.y_,        // direct private access
                    c_ * v.x_ + d_ * v.y_);
}

int main() {
    Vector2D v(1, 0);
    Matrix rot90(0, -1,
                 1,  0);
    Vector2D r = rot90.rotate(v);
    std::cout << "rotated (1,0) by 90° → (" << r.x() << ", " << r.y() << ")\n";
}
