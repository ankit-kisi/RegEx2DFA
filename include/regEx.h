#ifndef UTILS_H
#define UTILS_H

#include <string>

class regEx {
 private:
  std::string infix;

 public:
  // Constructor
  regEx() {}

  // Method to take input from the terminal
  std::string inputFromTerminal();

  static int precedence(char op);
  static std::string infixToPostfix(const std::string& exp);
  static std::string insertDots(const std::string& input);
};

#endif  // UTILS_H
