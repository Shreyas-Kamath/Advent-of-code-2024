#include <iostream>
#include <regex>
#include <string>
#include <fstream>

int main(){

    std::ifstream file("data.txt");
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");

    std::sregex_iterator begin(content.begin(), content.end(), pattern);
    std::sregex_iterator end;

    long long int sum{};
    bool enable_multiplication = true;

    for (auto it = begin; it != end; ++it) {
        std::smatch match = *it;

        if (match.str(0) == "do()") {
            enable_multiplication = true;
        } 
        
        else if (match.str(0) == "don't()") {
            enable_multiplication = false;
        } 
        
        else if (enable_multiplication) {
            sum += std::stoi(match.str(1)) * std::stoi(match.str(2));
        }
    }
    std::cout << sum;
    return 0;
}