#include <iostream>
#include <string>
#include <sstream>

int main() {
    std::string line;
    long long total = 0;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        int num;
        while (iss >> num) {
            total += num;
        }
    }

    std::cout << total << std::endl;
    return 0;
}