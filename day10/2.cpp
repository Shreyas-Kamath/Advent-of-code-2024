#include <vector>
#include <fstream>
#include <string>
#include <queue>

int explore_all_paths(std::vector<std::vector<int>>& grid, const int& x, const int& y, const int& rows, const int& cols, std::vector<std::vector<int>>& cache) {
    static const int dx[4] = {1, 0, 0, -1};
    static const int dy[4] = {0, -1, 1, 0};

    if (grid[x][y] == 9) return 1;
    if (cache[x][y] != -1) return cache[x][y];

    int paths{};

    for (int d{}; d < 4; ++d) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == grid[x][y] + 1) {
            paths += explore_all_paths(grid, nx, ny, rows, cols, cache);
        }
    }
    return cache[x][y] = paths;
}

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
    int cols = grid[0].size();

    std::vector<std::vector<int>> cache(rows, std::vector<int>(cols, -1));

    int distinct_trails{};
    for (const auto& [x, y]: starting_points) {
        distinct_trails += explore_all_paths(grid, x, y, rows, cols, cache);
    }

    printf("%d", distinct_trails);
}