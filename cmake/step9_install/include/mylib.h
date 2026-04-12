#pragma once
#include <string>
#include <vector>

namespace MyLib {
    std::string  repeat(const std::string& s, int n);
    std::string  join(const std::vector<std::string>& parts, const std::string& sep);
    bool         starts_with(const std::string& s, const std::string& prefix);
    std::string  to_snake_case(const std::string& camelCase);
}
