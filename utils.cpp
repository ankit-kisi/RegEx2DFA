#include "utils.h"
#include <stack>
#include <cctype>

int precedence(char op) {
    if (op == '+') return 1;
    if (op == '.') return 2; 
    if (op == '*') return 3;
    return 0;
}

std::string infixToPostfix(const std::string& exp) {
    std::stack<char> operators;
    std::string postfix;

    for (char ch : exp) {
        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        } else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}


//work is left here to recognize a*(a+b) => a*.(a+b)
std::string insertDots(const std::string& input) {
    if (input.empty()) {
        return input;
    }

    std::string result;
    result.reserve(input.size() * 2); // Reserve enough space to avoid frequent reallocations

    result += input[0];

    for (size_t i = 1; i < input.size(); ++i) {
        if ((isalnum(input[i]) && isalnum(input[i - 1])) || 
            (isalnum(input[i]) && input[i - 1] == ')') || 
            (isalnum(input[i - 1]) && input[i] == '(')) {
            result += '.';
        }
        result += input[i];
    }

    return result;
}
