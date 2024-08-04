#ifndef UTILS_H
#define UTILS_H

#include <string>

class regEx {
 private:
  std::string infix;
  std::string dottedInfix;
  std::string postfix;

 public:
  // Constructor
  regEx() {}

  // Public getter function to access postfix
  std::string getPostfix() const { return postfix; }

  // Method to take input from the terminal
  void inputFromTerminal();
  void checkRegularExpression();

  int precedence(char op);
  void infixToPostfix();
  void insertDots();
};

#endif  // UTILS_H
