#include <iostream>
#include <limits>
#include <string>

#include "dfa.h"
#include "graphviz_utils.h"
#include "nfa.h"
#include "print_utils.h"
#include "regEx.h"
#include "windowManagement.h"

int main() {
  std::cout << "\033[32m" << "---Welcome to ReEx2DFA---" << "\033[0m"
            << std::endl;
  bool isRunning = true;

  while (isRunning) {
    regEx x;
    std::string infix = x.inputFromTerminal();

    std::string processedInfix = regEx::insertDots(infix);
    std::string postfix = regEx::infixToPostfix(processedInfix);

    NFA nfa = NFA::constructNFA(postfix);

    // Reading NFA for converting to DFA
    NFA nfa_for_dfa = NFA::readNFAforDFAconversion(nfa);

    // Printing the NFA
    printNFA(nfa_for_dfa);

    // Converting the NFA to DFA
    DFA dfa = DFA::convertNFAtoDFA(nfa_for_dfa);

    // Printing the DFA
    printDFA(dfa);

    std::string dotfile_nfa = "nfa.dot";
    std::string dotfile_dfa = "dfa.dot";

    generate_dot_nfa(nfa, dotfile_nfa);
    generate_dot_dfa(dfa, dotfile_dfa);

    std::vector<std::string> imageFiles = {"nfa.png", "dfa.png"};
    generate_image(dotfile_nfa, imageFiles[0]);
    generate_image(dotfile_dfa, imageFiles[1]);

    // Create the WindowManagement object based on the platform
    WindowManagement* wm = createWindowManagement();

    // Open files
    for (const auto& file : imageFiles) {
      wm->openFile(file);
    }

    // Checking for another regular expression
    char choice;
    std::cout << "\033[33m" << "\nDo you want to continue? (y/n): " << "\033[0m"
              << std::endl;
    std::cin >> choice;

    // Clear the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 'n' || choice == 'N') {
      isRunning = false;
    } else if (choice == 'y' || choice == 'Y') {
      isRunning = true;

    } else {
      std::cerr << "\033[31m" << "\nInvalid choice. Exiting..."
                << "\033[0m" << std::endl;
      isRunning = false;
    }
    // close the png files
    wm->closeWindows(imageFiles);
  }
  std::cout << "\033[32m" << "\n---Thank you for using ReEx2DFA---"
            << "\033[0m" << std::endl;

  return 0;
}
