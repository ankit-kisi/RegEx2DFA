#include "regEx.h"

#include <cctype>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>

void regEx::inputFromTerminal() {
  bool isValidinfix = false;

  while (!isValidinfix) {
    std::cout << "\nEnter a regular expression: ";
    std::getline(std::cin, infix);

    try {
      checkRegularExpression();
      isValidinfix = true;
    } catch (const std::invalid_argument& e) {
      std::cerr << "\033[31m" << "\nError: " << e.what() << "\033[0m"
                << std::endl;
    }
  }
}

// Function to validate the regular expression string and check parentheses
void regEx::checkRegularExpression() {
  if (infix.empty()) {
    throw std::invalid_argument("Regular expression cannot be empty");
  }

  std::stack<char> parenthesesStack;

  // Variable to keep track of the last character for invalid sequences
  char lastChar = '\0';

  for (size_t i = 0; i < infix.length(); ++i) {
    char c = infix[i];

    // Check for valid characters
    if (!isalnum(c) && c != '+' && c != '*' && c != '(' && c != ')') {
      throw std::invalid_argument(
          "Invalid character in the regular expression");
    }

    // Check for invalid sequences
    if (c == '+') {
      if (i == 0 || i == infix.length() - 1) {
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
      if (i > 0 && infix[i - 1] == '(') {
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

void regEx::infixToPostfix() {
  std::stack<char> operators;

  for (char ch : dottedInfix) {
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
}

// work is left here to recognize a*(a+b) => a*.(a+b)
void regEx::insertDots() {
  // Reserve enough space to avoid frequent reallocations
  dottedInfix.reserve(infix.size() * 2);

  dottedInfix += infix[0];

  for (size_t i = 1; i < infix.size(); ++i) {
    if (isalnum(infix[i]) && isalnum(infix[i - 1]) ||
        (isalnum(infix[i]) && infix[i - 1] == ')') ||
        (isalnum(infix[i]) && infix[i - 1] == '*') ||
        (infix[i - 1] != '+' && infix[i] == '(')) {
      dottedInfix += '.';
    }
    dottedInfix += infix[i];
  }
}
