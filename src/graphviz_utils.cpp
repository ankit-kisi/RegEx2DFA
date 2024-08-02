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

  stateStack.push(nfa.start);
  std::vector<bool> visited(nfa.accept->id + 1, false);

  dotfile << "digraph NFA {\n";
  dotfile << "node [shape = point] START\n";
  dotfile << "node [shape = circle] ";

  for (int i = 0; i < nfa.accept->id; i++) {
    dotfile << "q" << i << " ";
  }
  dotfile << "\n";
  dotfile << "node [shape = doublecircle] q" << nfa.accept->id << "\n";
  dotfile << "START -> q" << nfa.start->id << " [label = \" START\"]\n";

  while (!stateStack.empty()) {
    State* state = stateStack.top();
    stateStack.pop();
    if (visited[state->id]) continue;
    visited[state->id] = true;

    for (auto& trans : state->transitions) {
      dotfile << "q" << state->id << " -> q" << trans.second->id
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
  for (int state : dfa.states) {
    // Only print if it's not a final state
    if (std::find(dfa.finalStates.begin(), dfa.finalStates.end(), state) ==
        dfa.finalStates.end()) {
      file << "q" << state << " ";
    }
  }
  file << "\n";

  // Print the final states
  file << "node [shape = doublecircle] ";
  for (int finalState : dfa.finalStates) {
    file << "q" << finalState << " ";
  }
  file << "\n";

  // Print the start state
  file << "START -> q" << dfa.startState << " [label = \" START\"];\n";

  // Print the transitions
  for (int srcState : dfa.states) {
    std::unordered_set<char> seenSymbols;
    for (char symbol : dfa.inputSymbols) {
      if (seenSymbols.find(symbol) == seenSymbols.end()) {
        int destState = dfa.transitionFn[srcState][symbol];
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