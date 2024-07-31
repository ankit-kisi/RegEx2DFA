#include "regEx.h"

#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <stdexcept>

std::string regEx::inputFromTerminal() {
  std::cout << "Enter a regular expression: ";
  std::getline(std::cin, infix);

  return infix;
}

// Function to check if the string contains only allowed characters
bool isValidCharacter(char c) {
    return std::isalnum(c) || c == '+' || c == '*' || c == '(' || c == ')';
}

// Function to validate the regular expression string and check parentheses
void checkRegularExpression(const std::string& pattern) {
    std::stack<char> parenthesesStack;

    // Check if all characters are valid
    for (char c : pattern) {
        if (!isValidCharacter(c)) {
            throw std::invalid_argument("Invalid character in the regular expression");
        }

        // Parenthesis checking
        if (c == '(') {
            parenthesesStack.push(c);
        } else if (c == ')') {
            if (parenthesesStack.empty() || parenthesesStack.top() != '(') {
                throw std::invalid_argument("Unmatched parenthesis");
            }
            parenthesesStack.pop();
        }
    }

    // Ensure all opened parentheses are closed
    if (!parenthesesStack.empty()) {
        throw std::invalid_argument("Unmatched parenthesis");
    }
}


int regEx::precedence(char op) {
  if (op == '+') return 1;
  if (op == '.') return 2;
  if (op == '*') return 3;
  return 0;
}

std::string regEx::infixToPostfix(const std::string& exp) {
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
      while (!operators.empty() &&
             precedence(operators.top()) >= precedence(ch)) {
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

// work is left here to recognize a*(a+b) => a*.(a+b)
std::string regEx::insertDots(const std::string& input) {
  if (input.empty()) {
    return input;
  }

  std::string result;
  result.reserve(input.size() *
                 2);  // Reserve enough space to avoid frequent reallocations

  result += input[0];

  for (size_t i = 1; i < input.size(); ++i) {
    if (isalnum(input[i]) && isalnum(input[i - 1]) ||
        (isalnum(input[i]) && input[i - 1] == ')') ||
        (isalnum(input[i]) && input[i - 1] == '*') ||
        (input[i - 1] != '+' && input[i] == '(')) {
      result += '.';
    }
    result += input[i];
  }

  return result;
}
