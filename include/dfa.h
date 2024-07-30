#ifndef DFA_H
#define DFA_H

#include <unordered_map>
#include <unordered_set>

#include "nfa.h"

class DFA {
 public:
  std::vector<int> states;
  std::vector<char> inputSymbols;
  std::unordered_map<int, std::unordered_map<char, int>> transitionFn;
  int startState;
  std::vector<int> finalStates;

  // constructor
  DFA() = default;
  DFA(const std::vector<int>& states, const std::vector<char>& inputSymbols,
      const std::unordered_map<int, std::unordered_map<char, int>>&
          transitionFn,
      int startState, const std::vector<int>& finalStates);

  // Function declarations
  static std::unordered_map<int, std::unordered_set<int>> findeClosure(
      NFA& nfa);

  static DFA convertNFAtoDFA(NFA& nfa);
};

#endif  // DFA_H
