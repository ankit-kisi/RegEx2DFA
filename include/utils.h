#ifndef UTILS_H
#define UTILS_H

#include <string>

int precedence(char op);
std::string infixToPostfix(const std::string& exp);
std::string insertDots(const std::string& input);

#endif // UTILS_H
