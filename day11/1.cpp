#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

int main() {
    std::ifstream in("data.txt"); std::string line;
    std::getline(in, line);

    std::string stone;

    std::unordered_map<long long, long long> stone_counts;
    std::istringstream iss(line);
    
    while (iss >> stone) ++stone_counts[std::stoll(stone)];

    for (int i = 0; i < 25; ++i) {
        std::unordered_map<long long, long long> new_stone_counts;

        for (const auto& [stone, count] : stone_counts) {
            if (stone == 0) {
                new_stone_counts[1] += count;
            } else { 
                std::string stone_str = std::to_string(stone);

                if (stone_str.size() % 2 == 0) {
                    std::string first = stone_str.substr(0, stone_str.size() / 2);
                    std::string second = stone_str.substr(stone_str.size() / 2);
                    new_stone_counts[std::stoll(first)] += count;
                    new_stone_counts[std::stoll(second)] += count;
                }
                    
                else {
                new_stone_counts[stone * 2024] += count;
                }
            }
        }
        stone_counts = std::move(new_stone_counts);
    }
    long long total = 0;
    for (const auto& [_, count] : stone_counts) total += count;

    std::cout << total;    
}
