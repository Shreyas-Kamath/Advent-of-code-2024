#include <regex>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int resolve_combo_op(int n, std::vector<int>& prog, std::vector<int>& registers) {
    if (n <= 3) return n;

    if (n == 4) return registers[0]; // Register A
    if (n == 5) return registers[1]; // Register B
    if (n == 6) return registers[2];

    return 0;
}

int main() {

    std::string line; std::ifstream in("data.txt");

    static const std::regex pattern(R"((Register [a-zA-Z]): (\d+))");

    std::vector<int> registers(3, 0); 

    while (std::getline(in, line)) {
        std::smatch match;

        if (std::regex_match(line, match, pattern)) {
            if (match[1].str() == "Register A") {
                registers[0] = std::stoi(match[2]);
            } else if (match[1].str() == "Register B") {
                registers[1] = std::stoi(match[2]);
            } else if (match[1].str() == "Register C") {
                registers[2] = std::stoi(match[2]);
            }
        }
    } in.close();

    std::ifstream in2("program.txt");
    std::getline(in2, line); 

    std::vector<int> program;

    std::istringstream ss(line); std::string temp;

    while (std::getline(ss, temp, ',')) program.emplace_back(std::stoi(temp));

    in2.close();

    int id{}; std::string ans{};

    while (id < program.size()) {
        switch (program[id])
        {
            case 0: {
                    registers[0] /= (1 << resolve_combo_op(program[id + 1], program, registers));
                    id += 2;
                    break;
                }
            case 1: {
                    registers[1] ^= program[id + 1];
                    id += 2;
                    break;
                }
            case 2: {
                    registers[1] = resolve_combo_op(program[id + 1], program, registers) % 8;
                    id += 2;
                    break;
                }
            case 3: {
                if (registers[0] == 0) { id += 2; break; }
                id = program[id + 1];
                break;
            }
            case 4: {
                registers[1] ^= registers[2];
                id += 2;
                break;
            }
            case 5: {
                int resolved_operand = resolve_combo_op(program[id + 1], program, registers);
                ans.append(std::to_string(resolved_operand % 8)).append(",");
                id += 2;
                break;
            }
            case 6: {
                registers[1] = registers[0] / (1 << resolve_combo_op(program[id + 1], program, registers));
                id += 2;
                break;
            }
            case 7: {
                registers[2] = registers[0] / (1 << resolve_combo_op(program[id + 1], program, registers));
                id += 2;
                break;
            }
            default:
                break;
        }
    }
    ans.pop_back();
    std::cout << ans;

}