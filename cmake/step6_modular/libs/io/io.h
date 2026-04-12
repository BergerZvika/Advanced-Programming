#pragma once
#include <string>
#include <vector>
#include <utility>

namespace IO {
    void print_separator(char ch = '-', int width = 44);
    void print_table(const std::vector<std::pair<std::string, std::string>>& rows);
}
