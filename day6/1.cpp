#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <fstream>
#include <algorithm>

int main() {
    std::string line;
    std::ifstream input("data.txt");

    std::vector<std::vector<char>> grid;
    grid.reserve(130);

    while (std::getline(input, line)) {
        std::vector<char> row;
        row.reserve(130);
        for (char& c : line) {
            row.push_back(c);
        }
        grid.emplace_back(std::move(row));
    }

    const std::vector<std::pair<int, int>> directions = {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0}
    };

    std::unordered_set<std::string> visited;

    int r{43}, c{79};  
    int facing{3}; 

    visited.insert(std::to_string(r) + "," + std::to_string(c));

    while (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size()) {
        auto [dr, dc] = directions[facing];
        int nr = r + dr; 
        int nc = c + dc;

        if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size()) break;

        if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[0].size() && grid[nr][nc] != '#') {
            r = nr;
            c = nc;
            visited.insert(std::to_string(r) + "," + std::to_string(c));
        } else {
            facing = (facing + 1) % 4;
        }
    }

    std::cout << visited.size() << std::endl;

    return 0;
}
