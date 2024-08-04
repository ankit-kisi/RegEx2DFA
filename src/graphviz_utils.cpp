#include "graphviz_utils.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>

void generate_dot_nfa(const NFA& nfa, const std::string& filename) {
  std::ofstream dotfile(filename);

  if (!dotfile.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return;
  }

  std::stack<State*> stateStack;

  stateStack.push(nfa.getStart());
  std::vector<bool> visited(nfa.getAccept()->getId() + 1, false);

  dotfile << "digraph NFA {\n";
  dotfile << "node [shape = point] START\n";
  dotfile << "node [shape = circle] ";

  for (int i = 0; i < nfa.getAccept()->getId(); i++) {
    dotfile << "q" << i << " ";
  }
  dotfile << "\n";
  dotfile << "node [shape = doublecircle] q" << nfa.getAccept()->getId()
          << "\n";
  dotfile << "START -> q" << nfa.getStart()->getId()
          << " [label = \" START\"]\n";

  while (!stateStack.empty()) {
    State* state = stateStack.top();
    stateStack.pop();
    if (visited[state->getId()]) continue;
    visited[state->getId()] = true;

    for (auto& trans : state->getTransitions()) {
      dotfile << "q" << state->getId() << " -> q" << trans.second->getId()
              << " [label = \" "
              << (trans.first == '\0' ? "ε" : std::string(1, trans.first))
              << "\"]\n";
      stateStack.push(trans.second);
    }
  }

  dotfile << "}\n";
  dotfile.close();

  std::cout << "NFA graph description has been written to " << filename
            << std::endl;
}

void generate_dot_dfa(DFA& dfa, const std::string& filename) {
  std::ofstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  file << "digraph DFA {\n";
  file << "node [shape = point] START\n";

  // Print the regular states
  file << "node [shape = circle] ";
  for (int state : dfa.getStates()) {
    // Only print if it's not a final state
    if (std::find(dfa.getFinalStates().begin(), dfa.getFinalStates().end(),
                  state) == dfa.getFinalStates().end()) {
      file << "q" << state << " ";
    }
  }
  file << "\n";

  // Print the final states
  file << "node [shape = doublecircle] ";
  for (int finalState : dfa.getFinalStates()) {
    file << "q" << finalState << " ";
  }
  file << "\n";

  // Print the getStart() state
  file << "START -> q" << dfa.getStartState() << " [label = \" START\"];\n";

  // Print the getTransitions()
  for (int srcState : dfa.getStates()) {
    std::unordered_set<char> seenSymbols;
    for (char symbol : dfa.getInputSymbols()) {
      if (seenSymbols.find(symbol) == seenSymbols.end()) {
        auto transitionFn = dfa.getTransitionFn();
        int destState = transitionFn[srcState][symbol];
        if (destState != -1) {
          file << "q" << srcState << " -> q" << destState << " [label = \" "
               << symbol << "\"];\n";
          seenSymbols.insert(symbol);
        }
      }
    }
  }
  file << "}\n";
  file.close();

  std::cout << "DFA graph description has been written to " << filename
            << std::endl;
}

// Function to generate a Graphviz image and open it immediately
void generate_image(const std::string& dotfile, const std::string& imagefile) {
  // Generate the image using the Graphviz dot command
  std::string command = "dot -Tpng " + dotfile + " -o " + imagefile;
  int result = system(command.c_str());

  if (result != 0) {
    std::cerr << "Error: Could not generate image " << imagefile << std::endl;
    return;
  }
}