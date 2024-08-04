// print_utils.cpp
#include "print_utils.h"

#include <iomanip>
#include <iostream>

#include "dfa.h"
#include "nfa.h"

void printNFA(NFA &nfa) {
  int width = 6;
  std::cout << "Given NFA:\n";
  std::cout << "States: ";
  for (int c : nfa.getStates()) {
    std::cout << c << ", ";
  }

  std::cout << "\b\b \nInput symbols: ";
  for (char c : nfa.getInputSymbols()) {
    std::cout << c << ", ";
  }

  std::cout << "\b\b \nTransition Function:\n";
  std::cout << std::setw(width) << "";
  for (char c : nfa.getInputSymbols()) {
    std::cout << std::setw(width) << c;
  }
  std::cout << std::setw(width) << "$" << std::endl;
  for (int srcState : nfa.getStates()) {
    std::cout << std::setw(width) << srcState;
    std::vector<char> symbols = nfa.getInputSymbols();
    symbols.push_back('$');
    for (char symbol : symbols) {
      std::unordered_map<int, std::unordered_map<char, std::vector<int>>>
          transitionFn = nfa.getTransitionFn();
      std::vector<int> destStates = transitionFn[srcState][symbol];
      std::string str = "";
      for (int state : destStates) {
        str += std::to_string(state);
      }
      std::cout << std::setw(width) << str;
    }
    std::unordered_map<int, std::unordered_map<char, std::vector<int>>>
        transitionFn = nfa.getTransitionFn();
    std::vector<int> destStates = transitionFn[srcState]['$'];
    std::string str = "";
    for (int state : destStates) {
      str += state;
    }
    std::cout << std::setw(width) << str << std::endl;
  }

  std::cout << "Start State: " << nfa.getStartState();
  std::cout << "\nFinal States: ";
  for (int c : nfa.getFinalStates()) {
    std::cout << c << ", ";
  }
  std::cout << "\b\b \n\n";
}

void printDFA(DFA &dfa) {
  int width = 6;
  std::cout << "\n\nThe converted DFA is:\n";
  std::cout << "States: ";
  for (int i : dfa.getStates()) {
    std::cout << i << ", ";
  }

  std::cout << "\b\b \nInput symbols: ";
  for (char c : dfa.getInputSymbols()) {
    std::cout << c << ", ";
  }

  std::cout << "\b\b \nTransition Function:\n";
  std::cout << std::setw(width) << "";
  for (char c : dfa.getInputSymbols()) {
    std::cout << std::setw(width) << c;
  }
  for (int srcState : dfa.getStates()) {
    std::cout << std::endl << std::setw(width) << srcState;
    for (char symbol : dfa.getInputSymbols()) {
      std::unordered_map<int, std::unordered_map<char, int>> transitionFn =
          dfa.getTransitionFn();
      int destState = transitionFn[srcState][symbol];
      std::cout << std::setw(width) << destState;
    }
  }

  std::cout << "\nStart State: " << dfa.getStartState();
  std::cout << "\nFinal States: ";
  for (int c : dfa.getFinalStates()) {
    std::cout << c << ", ";
  }
  std::cout << "\b\b \n\n";
}

void printeClosure(const NFA &nfa,
                   std::unordered_map<int, std::unordered_set<int>> &eClosure) {
  std::cout << "Epsilon Closures are:";
  for (int state : nfa.getStates()) {
    std::cout << "\nState " << state << ": ";
    for (int c : eClosure[state]) {
      std::cout << c << " ";
    }
  }
}

void printMappings(
    std::unordered_map<int, std::unordered_set<int>> &mappedStates) {
  std::cout << "\n\nMapped states are:\n";
  std::cout << "DFA == NFA\n";
  int n = mappedStates.size();
  for (int i = 0; i < n; i++) {
    std::cout << i << " == ";
    for (auto c : mappedStates[i]) {
      std::cout << c << ", ";
    }
    std::cout << "\b\b \n";
  }
}
