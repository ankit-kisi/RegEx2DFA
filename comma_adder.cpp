#include <iostream>
#include <string>

std::string insertDots(const std::string& input) {
    if (input.empty()) {
        return input;
    }

    std::string result;
    result.reserve(input.size() * 2); // Reserve enough space to avoid frequent reallocations

    result += input[0];

    for (size_t i = 1; i < input.size(); ++i) {
        if (isalnum(input[i]) && isalnum(input[i - 1]) || (isalnum(input[i]) && input[i-1] == ')' ) ||(isalnum(input[i]) && input[i-1] == '*' ) || (input[i-1]!='+'&& input[i] == '(')) {
            result += '.';
        }
        result += input[i];
    }

    return result;
}

int main() {
    std::string input;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

    std::string output = insertDots(input);

    std::cout << "Result: " << output << std::endl;

    return 0;
}
