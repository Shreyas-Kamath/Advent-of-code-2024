#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

bool is_increasing_or_decreasing(const std::vector<int>& levels){
    bool increasing = true; bool decreasing = true;
    for (size_t i{}; i < levels.size() - 1; ++i){
        if (levels[i] > levels[i + 1]) increasing = false;
        if (levels[i] < levels[i + 1]) decreasing = false;
    }
    return increasing || decreasing;
}

bool atleast_one_atmost_three(const std::vector<int>& levels){
    int i{}; size_t end{levels.size() - 1};
    
    for (i; i < end; ++i){
        if (abs(levels[i] - levels[i + 1]) > 3 || abs(levels[i] - levels[i + 1]) < 1) return false;
    }

    return true;
}

int main() {
    std::vector<std::vector<int>> reports;      //vector of vector of ints

    std::ifstream file("data.txt");
    std::string line, num;

    while (std::getline(file, line)){           // inner vector contains levels
        std::stringstream ss(line); std::vector<int> temp;

        while (ss >> num){
            temp.push_back(stoi(num));
        }
        
        reports.push_back(temp);
    }


    // ---- after reading data ----

    int safe{};

    for (const std::vector<int>& levels : reports){
        if (is_increasing_or_decreasing(levels) && atleast_one_atmost_three(levels)) safe++;
    }

    std::cout << safe;
}