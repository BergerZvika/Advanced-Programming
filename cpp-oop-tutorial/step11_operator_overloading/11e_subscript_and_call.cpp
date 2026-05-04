// Concept: operator[] and operator().
//
// operator[] — element access. Provide TWO overloads:
//   T&        operator[](size_t i);          // for non-const objects (writable)
//   const T&  operator[](size_t i) const;    // for const objects (read-only)
//
// operator() — function-call syntax on an object (a "callable" / functor).
// Same idea you saw in cpp-stl-tutorial/step14_functors. You may overload it
// with any number of parameter lists.
#include <iostream>
#include <vector>

class Grid {
public:
    Grid(int w, int h) : w_(w), h_(h), data_(w * h, 0) {}

    // Non-const subscript — caller may write
    int& operator[](int i)             { return data_[i]; }
    // Const subscript — read-only view
    const int& operator[](int i) const { return data_[i]; }

    // 2D access via operator() — multiple parameter lists let you do this naturally
    int&       operator()(int x, int y)       { return data_[y * w_ + x]; }
    const int& operator()(int x, int y) const { return data_[y * w_ + x]; }

    int width()  const { return w_; }
    int height() const { return h_; }

private:
    int w_, h_;
    std::vector<int> data_;
};

void readonly_dump(const Grid& g) {
    // const Grid& only lets us call the const overloads of [] and ()
    std::cout << "  read-only g(1,1) = " << g(1, 1) << "\n";
    std::cout << "  read-only g[0]   = " << g[0]    << "\n";
}

int main() {
    Grid g(3, 3);

    // Mutating writes — non-const overloads selected
    g[0]      = 10;
    g(1, 1)   = 99;
    g(2, 2)   = 7;

    std::cout << "  g[0]    = " << g[0]    << "\n";
    std::cout << "  g(1,1)  = " << g(1,1)  << "\n";

    readonly_dump(g);
}
