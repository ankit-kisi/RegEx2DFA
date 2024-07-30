#include "dfa.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "nfa.h"

// Constructor definition
DFA::DFA(
    const std::vector<int> &states, const std::vector<char> &inputSymbols,
    const std::unordered_map<int, std::unordered_map<char, int>> &transitionFn,
    int startState, const std::vector<int> &finalStates)
    : states(states),
      inputSymbols(inputSymbols),
      transitionFn(transitionFn),
      startState(startState),
      finalStates(finalStates) {}

std::unordered_map<int, std::unordered_set<int>> DFA::findeClosure(NFA &nfa) {
  std::unordered_map<int, std::unordered_set<int>> eClosure;
  for (int c : nfa.states) {
    std::queue<int> q;
    std::unordered_set<int> visited;
    q.push(c);
    visited.insert(c);
    while (!q.empty()) {
      int srcState = q.front();
      q.pop();
      std::vector<int> destStates = nfa.transitionFn[srcState]['$'];
      for (int destState : destStates) {
        if (visited.find(destState) == visited.end()) {
          visited.insert(destState);
          q.push(destState);
        }
      }
    }
    for (auto eReachableState : visited) {
      eClosure[c].insert(eReachableState);
    }
  }
  return eClosure;
}

void DFA::printeClosure(
    NFA &nfa, std::unordered_map<int, std::unordered_set<int>> &eClosure) {
  std::cout << "Epsilon Closures are:";
  for (int state : nfa.states) {
    std::cout << "\nState " << state << ": ";
    for (int c : eClosure[state]) {
      std::cout << c << " ";
    }
  }
}

void DFA::printMappings(
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

DFA DFA::convertNFAtoDFA(NFA &nfa) {
  std::unordered_map<int, std::unordered_set<int>> eClosure = findeClosure(nfa);
  printeClosure(nfa, eClosure);

  DFA dfa;
  dfa.inputSymbols = nfa.inputSymbols;
  dfa.startState = 0;
  int noOfDFAStates = 1;
  std::unordered_map<int, std::unordered_set<int>> mappedStates;
  std::queue<int> q;
  q.push(0);
  mappedStates[0] = eClosure[nfa.startState];

  while (!q.empty()) {
    int dfaState = q.front();
    q.pop();
    for (char symbol : nfa.inputSymbols) {
      std::unordered_set<int> reach;
      std::unordered_set<int> nfaStates = mappedStates[dfaState];
      for (int srcState : nfaStates) {
        std::vector<int> destStates = nfa.transitionFn[srcState][symbol];
        for (int destState : destStates) {
          std::unordered_set<int> s = eClosure[destState];
          reach.insert(s.begin(), s.end());
        }
      }

      int found = -1;
      for (int i = 0; i < noOfDFAStates; i++) {
        if (mappedStates[i] == reach) {
          found = i;
          break;
        }
      }
      if (found != -1) {
        dfa.transitionFn[dfaState][symbol] = found;
      } else {
        dfa.transitionFn[dfaState][symbol] = noOfDFAStates;
        mappedStates[noOfDFAStates] = reach;
        q.push(noOfDFAStates);
        noOfDFAStates++;
      }
    }
  }

  printMappings(mappedStates);
  for (int i = 0; i < noOfDFAStates; i++) {
    dfa.states.push_back(i);
  }

  auto &states1 = nfa.finalStates;
  for (int i = 0; i < noOfDFAStates; i++) {
    auto &states2 = mappedStates[i];
    for (auto c1 : states1) {
      if (states2.find(c1) != states2.end()) {
        dfa.finalStates.push_back(i);
        break;
      }
    }
  }

  return dfa;
}

void DFA::printNFA(NFA &nfa) {
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
    for (char symbol : nfa.inputSymbols) {
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

void DFA::printDFA(DFA &dfa) {
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
