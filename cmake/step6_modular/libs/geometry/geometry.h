#pragma once
#include <cmath>

struct Point     { double x, y; };
struct Circle    { Point center; double radius; };
struct Rectangle { Point top_left; double w, h; };

namespace Geo {
    double distance(Point a, Point b);
    double circle_area(const Circle& c);
    double rect_area(const Rectangle& r);
    bool   point_in_circle(Point p, const Circle& c);
}
