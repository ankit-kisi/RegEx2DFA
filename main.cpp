#include <iostream>
#include <string>
#include "nfa.h"
#include "graphviz_utils.h"
#include "utils.h"

int main() {
    std::cout << "Enter the expression: ";
    std::string infix;
    std::getline(std::cin, infix);

    std::string processedInfix = insertDots(infix);
    std::string postfix = infixToPostfix(processedInfix);
    NFA nfa = constructNFA(postfix);

    std::string dotfile = "nfa.dot";
    std::string imagefile = "nfa.png";

    generate_dot(nfa, dotfile);
    generate_image(dotfile, imagefile);

    std::cout << "NFA graph has been generated and saved as " << imagefile << std::endl;

    return 0;
}
