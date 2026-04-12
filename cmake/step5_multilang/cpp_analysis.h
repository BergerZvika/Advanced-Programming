#pragma once
#include <vector>

struct Stats {
    static double mean(const std::vector<double>& v);
    static double stddev(const std::vector<double>& v);
    static double median(std::vector<double> v);   // by value: sorts internally
};
