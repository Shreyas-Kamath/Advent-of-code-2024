#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

int main() {
    std::ifstream file("data.txt"); std::string line, num;

    std::vector<int> v1, v2;             // two vectors to hold numbers
    while (std::getline(file, line)){    // read a line
        std::stringstream ss(line);
        ss >> num;
        v1.push_back(stoi(num));
        ss >> num;
        v2.push_back(stoi(num));
    }
    
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    int sum{};
    for (int i{}; i < v1.size(); ++i) sum += abs(v1[i]-v2[i]);          // sum of absolute differences
    std::cout << sum;                                                   // both vectors are same size    
}