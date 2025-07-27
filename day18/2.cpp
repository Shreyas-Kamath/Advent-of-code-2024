#include <unordered_set>
#include <string>
#include <queue>
#include <fstream>
#include <string>
#include <optional>

using Point = std::pair<int, int>;

struct PointHash {
    size_t operator()(const Point& p) const {
        return ((uint64_t)p.first << 32) | (uint32_t)p.second;
    }
};

std::optional<Point> bfs(const Point& wall, std::unordered_set<Point, PointHash>& walls, std::unordered_set<Point, PointHash>& existing_path) {
    walls.insert(wall);

    if (!existing_path.empty() && !existing_path.contains(wall)) { return std::nullopt; }

    static const int dx[4] = {1, 0, 0, -1};
    static const int dy[4] = {0, 1, -1, 0};

    std::unordered_set<Point, PointHash> new_path;
    std::unordered_set<Point, PointHash> visited;
    std::queue<Point> queue;

    queue.emplace(0, 0);
    visited.emplace(0, 0);
    new_path.emplace(0, 0);

    while (!queue.empty()) {
        const auto [x, y] = queue.front(); queue.pop();

        for (int d{}; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx < 0 || nx >= 71 || ny < 0 || ny >= 71) continue;
            if (visited.contains({ nx, ny }) || walls.contains({ nx, ny })) continue;

            new_path.emplace(nx, ny);
            visited.emplace(nx, ny);
            queue.emplace(nx, ny);
        }
    }

    if (!visited.contains({ 70, 70 })) {
        existing_path = std::move(new_path);
        return wall;
    }

    return std::nullopt;
}

int main() {
    std::string line; std::ifstream in("data.txt");
    const char* format = "%d,%d";

    std::unordered_set<Point, PointHash> walls;
    std::unordered_set<Point, PointHash> path;

    while (std::getline(in, line))
    {
        int x, y;
        sscanf(line.c_str(), format, &x, &y);
        
        auto ans = bfs({x, y}, walls, path);
        if (ans.has_value()) {
            const auto& [x, y] = ans.value();
            printf("%d,%d", x, y);
            return 0;
        }
    }
    
}