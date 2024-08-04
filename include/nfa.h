#ifndef NFA_H
#define NFA_H

#include <unordered_map>
#include <vector>

#include "automata.h"
#include "state.h"

class NFA : public Automata {
 private:
  State* start;
  State* accept;

  std::unordered_map<int, std::unordered_map<char, std::vector<int>>>
      transitionFn;

 public:
  // Default constructor
  NFA() : Automata({}, {}, -1, {}), start(nullptr), accept(nullptr) {}

  // Constructor for Thompson's Construction
  NFA(State* start, State* accept);

  // Constructor for NFA to DFA Conversion
  NFA(const std::vector<int>& states, const std::vector<char>& inputSymbols,
      const std::unordered_map<int, std::unordered_map<char, std::vector<int>>>&
          transitionFn,
      int startState, const std::vector<int>& finalStates);

  // Getter functions for Thompson's Construction
  State* getStart() const;
  State* getAccept() const;

  // Getter functions for NFA to DFA Conversion
  const std::unordered_map<int, std::unordered_map<char, std::vector<int>>>&
  getTransitionFn() const;

  // Function declarations
  NFA basic(char c);
  NFA unionNFA(NFA a, NFA b);
  NFA concatNFA(NFA a, NFA b);
  NFA kleeneStarNFA(NFA a);
  NFA constructNFA(const std::string& postfix);

  // Convert NFA to DFA-like structure
  NFA readNFAforDFAconversion();
};

#endif  // NFA_H
