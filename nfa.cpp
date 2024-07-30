#include "nfa.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <unordered_set>
#include <vector>

int stateId = 0;  // Definition of stateId

State::State(int id) : id(id) {}

// for thompson's construction
NFA::NFA(State* start, State* accept) : start(start), accept(accept) {}

// for nfa to dfa conversion
NFA::NFA(
    const std::vector<int>& states, const std::vector<char>& inputSymbols,
    const std::unordered_map<int, std::unordered_map<char, std::vector<int>>>
        transitionFn,
    int startState, const std::vector<int>& finalStates)
    : states(states),
      inputSymbols(inputSymbols),
      transitionFn(transitionFn),
      startState(startState),
      finalStates(finalStates) {}

NFA NFA::basic(char c) {
  State* start = new State(stateId++);
  State* accept = new State(stateId++);
  start->transitions.push_back({c, accept});
  return NFA(start, accept);
}

NFA NFA::unionNFA(NFA a, NFA b) {
  State* start = new State(stateId++);
  State* accept = new State(stateId++);
  start->transitions.push_back({'\0', a.start});
  start->transitions.push_back({'\0', b.start});
  a.accept->transitions.push_back({'\0', accept});
  b.accept->transitions.push_back({'\0', accept});
  return NFA(start, accept);
}

NFA NFA::concatNFA(NFA a, NFA b) {
  a.accept->transitions.push_back({'\0', b.start});
  return NFA(a.start, b.accept);
}

NFA NFA::kleeneStarNFA(NFA a) {
  State* start = new State(stateId++);
  State* accept = new State(stateId++);
  start->transitions.push_back({'\0', a.start});
  start->transitions.push_back({'\0', accept});
  a.accept->transitions.push_back({'\0', a.start});
  a.accept->transitions.push_back({'\0', accept});
  return NFA(start, accept);
}

NFA NFA::constructNFA(const std::string& postfix) {
  std::stack<NFA> nfaStack;
  for (char ch : postfix) {
    if (isalnum(ch)) {
      nfaStack.push(basic(ch));
    } else if (ch == '+') {
      NFA b = nfaStack.top();
      nfaStack.pop();
      NFA a = nfaStack.top();
      nfaStack.pop();
      nfaStack.push(unionNFA(a, b));
    } else if (ch == '.') {
      NFA b = nfaStack.top();
      nfaStack.pop();
      NFA a = nfaStack.top();
      nfaStack.pop();
      nfaStack.push(concatNFA(a, b));
    } else if (ch == '*') {
      NFA a = nfaStack.top();
      nfaStack.pop();
      nfaStack.push(kleeneStarNFA(a));
    }
  }
  return nfaStack.top();
}

NFA NFA::readNFAforDFAconversion(const NFA& nfa) {
  std::vector<int> states;
  std::vector<char> inputSymbols;
  std::unordered_map<int, std::unordered_map<char, std::vector<int>>>
      transitionFn;
  int startState;  // Default value for startState
  std::vector<int> finalStates;

  std::stack<State*> stateStack;

  stateStack.push(nfa.start);
  std::vector<bool> visited(nfa.accept->id + 1, false);

  for (int i = 0; i <= nfa.accept->id; i++) {
    states.push_back(i);
  }

  finalStates.push_back(nfa.accept->id);
  startState = nfa.start->id;

  while (!stateStack.empty()) {
    State* state = stateStack.top();
    stateStack.pop();
    if (visited[state->id]) continue;
    visited[state->id] = true;

    for (auto& trans : state->transitions) {
      int fromState = state->id;
      char inputSymbol = (trans.first == '\0' ? '$' : trans.first);

      int toState = trans.second->id;

      // Check if the state exists in the outer map; if not, insert it

      transitionFn.emplace(fromState,
                           std::unordered_map<char, std::vector<int>>());

      // Check if the input symbol exists in the inner map; if not, insert it
      if (transitionFn[fromState].find(inputSymbol) ==
          transitionFn[fromState].end()) {
        transitionFn[fromState][inputSymbol] = std::vector<int>();
      }

      // Add the destination state to the vector of the given input symbol
      transitionFn[fromState][inputSymbol].push_back(toState);

      inputSymbols.push_back(inputSymbol);

      stateStack.push(trans.second);
    }
  }

  // Remove all '$' characters
  inputSymbols.erase(std::remove(inputSymbols.begin(), inputSymbols.end(), '$'),
                     inputSymbols.end());

  // Using an unordered_set to remove duplicates
  std::unordered_set<char> uniqueElements(inputSymbols.begin(),
                                          inputSymbols.end());

  // Assign the unique elements back to the vector
  inputSymbols.assign(uniqueElements.begin(), uniqueElements.end());

  return NFA(states, inputSymbols, transitionFn, startState, finalStates);
}

// void NFA::print() const {
//   std::cout << "States: ";
//   for (int state : states) {
//     std::cout << state << " ";
//   }
//   std::cout << std::endl;

//   std::cout << "Input Symbols: ";
//   for (char symbol : inputSymbols) {
//     std::cout << symbol << " ";
//   }
//   std::cout << std::endl;

//   std::cout << "Transitions: " << std::endl;
//   for (const auto& fromState : transitionFn) {
//     for (const auto& trans : fromState.second) {
//       std::cout << fromState.first << " --" << trans.first << "--> ";
//       for (int toState : trans.second) {
//         std::cout << toState << " ";
//       }
//       std::cout << std::endl;
//     }
//   }

//   std::cout << "Start State: " << startState << std::endl;

//   std::cout << "Final States: ";
//   for (int finalState : finalStates) {
//     std::cout << finalState << " ";
//   }
//   std::cout << std::endl;
// }