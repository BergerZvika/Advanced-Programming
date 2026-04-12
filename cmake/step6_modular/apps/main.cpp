#include <iostream>
#include <string>
#include "geometry.h"
#include "io.h"

int main() {
    std::cout << "=== Step 6: Modular Project with Subdirectories ===\n\n";

    Circle    c  = {{0.0, 0.0}, 5.0};
    Rectangle r  = {{0.0, 0.0}, 8.0, 3.0};
    Point     p1 = {3.0, 4.0};
    Point     p2 = {6.0, 6.0};

    IO::print_table({
        {"Circle radius",     std::to_string(c.radius)},
        {"Circle area",       std::to_string(Geo::circle_area(c))},
        {"Rect (8x3) area",   std::to_string(Geo::rect_area(r))},
        {"dist(p1, origin)",  std::to_string(Geo::distance(p1, {0,0}))},
        {"dist(p1, p2)",      std::to_string(Geo::distance(p1, p2))},
        {"p1 in circle?",     Geo::point_in_circle(p1, c) ? "YES" : "NO"},
        {"p2 in circle?",     Geo::point_in_circle(p2, c) ? "YES" : "NO"},
    });

    return 0;
}
