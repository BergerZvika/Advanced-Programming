#include "vec3.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cmath>

namespace Stats {

double mean(const std::vector<double>& v) {
    if (v.empty()) throw std::invalid_argument("empty vector");
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double variance(const std::vector<double>& v) {
    double m = mean(v);
    double sq = 0.0;
    for (double x : v) sq += (x - m) * (x - m);
    return sq / v.size();
}

double stddev(const std::vector<double>& v) {
    return std::sqrt(variance(v));
}

double median(std::vector<double> v) {
    if (v.empty()) throw std::invalid_argument("empty vector");
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    return (n % 2 == 0) ? (v[n/2-1] + v[n/2]) / 2.0 : v[n/2];
}

double correlation(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size()) throw std::invalid_argument("vectors must have equal length");
    if (x.empty()) throw std::invalid_argument("empty vector");
    double mx = mean(x), my = mean(y);
    double num = 0.0, dx2 = 0.0, dy2 = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        double a = x[i] - mx, b = y[i] - my;
        num  += a * b;
        dx2  += a * a;
        dy2  += b * b;
    }
    double denom = std::sqrt(dx2 * dy2);
    if (denom == 0.0) throw std::domain_error("zero variance — correlation undefined");
    return num / denom;
}

} // namespace Stats
