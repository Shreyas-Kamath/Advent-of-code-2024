#include <fstream>
#include <string>
#include <array>

struct Robot {
    int p_x{}, p_y{}, v_x{}, v_y{};
};

int main() {
    std::string line; std::ifstream in("data.txt");
    std::array<Robot, 500> robots;

    int rows{ 103 }, cols{ 101 };
    int id{};
    const char* format = "p=%d,%d v=%d,%d";

    while (std::getline(in, line))
    {
        int px, py, vx, vy;

        if (sscanf(line.c_str(), format, &px, &py, &vx, &vy) == 4) robots[id++] = {px, py, vx, vy};
    }
      
    for (int i{}; i < 100; ++i) {
        for (auto& [px, py, vx, vy]: robots) {
            px = ((px + vx) % cols + cols) % cols;
            py = ((py + vy) % rows + rows) % rows;
        }
    }

    int first{}, second{}, third{}, fourth{};
    for (const auto& [px, py, vx, vy]: robots) {
        if (py < rows / 2 && px < cols / 2) ++first;
        else if (py < rows / 2 && px > cols / 2) ++second;
        else if (py > rows / 2 && px > cols / 2) ++third;
        else if (py > rows / 2 && px < cols / 2) ++fourth;
    }

    printf("%d", first * second * third * fourth);
}