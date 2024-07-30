#include <iostream>
#include <string>

#include "dfa.h"
#include "graphviz_utils.h"
#include "nfa.h"
#include "utils.h"

int main() {
  std::cout << "Enter the expression: ";
  std::string infix;
  std::getline(std::cin, infix);

  std::string processedInfix = insertDots(infix);
  std::string postfix = infixToPostfix(processedInfix);
  NFA nfa = NFA::constructNFA(postfix);

  std::string dotfile_nfa = "nfa.dot";
  std::string imagefile_nfa = "nfa.png";

  generate_dot_nfa(nfa, dotfile_nfa);
  generate_image(dotfile_nfa, imagefile_nfa);

  std::cout << "NFA graph has been generated and saved as " << imagefile_nfa
            << std::endl;

  // Reading NFA for converting to DFA
  NFA nfa_for_dfa = NFA::readNFAFromDotFile(nfa);

  // nfa_for_dfa.print();

  // Printing the NFA
  DFA::printNFA(nfa_for_dfa);

  // Converting the NFA to DFA
  DFA dfa = DFA::convertNFAtoDFA(nfa_for_dfa);

  // Printing the DFA
  DFA::printDFA(dfa);

  std::string dotfile_dfa = "dfa.dot";
  std::string imagefile_dfa = "dfa.png";

  generate_dot_dfa(dfa, dotfile_dfa);
  generate_image(dotfile_dfa, imagefile_dfa);

  std::cout << "DFA graph has been generated and saved as " << imagefile_dfa
            << std::endl;

  return 0;
}
