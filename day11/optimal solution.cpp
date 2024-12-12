#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>


void one_blink(std::unordered_map<unsigned long long int, size_t>& stones) {

    std::unordered_map<unsigned long long int, size_t> changes;

    for (auto& pair : stones) {
        unsigned long long int stone = pair.first;
        size_t count = pair.second;

        if (count == 0) continue;

        if (stone == 0) {
            changes[1] += count;
            changes[stone] -= count;        // yes, there is an underflow
                                            // but it is self correcting because
                                            // we add the changes map back to stones at 
                                            // the end effectively nullifying underflow
        } 
        else if (std::to_string(stone).length() % 2 == 0) {
            std::string stone_str = std::to_string(stone);
            size_t mid = stone_str.length() / 2;

            std::string lhs = stone_str.substr(0, mid);
            std::string rhs = stone_str.substr(mid);

            changes[std::stoull(lhs)] += count;
            changes[std::stoull(rhs)] += count;
            changes[stone] -= count;
        } 
        else {
            changes[stone * 2024] += count;
            changes[stone] -= count;
        }
    }

    for (auto& change : changes) {
        stones[change.first] += change.second;
    }
}

int main(){
    std::ifstream in("data.txt");
    std::string line, num;
    
    std::getline(in, line); std::stringstream ss(line);
    std::unordered_map<long long unsigned int, size_t> stones;

    while (ss >> num){
        stones[std::stoull(num)]++;
    }
    // first is key, second is count

    int iterations{75};

    std::unordered_map<long long unsigned int, size_t> hold_stones;

    for (int i{}; i < iterations; ++i){
        one_blink(stones);
    }
    unsigned long long int sum{};
    for (auto& _: stones){
        sum += _.second;
    }

    std::cout << sum << '\n';

    return 0;
}