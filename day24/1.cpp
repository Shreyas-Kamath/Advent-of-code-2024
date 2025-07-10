#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <ranges>
#include <algorithm>

struct Instruction {
    std::string lhs, op, rhs, result;
};

int main() {
    std::string line; std::ifstream in("regs.txt");

    std::unordered_map<std::string, int> registers;

    while (std::getline(in, line))
    {
        std::string reg, val;

        auto pos = line.find(' ');

        reg = line.substr(0, pos);
        reg.pop_back();

        val = line.substr(pos + 1);

        registers[reg] = std::stoi(val);
    }
    in.close();

    std::queue<Instruction> q;

    std::ifstream in2("data.txt");

    while (std::getline(in2, line)) {
        std::istringstream iss(line);

        std::string lhs, op, rhs, arrow, result;

        iss >> lhs >> op >> rhs >> arrow >> result;

        q.emplace(lhs, op, rhs, result);
    }

    while (!q.empty()) {
        const auto front = q.front(); q.pop();

        if (registers.contains(front.lhs) && registers.contains(front.rhs)) {
            if (front.op == "AND") registers[front.result] = registers[front.lhs] & registers[front.rhs];
            else if (front.op == "OR") registers[front.result] = registers[front.lhs] | registers[front.rhs];
            else registers[front.result] = registers[front.lhs] ^ registers[front.rhs];
        }

        else q.push(front);
    }
    
    auto vec = registers
    | std::views::filter([](const auto& pair) { return pair.first.starts_with('z'); })
    | std::ranges::to<std::vector<std::pair<std::string, int>>>();

    std::ranges::sort(vec, [](const auto& lhs, const auto& rhs) {
        return lhs.first > rhs.first;
    });

    auto ans = vec
    | std::views::transform([](const auto& pair) { return std::to_string(pair.second); })
    | std::views::join
    | std::ranges::to<std::string>();

    printf("%lld", std::stoll(ans, nullptr, 2));
}