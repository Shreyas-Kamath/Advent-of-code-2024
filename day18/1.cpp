#include <fstream>
#include <vector>
#include <string>
#include <queue>

int main() {
    std::vector<std::string> grid(71, std::string(71, '.'));

    std::string line; std::ifstream in("data.txt");
    const char* format = "%d,%d";

    for (int _{}; _ < 1024; ++_) {
        std::getline(in, line);
        int x, y;

        sscanf(line.c_str(), format, &x, &y);
        grid[y][x] = '#';
    }

    std::queue<std::tuple<int, int, int>> q;
    std::vector<std::vector<bool>> visited(71, std::vector<bool>(71, false));

    q.emplace(0, 0, 1);
    visited[0][0] = true;

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    while (!q.empty()) {
        const auto [x, y, cost] = q.front(); q.pop();

        for (int d{}; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            if (nx == 70 && ny == 70) { 
                printf("%d", cost); 
                return 0; 
            }

            if (nx < 0 || nx >= 71 || ny < 0 || ny >= 71) continue;
            if (grid[ny][nx] == '#' || visited[ny][nx]) continue;

            visited[ny][nx] = true;
            q.emplace(nx, ny, cost + 1);
        }
    }
}