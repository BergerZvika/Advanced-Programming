#include "io.h"
#include <iostream>
#include <iomanip>

namespace IO {
    void print_separator(char ch, int width) {
        std::cout << std::string(width, ch) << "\n";
    }

    void print_table(const std::vector<std::pair<std::string, std::string>>& rows) {
        print_separator('=');
        for (auto& [key, val] : rows)
            std::cout << "  " << std::left << std::setw(22) << key << val << "\n";
        print_separator('=');
    }
}
