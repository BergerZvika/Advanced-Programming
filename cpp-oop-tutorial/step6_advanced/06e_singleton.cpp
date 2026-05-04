// Concept: singleton pattern — exactly one instance, accessed via instance().
// Uses a static local (Meyers' singleton) — thread-safe initialisation in C++11+.
#include <iostream>
#include <map>
#include <string>

class AppConfig {
public:
    // Disallow copy and move so callers cannot duplicate the singleton.
    AppConfig(const AppConfig&)            = delete;
    AppConfig& operator=(const AppConfig&) = delete;

    static AppConfig& instance() {
        static AppConfig the_one;     // constructed on first call
        return the_one;
    }

    void set(const std::string& k, const std::string& v) { data_[k] = v; }
    void show() const {
        std::cout << "  AppConfig:\n";
        for (auto& [k, v] : data_) std::cout << "    " << k << " = " << v << "\n";
    }

private:
    AppConfig() { std::cout << "  AppConfig constructed\n"; }
    std::map<std::string, std::string> data_;
};

int main() {
    AppConfig& a = AppConfig::instance();
    AppConfig& b = AppConfig::instance();

    a.set("theme", "dark");
    a.set("language", "en");

    std::cout << "&a == &b? " << (&a == &b ? "YES — same instance" : "NO") << "\n";
    b.show();    // sees what a set
}
