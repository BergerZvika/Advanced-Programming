#pragma once
#include <cmath>
#include <string>
#include <vector>
#include <stdexcept>

// ─── 3-D vector ──────────────────────────────────────────────────────────────
struct Vec3 {
    double x, y, z;

    Vec3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& o) const { return {x+o.x, y+o.y, z+o.z}; }
    Vec3 operator-(const Vec3& o) const { return {x-o.x, y-o.y, z-o.z}; }
    Vec3 operator*(double s)      const { return {x*s,   y*s,   z*s};   }

    bool operator==(const Vec3& o) const { return x==o.x && y==o.y && z==o.z; }

    double dot(const Vec3& o) const {
        return x*o.x + y*o.y + z*o.z;
    }

    Vec3 cross(const Vec3& o) const {
        return { y*o.z - z*o.y,
                 z*o.x - x*o.z,
                 x*o.y - y*o.x };
    }

    double norm() const { return std::sqrt(x*x + y*y + z*z); }

    Vec3 normalize() const {
        double n = norm();
        if (n == 0.0) throw std::domain_error("cannot normalize zero vector");
        return {x/n, y/n, z/n};
    }

    double angle_to(const Vec3& o) const {
        double denom = norm() * o.norm();
        if (denom == 0.0) throw std::domain_error("zero vector has no angle");
        double cosval = dot(o) / denom;
        // clamp to [-1, 1] to guard against floating-point drift
        cosval = std::max(-1.0, std::min(1.0, cosval));
        return std::acos(cosval);  // radians
    }

    std::string to_string() const {
        return "Vec3(" + std::to_string(x) + ", "
                       + std::to_string(y) + ", "
                       + std::to_string(z) + ")";
    }
};

// ─── Statistics ───────────────────────────────────────────────────────────────
namespace Stats {
    double mean(const std::vector<double>& v);
    double variance(const std::vector<double>& v);   // population variance
    double stddev(const std::vector<double>& v);
    double median(std::vector<double> v);             // by-value: sorts copy
    double correlation(const std::vector<double>& x,
                       const std::vector<double>& y); // Pearson r
}
