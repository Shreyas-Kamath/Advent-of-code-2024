#include <fstream>
#include <iostream>
#include <string>

long long secret(long long& num) {
    num ^= num * 64;
    num %= 16777216;

    num ^= num / 32;
    num %= 16777216;

    num ^= num * 2048;
    num %= 16777216;

    return num;
}

int main() {
    std::string line; std::ifstream in("data.txt");

    long long ans{};

    while (std::getline(in, line)) {
        long long num = std::stoll(line);

        for (int i{}; i < 2000; ++i) num = secret(num);

        ans += num;
    }

    std::cout << ans;
}