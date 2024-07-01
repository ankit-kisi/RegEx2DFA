#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <cctype>

// Function to return precedence of operators
int precedence(char op) {
    if (op == '+') return 1;
    if (op == '.') return 2; 
    if (op == '*') return 3;
    return 0;
}

// Function to convert infix expression to postfix expression
std::string infixToPostfix(const std::string& exp) {
    std::stack<char> operators;
    std::string postfix;

    for (char ch : exp) {
        if (isalnum(ch)) {
            // If the character is an operand, add it to the postfix expression
            postfix += ch;
        } else if (ch == '(') {
            // If the character is '(', push it to the stack
            operators.push(ch);
        } else if (ch == ')') {
            // If the character is ')', pop and output from the stack until an '(' is encountered
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Remove '(' from stack
        } else {
            // An operator is encountered
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    // Pop all the operators from the stack
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

int main() {
    std::cout<<"Enter the expression: ";
    std::string infix;
    std::cin>>infix;
    std::string postfix = infixToPostfix(infix);
    std::cout << "Postfix Expression: " << postfix << std::endl;
    return 0;
}
