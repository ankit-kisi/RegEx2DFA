#ifndef STATE_H
#define STATE_H

#include <utility>
#include <vector>

class State {
 private:
  int id;
  std::vector<std::pair<char, State*>> transitions;

 public:
  State(int id);

  int getId() const;
  void addTransition(char symbol, State* state);
  const std::vector<std::pair<char, State*>>& getTransitions() const;
};

#endif  // STATE_H
