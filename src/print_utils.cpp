// print_utils.cpp
#include "print_utils.h"

#include <iomanip>
#include <iostream>

void printNFA(NFA &nfa) {
  int width = 6;
  std::cout << "Given NFA:\n";
  std::cout << "States: ";
  for (int c : nfa.states) {
    std::cout << c << ", ";
  }

  std::cout << "\b\b \nInput symbols: ";
  for (char c : nfa.inputSymbols) {
    std::cout << c << ", ";
  }

  std::cout << "\b\b \nTransition Function:\n";
  std::cout << std::setw(width) << "";
  for (char c : nfa.inputSymbols) {
    std::cout << std::setw(width) << c;
  }
  std::cout << std::setw(width) << "$" << std::endl;
  for (int srcState : nfa.states) {
    std::cout << std::setw(width) << srcState;
    std::vector<char> symbols = nfa.inputSymbols;
    symbols.push_back('$');
    for (char symbol : symbols) {
      std::vector<int> destStates = nfa.transitionFn[srcState][symbol];
      std::string str = "";
      for (int state : destStates) {
        str += std::to_string(state);
      }
      std::cout << std::setw(width) << str;
    }
    std::vector<int> destStates = nfa.transitionFn[srcState]['$'];
    std::string str = "";
    for (int state : destStates) {
      str += state;
    }
    std::cout << std::setw(width) << str << std::endl;
  }

  std::cout << "Start State: " << nfa.startState;
  std::cout << "\nFinal States: ";
  for (int c : nfa.finalStates) {
    std::cout << c << ", ";
  }
  std::cout << "\b\b \n\n";
}

void printDFA(DFA &dfa) {
  int width = 6;
  std::cout << "\n\nThe converted DFA is:\n";
  std::cout << "States: ";
  for (int i : dfa.states) {
    std::cout << i << ", ";
  }

  std::cout << "\b\b \nInput symbols: ";
  for (char c : dfa.inputSymbols) {
    std::cout << c << ", ";
  }

  std::cout << "\b\b \nTransition Function:\n";
  std::cout << std::setw(width) << "";
  for (char c : dfa.inputSymbols) {
    std::cout << std::setw(width) << c;
  }
  for (int srcState : dfa.states) {
    std::cout << std::endl << std::setw(width) << srcState;
    for (char symbol : dfa.inputSymbols) {
      int destState = dfa.transitionFn[srcState][symbol];
      std::cout << std::setw(width) << destState;
    }
  }

  std::cout << "\nStart State: " << dfa.startState;
  std::cout << "\nFinal States: ";
  for (int c : dfa.finalStates) {
    std::cout << c << ", ";
  }
  std::cout << "\b\b \n\n";
}

void printeClosure(NFA &nfa,
                   std::unordered_map<int, std::unordered_set<int>> &eClosure) {
  std::cout << "Epsilon Closures are:";
  for (int state : nfa.states) {
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
