#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <unordered_map>
#include <vector>

class Automata {
 protected:
  std::vector<int> states;
  std::vector<char> inputSymbols;
  int startState;
  std::vector<int> finalStates;

 public:
  // Constructor
  Automata(const std::vector<int>& states,
           const std::vector<char>& inputSymbols, int startState,
           const std::vector<int>& finalStates);

  // Getter functions
  const std::vector<int>& getStates() const;
  const std::vector<char>& getInputSymbols() const;
  int getStartState() const;
  const std::vector<int>& getFinalStates() const;

  // Virtual destructor
  virtual ~Automata() = default;

  // Pure virtual functions for specific automata types
  //   virtual const std::unordered_map<int, std::unordered_map<char, int>>&
  //   getTransitionFn() const = 0;
};

#endif  // AUTOMATA_H
