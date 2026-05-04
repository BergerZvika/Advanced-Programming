// Concept: operator<< and operator>> — connect your type to std::cout/cin.
//
// MUST be free functions (not members) — the LEFT operand is std::ostream/
// std::istream which you don't own. Often need 'friend' access to read or
// write private members.
//
//   std::ostream& operator<<(std::ostream& os, const T& v);
//   std::istream& operator>>(std::istream& is,       T& v);   // mutates v
//
// Always return the stream BY REFERENCE so insertions/extractions can chain:
//   std::cout << a << b << c;
#include <iostream>
#include <sstream>
#include <string>

class Date {
public:
    Date() = default;
    Date(int y, int m, int d) : y_(y), m_(m), d_(d) {}

    friend std::ostream& operator<<(std::ostream& os, const Date& v) {
        return os << v.y_ << "-" << (v.m_ < 10 ? "0" : "") << v.m_
                  << "-" << (v.d_ < 10 ? "0" : "") << v.d_;
    }
    friend std::istream& operator>>(std::istream& is, Date& v) {
        char dash1, dash2;
        is >> v.y_ >> dash1 >> v.m_ >> dash2 >> v.d_;
        if (dash1 != '-' || dash2 != '-') is.setstate(std::ios::failbit);
        return is;
    }

private:
    int y_ = 0, m_ = 0, d_ = 0;
};

int main() {
    Date d(2024, 7, 14);
    std::cout << "  cout << d → " << d << "\n";

    // operator>> from a string — useful for parsing config / files / CSV
    std::istringstream in("2025-01-09");
    Date parsed;
    in >> parsed;
    std::cout << "  parsed    → " << parsed << "\n";

    // Chained insertions — each returns the stream
    std::cout << "  chain     → " << d << " | " << parsed << "\n";
}
