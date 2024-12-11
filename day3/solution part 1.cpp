#include <iostream>
#include <regex>
#include <string>
#include <fstream>

int main(){

    std::ifstream file("data.txt");
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    std::regex pattern(R"(mul\((\d+),(\d+)\))");

    std::sregex_iterator begin(content.begin(), content.end(), pattern);
    std::sregex_iterator end;

    long long int sum{};
    for (auto it = begin; it != end; ++it){
        std::smatch match = *it;
        int lhs = stoi(match[1].str());
        int rhs = stoi(match[2].str());
        sum += (lhs * rhs);
    }
    std::cout << sum;
    return 0;
}