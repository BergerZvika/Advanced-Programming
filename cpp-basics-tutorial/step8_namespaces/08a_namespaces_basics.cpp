// Concept: namespaces group related names and prevent collisions.
//
// vs C:
//   C has only ONE global namespace, so libraries prefix everything to avoid
//   collisions: 'gtk_widget_show', 'png_create_read_struct', etc.
//   In C++ you put related names inside a namespace and address them with
//   'name::' — the same name in two different namespaces is no conflict.
#include <iostream>

namespace math {
    constexpr double pi = 3.14159265;
    double square(double x) { return x * x; }
}

namespace physics {
    constexpr double pi = 3.14;            // a coarser approximation
    double force(double m, double a) { return m * a; }
}

int main() {
    std::cout << "math::pi    = " << math::pi    << "\n";
    std::cout << "physics::pi = " << physics::pi << "  (coarser approximation)\n";
    std::cout << "math::square(5)        = " << math::square(5)      << "\n";
    std::cout << "physics::force(2, 9.8) = " << physics::force(2,9.8)<< "\n";
    // The standard library lives in namespace 'std' — that is why std::cout, etc.
}
