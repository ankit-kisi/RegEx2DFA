#include <iostream>
#include <string>

#include "dfa.h"
#include "graphviz_utils.h"
#include "nfa.h"
#include "print_utils.h"
#include "regEx.h"

int main() {
  std::cout << "" << std::endl;
  std::cout << "---Welcome to ReEx2DFA---" << std::endl;
  std::cout << "" << std::endl;
  regEx x;
  std::string infix = x.inputFromTerminal();
  
  try {
      checkRegularExpression(infix); 
  } catch (const std::invalid_argument& e) {
      std::cerr << e.what() << std::endl;
      std::exit(EXIT_FAILURE);  // Terminate the program
  }
  
  std::string processedInfix = regEx::insertDots(infix);
  std::string postfix = regEx::infixToPostfix(processedInfix);

  NFA nfa = NFA::constructNFA(postfix);

  std::string dotfile_nfa = "nfa.dot";
  std::string imagefile_nfa = "nfa.png";

  generate_dot_nfa(nfa, dotfile_nfa);
  generate_image(dotfile_nfa, imagefile_nfa);

  // Reading NFA for converting to DFA
  NFA nfa_for_dfa = NFA::readNFAforDFAconversion(nfa);

  // Printing the NFA
  printNFA(nfa_for_dfa);

  // Converting the NFA to DFA
  DFA dfa = DFA::convertNFAtoDFA(nfa_for_dfa);

  // Printing the DFA
  printDFA(dfa);

  std::string dotfile_dfa = "dfa.dot";
  std::string imagefile_dfa = "dfa.png";

  generate_dot_dfa(dfa, dotfile_dfa);
  generate_image(dotfile_dfa, imagefile_dfa);

  return 0;
}
