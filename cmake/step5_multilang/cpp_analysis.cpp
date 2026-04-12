#include "cpp_analysis.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>

double Stats::mean(const std::vector<double>& v) {
    if (v.empty()) throw std::invalid_argument("empty vector");
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double Stats::stddev(const std::vector<double>& v) {
    double m = mean(v);
    double sq = 0.0;
    for (double x : v) sq += (x - m) * (x - m);
    return std::sqrt(sq / v.size());
}

double Stats::median(std::vector<double> v) {
    if (v.empty()) throw std::invalid_argument("empty vector");
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    return (n % 2 == 0) ? (v[n/2 - 1] + v[n/2]) / 2.0 : v[n/2];
}
