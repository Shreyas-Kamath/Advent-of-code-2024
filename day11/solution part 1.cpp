#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdint>

std::vector<uint64_t> update(std::vector<uint64_t>& stones){
     std::vector<uint64_t> updated_stones;
    for (uint64_t& stone: stones){
        if (stone == 0) updated_stones.push_back(1);
        else if (std::to_string(stone).length() %2 == 0){
            std::string stone_string = std::to_string(stone);
            int mid = stone_string.length()/2;

            uint64_t lhs = static_cast<uint64_t>(std::stoull(stone_string.substr(0, mid)));
            uint64_t rhs = static_cast<uint64_t>(std::stoull(stone_string.substr(mid)));

            updated_stones.push_back(lhs);
            updated_stones.push_back(rhs);
        }
        else updated_stones.push_back(stone * 2024);
    }
    return updated_stones;
}

int main() {
    std::ifstream file("data.txt"); std::string line, stone; std::vector<uint64_t> stones;
    std::getline(file, line); 
    file.close();

    std::stringstream ss(line);
    while (ss >> stone){
        stones.push_back(static_cast<uint64_t>(stoi(stone)));
    }

    for (int i{}; i < 25; ++i){
        stones = update(stones);
    }
    std::cout << stones.size();
    return 0;
}