#include "dfa.h"

#include <iomanip>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "print_utils.h"

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

// Function to find epsilon closure

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
        // Check if the destination state is already visited
        // if not found it will return end of the set
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

// Function to convert NFA to DFA

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
