#include "automata.h"

// Constructor definition
Automata::Automata(const std::vector<int>& states,
                   const std::vector<char>& inputSymbols, int startState,
                   const std::vector<int>& finalStates)
    : states(states),
      inputSymbols(inputSymbols),
      startState(startState),
      finalStates(finalStates) {}

// Getter functions

const std::vector<int>& Automata::getStates() const { return states; }

const std::vector<char>& Automata::getInputSymbols() const {
  return inputSymbols;
}

int Automata::getStartState() const { return startState; }

const std::vector<int>& Automata::getFinalStates() const { return finalStates; }
