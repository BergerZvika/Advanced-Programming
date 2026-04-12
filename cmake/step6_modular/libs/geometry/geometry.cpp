#include "geometry.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Geo {
    double distance(Point a, Point b) {
        return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
    }

    double circle_area(const Circle& c) {
        return M_PI * c.radius * c.radius;
    }

    double rect_area(const Rectangle& r) {
        return r.w * r.h;
    }

    bool point_in_circle(Point p, const Circle& c) {
        return distance(p, c.center) <= c.radius;
    }
}
