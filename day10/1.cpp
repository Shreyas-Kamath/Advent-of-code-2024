#include <vector>
#include <fstream>
#include <string>
#include <queue>

int main() {
    std::string line; std::ifstream in("data.txt"); int rows{};
    std::vector<std::pair<int, int>> starting_points;
    std::vector<std::vector<int>> grid;

    while (std::getline(in, line))
    {
        std::vector<int> row;

        for (int cols{}; cols < line.length(); ++cols) {
            if (line[cols] == '0') starting_points.emplace_back(rows, cols);
            row.emplace_back(line[cols] - '0');
        }
        ++rows;
        grid.emplace_back(std::move(row));
    }

    const int dx[4] = {1, 0, 0, -1};
    const int dy[4] = {0, -1, 1, 0};

    int trailheads{}, cols = grid[0].size();

    for (const auto& [sx, sy]: starting_points) {
        std::queue<std::tuple<int, int, int>> q;
        std::vector<std::vector<std::vector<bool>>> visited(rows, std::vector<std::vector<bool>>(cols, std::vector<bool>(10, false)));

        q.emplace(sx, sy, 0);
        visited[sx][sy][0] = true;

        int curr_trails{};

        while (!q.empty())
        {
            auto [x, y, prev_height] = q.front(); q.pop();
            if (prev_height == 9) { ++curr_trails; continue; }

            for (int d{}; d < 4; ++d) {
                int nx = x + dx[d];
                int ny = y + dy[d];

                if (nx < 0 || nx >= rows || ny < 0 || ny >= cols) continue;

                int curr_height = grid[nx][ny];
                if (visited[nx][ny][curr_height]) continue;

                if (curr_height - prev_height == 1) {
                    q.emplace(nx, ny, curr_height);
                    visited[nx][ny][curr_height] = true;
                }
            }
        }
        trailheads += curr_trails;
    }

    printf("%d", trailheads);
}