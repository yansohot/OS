#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        int num;
        bool first = true;
        while (iss >> num) {
            if (!first) std::cout << " ";
            std::cout << num * num * num;
            first = false;
        }
        std::cout << std::endl;
    }
    return 0;
}