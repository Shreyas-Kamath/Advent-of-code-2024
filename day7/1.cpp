#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdint>

using u64 = uint64_t;

std::vector<std::vector<char>> generate_operator_combinations(int ops) {
    std::vector<std::vector<char>> all_combos;

    for (int mask = 0; mask < (1 << ops); ++mask) {
        std::vector<char> combo;
        
        for (int i = 0; i < ops; ++i) {
            combo.push_back((mask >> i) & 1 ? '*' : '+'); 
        }
  
        all_combos.push_back(std::move(combo));
    }

    return all_combos;
}

int main() {
    std::ifstream in("data.txt");

    std::string line; std::string temp, target_str; u64 final_sum{};

    while (std::getline(in, line))
    {
        std::vector<u64> nums;

        std::stringstream ss(line); u64 target{};

        ss >> target_str;
        target_str.pop_back();

        target = std::stoull(target_str);
        
        while (ss >> temp) { nums.emplace_back(std::stoull(temp)); }

        int ops = nums.size() - 1;

        auto all_combos = generate_operator_combinations(ops);

        bool found = false;

        for (const auto& combo: all_combos) {
            if (found) break;
            u64 value = nums[0];
            for (int i = 0; i < ops; ++i) {
                if (combo[i] == '+') {
                    value += nums[i + 1];
                } else {
                    value *= nums[i + 1];
                }
            }
            if (value == target) {
                final_sum += target;
                found = true;
                break;  
            }
        }

    }
    std::printf("Final sum: %llu\n", final_sum);
    return 0;
}