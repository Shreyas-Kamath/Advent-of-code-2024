#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::ifstream file("data.txt");
    std::string line, num;

    std::vector<int> v1, v2;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        ss >> num;
        v1.push_back(stoi(num));
        ss >> num;
        v2.push_back(stoi(num));
    }

    std::unordered_map<int, int> counts;  // use a hashmap for O(N) complexity
    for (int num : v2) {
        counts[num]++;
    }

    int sum = 0;
    for (int num : v1) {
        sum += num * counts[num];
    }

    std::cout << sum << std::endl;

    return 0;
}
