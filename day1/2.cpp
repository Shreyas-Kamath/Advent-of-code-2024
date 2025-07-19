#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>

int main() {
    std::string line, first, second; std::ifstream in("data.txt");

    std::vector<int> v1, v2; v1.reserve(1000);
    std::unordered_map<int, int> freq;

    const char* format = "%d   %d";

    while (std::getline(in, line)) {
        int first, second;

        if (sscanf(line.c_str(), format, &first, &second) == 2) {
            v1.push_back(first);
            ++freq[second];
        }
    }

    int ans{};

    for (const auto& num: v1) {
        ans += num * freq[num];
    }

    printf("%d", ans);
}