#include "regEx.h"

#include <cctype>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>

std::string regEx::inputFromTerminal() {
  bool isValidInput = false;

  while (!isValidInput) {
    std::cout << "\nEnter a regular expression: ";
    std::getline(std::cin, infix);

    try {
      checkRegularExpression(infix);
      isValidInput = true;
    } catch (const std::invalid_argument& e) {
      std::cerr << "\033[31m" << "\nError: " << e.what() << "\033[0m"
                << std::endl;
    }
  }

  return infix;
}

// Function to validate the regular expression string and check parentheses
void regEx::checkRegularExpression(const std::string& input) {
  if (input.empty()) {
    throw std::invalid_argument("Regular expression cannot be empty");
  }

  std::stack<char> parenthesesStack;

  // Variable to keep track of the last character for invalid sequences
  char lastChar = '\0';

  for (size_t i = 0; i < input.length(); ++i) {
    char c = input[i];

    // Check for valid characters
    if (!isalnum(c) && c != '+' && c != '*' && c != '(' && c != ')') {
      throw std::invalid_argument(
          "Invalid character in the regular expression");
    }

    // Check for invalid sequences
    if (c == '+') {
      if (i == 0 || i == input.length() - 1) {
        throw std::invalid_argument(
            "Operator '+' cannot be at the start or end of the regular "
            "expression");
      }
      if (lastChar == '+') {
        throw std::invalid_argument(
            "Invalid sequence: " + std::string(1, lastChar) +
            std::string(1, c));
      }
    }

    if (c == '*') {
      if (i == 0) {
        throw std::invalid_argument(
            "Operator '*' cannot be at the start of the regular expression");
      }
      if (lastChar == '*' || lastChar == '+') {
        throw std::invalid_argument(
            "Invalid sequence: " + std::string(1, lastChar) +
            std::string(1, c));
      }
    }

    // Parenthesis checking
    if (c == '(') {
      parenthesesStack.push(c);
    } else if (c == ')') {
      if (parenthesesStack.empty() || parenthesesStack.top() != '(') {
        throw std::invalid_argument("Unmatched parenthesis");
      }
      parenthesesStack.pop();

      // Check for empty parentheses pair
      if (i > 0 && input[i - 1] == '(') {
        throw std::invalid_argument("Empty parentheses pair found");
      }
    }

    // Update last character
    lastChar = c;
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
