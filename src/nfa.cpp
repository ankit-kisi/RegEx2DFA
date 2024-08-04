#include "nfa.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>

#include "state.h"

// Initialize the static member
int stateId = 0;

// Constructor for Thompson's Construction
NFA::NFA(State* start, State* accept)
    : Automata({}, {}, -1, {}), start(start), accept(accept) {}

// Constructor for NFA to DFA Conversion
NFA::NFA(
    const std::vector<int>& states, const std::vector<char>& inputSymbols,
    const std::unordered_map<int, std::unordered_map<char, std::vector<int>>>&
        transitionFn,
    int startState, const std::vector<int>& finalStates)
    : Automata(states, inputSymbols, startState, finalStates),
      transitionFn(transitionFn) {}

// getter functions

State* NFA::getStart() const { return start; }

State* NFA::getAccept() const { return accept; }

const std::unordered_map<int, std::unordered_map<char, std::vector<int>>>&
NFA::getTransitionFn() const {
  return transitionFn;
};

NFA NFA::basic(char c) {
  State* start = new State(stateId++);
  State* accept = new State(stateId++);
  start->addTransition(c, accept);
  return NFA(start, accept);
}

NFA NFA::unionNFA(NFA a, NFA b) {
  State* start = new State(stateId++);
  State* accept = new State(stateId++);
  start->addTransition('\0', a.getStart());
  start->addTransition('\0', b.getStart());
  a.getAccept()->addTransition('\0', accept);
  b.getAccept()->addTransition('\0', accept);
  return NFA(start, accept);
}

NFA NFA::concatNFA(NFA a, NFA b) {
  a.getAccept()->addTransition('\0', b.getStart());
  return NFA(a.getStart(), b.getAccept());
}

NFA NFA::kleeneStarNFA(NFA a) {
  State* start = new State(stateId++);
  State* accept = new State(stateId++);
  start->addTransition('\0', a.getStart());
  start->addTransition('\0', accept);
  a.getAccept()->addTransition('\0', a.getStart());
  a.getAccept()->addTransition('\0', accept);
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
  stateId = 0;  // Reset the stateId in case the user wants to enter
                // another regular expression

  return nfaStack.top();
}

NFA NFA::readNFAforDFAconversion() {
  std::stack<State*> stateStack;

  // Push the start state to the stack
  stateStack.push(getStart());
  // Vector to keep track of visited states
  std::vector<bool> visited(getAccept()->getId() + 1, false);

  // all states are stored in the states vector
  for (int i = 0; i <= getAccept()->getId(); i++) {
    states.push_back(i);
  }

  finalStates.push_back(getAccept()->getId());
  startState = getStart()->getId();

  while (!stateStack.empty()) {
    State* state = stateStack.top();
    stateStack.pop();
    if (visited[state->getId()]) continue;
    visited[state->getId()] = true;

    auto& transitions = state->getTransitions();

    for (auto& trans : transitions) {
      int fromState = state->getId();
      char inputSymbol = (trans.first == '\0' ? '$' : trans.first);

      int toState = trans.second->getId();

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
