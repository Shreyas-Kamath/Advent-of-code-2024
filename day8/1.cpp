#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

struct Point {
    int x{}, y{};

    Point operator +(const Point& rhs) const {
        return { this->x + rhs.x, this->y + rhs.y };
    }

    Point operator -(const Point& rhs) const {
        return { this->x - rhs.x, this-> y - rhs.y };
    }

    bool operator ==(const Point& rhs) const {
        return this->x == rhs.x && this->y == rhs.y;
    }
};

namespace std {
    template <>
    struct hash<Point> {
        size_t operator ()(const Point& p) const noexcept {
            return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
        }
    };
}

int main() {
    std::unordered_set<Point> unique_antinodes;

    std::unordered_map<char, std::vector<Point>> antenna_coords;

    std::string line; std::ifstream in("data.txt"); int row{};

    while (std::getline(in, line)) {
        for (int col{}; col < line.length(); ++col) {
            if (line[col] != '.') antenna_coords[line[col]].emplace_back(row, col);
        }

        ++row;
    }

    int bounds_x = row, bounds_y = line.length();

    for (const auto& [name, coord_list]: antenna_coords) {
        for (int i{}; i < coord_list.size() - 1; ++i) {
            for (int j{ i + 1 }; j < coord_list.size(); ++j) {
                Point delta = coord_list[j] - coord_list[i];
                
                Point a1 = coord_list[i] - delta;
                Point a2 = coord_list[j] + delta;

                if (a1.x >= 0 && a1.x < bounds_x && a1.y >= 0 && a1.y < bounds_y) unique_antinodes.insert(a1);
                if (a2.x >= 0 && a2.x < bounds_x && a2.y >= 0 && a2.y < bounds_y) unique_antinodes.insert(a2);
            }
        }
    }

    printf("%zu", unique_antinodes.size());
}