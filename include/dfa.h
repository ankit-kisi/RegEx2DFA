#ifndef DFA_H
#define DFA_H

#include <unordered_map>
#include <unordered_set>

#include "automata.h"
#include "nfa.h"

class DFA : public Automata {
 private:
  std::unordered_map<int, std::unordered_map<char, int>> transitionFn;

 public:
  // Constructor
  DFA() : Automata({}, {}, 0, {}), transitionFn() {
    // Default initialization of Automata base class and transitionFn
  }
  DFA(const std::vector<int>& states, const std::vector<char>& inputSymbols,
      const std::unordered_map<int, std::unordered_map<char, int>>&
          transitionFn,
      int startState, const std::vector<int>& finalStates);

  // Getter functions
  const std::unordered_map<int, std::unordered_map<char, int>>&
  getTransitionFn() const;

  // Function declarations
  std::unordered_map<int, std::unordered_set<int>> findeClosure(const NFA& nfa);

  DFA convertNFAtoDFA(const NFA& nfa);
};

#endif  // DFA_H
