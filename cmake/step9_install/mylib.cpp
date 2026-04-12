#include "mylib.h"
#include <cctype>
#include <sstream>

namespace MyLib {
    std::string repeat(const std::string& s, int n) {
        std::string result;
        result.reserve(s.size() * n);
        for (int i = 0; i < n; i++) result += s;
        return result;
    }

    std::string join(const std::vector<std::string>& parts, const std::string& sep) {
        std::string result;
        for (size_t i = 0; i < parts.size(); i++) {
            if (i > 0) result += sep;
            result += parts[i];
        }
        return result;
    }

    bool starts_with(const std::string& s, const std::string& prefix) {
        return s.size() >= prefix.size() &&
               s.compare(0, prefix.size(), prefix) == 0;
    }

    std::string to_snake_case(const std::string& s) {
        std::string result;
        for (char c : s) {
            if (std::isupper(c) && !result.empty()) result += '_';
            result += (char)std::tolower(c);
        }
        return result;
    }
}
