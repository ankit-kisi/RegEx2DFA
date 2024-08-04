#include "state.h"

State::State(int id) : id(id) {}

int State::getId() const { return id; }

void State::addTransition(char symbol, State* state) {
  transitions.emplace_back(symbol, state);
}

const std::vector<std::pair<char, State*>>& State::getTransitions() const {
  return transitions;
}
