#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <ranges>

int main() {
    std::string line, first, second; std::ifstream in("data.txt");

    std::vector<int> v1, v2; v1.reserve(1000); v2.reserve(1000);

    const char* format = "%d   %d";
    while (std::getline(in, line)) {
        int first, second;

        if (sscanf(line.c_str(), format, &first, &second) == 2) {
            v1.push_back(first);
            v2.push_back(second);
        }
    }

    std::ranges::sort(v1); std::ranges::sort(v2);

    int64_t ans{};
    for (const auto& [a, b]: std::views::zip(v1, v2)) {
        ans += std::abs(b - a); 
    }

    printf("%d", ans);
}