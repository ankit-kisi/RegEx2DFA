#ifndef NFA_H
#define NFA_H

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class State {
 public:
  int id;
  std::vector<std::pair<char, State*>> transitions;
  State(int id);
};

class NFA {
 public:
  // Attributes for Thompson's Construction
  State* start;
  State* accept;

  // Attributes for NFA to DFA Conversion
  std::vector<int> states;
  std::vector<char> inputSymbols;
  std::unordered_map<int, std::unordered_map<char, std::vector<int>>>
      transitionFn;
  int startState;
  std::vector<int> finalStates;

  // Constructor for Thompson's Construction
  NFA(State* start, State* accept);

  // Constructor for NFA to DFA Conversion
  NFA(const std::vector<int>& states, const std::vector<char>& inputSymbols,
      const std::unordered_map<int, std::unordered_map<char, std::vector<int>>>
          transitionFn,
      int startState, const std::vector<int>& finalStates);

  // Function declarations
  static NFA basic(char c);
  static NFA unionNFA(NFA a, NFA b);
  static NFA concatNFA(NFA a, NFA b);
  static NFA kleeneStarNFA(NFA a);
  static NFA constructNFA(const std::string& postfix);

  // Convert NFA to DFA-like structure
  static NFA readNFAFromDotFile(const NFA& nfa);

  void print() const;

  // Other methods if needed
};

// External declaration of stateId
extern int stateId;

#endif  // NFA_H
