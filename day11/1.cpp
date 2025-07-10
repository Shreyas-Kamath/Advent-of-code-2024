#include <fstream>
#include <unordered_map>
#include <ranges>

void sim(std::unordered_map<long long, long long>& stones, const int& blinks) {
    std::unordered_map<long long, long long> next;

    for (int i{}; i < blinks; ++i) {
        for (const auto& [stone, freq]: stones) {
            if (stone == 0) { next[1] += freq; continue; }

            std::string stone_str = std::to_string(stone);

            auto len = stone_str.length();
            if (len % 2 == 0) {
                std::string first = stone_str.substr(0, len / 2);
                std::string second = stone_str.substr(len / 2);

                next[std::stoull(first)] += freq;
                next[std::stoull(second)] += freq;
            }

            else next[stone * 2024] += freq;
        }
        stones = std::move(next);
    }
}

int main() {
    std::unordered_map<long long, long long> stones;

    std::string line; std::ifstream in("data.txt");

    std::getline(in, line);

    for (const auto& token: line | std::views::split(' ')) {
        ++stones[std::stoull(std::string(token.begin(), token.end()))];
    }

    const int blinks{ 25 };

    sim(stones, blinks);

    long long ans{};

    for (const auto& [stone, freq]: stones) ans += freq;

    printf("%lld", ans);
}