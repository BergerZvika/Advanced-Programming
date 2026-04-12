#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>

int main() {
    fmt::print("=== Step 7: FetchContent - External Dependencies ===\n\n");

    // nlohmann/json example
    nlohmann::json config = {
        {"project",  "CMake Tutorial"},
        {"version",  7},
        {"features", {"fetchcontent", "json", "fmt", "auto-download"}},
        {"settings", {
            {"debug",    false},
            {"parallel", 4}
        }}
    };

    fmt::print("JSON output:\n{}\n\n", config.dump(2));

    // fmt library example
    std::vector<int> numbers = {1, 4, 9, 16, 25, 36};
    fmt::print("Squares: {}\n", numbers);
    fmt::print("Pi is approximately {:.10f}\n", 3.14159265358979);

    // Parse JSON back
    auto parsed = nlohmann::json::parse(R"({"name":"Alice","score":95.5})");
    fmt::print("\nParsed: name={}, score={}\n",
               parsed["name"].get<std::string>(),
               parsed["score"].get<double>());

    return 0;
}
