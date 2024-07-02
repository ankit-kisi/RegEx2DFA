#include "graphviz_utils.h"
#include <fstream>
#include <stack>
#include <vector>
#include <iostream>

void generate_dot(const NFA& nfa, const std::string& filename) {
    std::ofstream dotfile(filename);

    if (!dotfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::stack<State*> stateStack;
    stateStack.push(nfa.start);
    std::vector<bool> visited(stateId, false);  // Use stateId here

    dotfile << "digraph nfa{\n";
    dotfile << "node[shape = point] START\n";
    dotfile << "node[shape = circle] ";

    for (int i = 0; i < nfa.accept->id; i++) {
        dotfile << "q" << i << " ";
    }
    dotfile << "\n";
    dotfile << "node[shape = doublecircle] q" << nfa.accept->id << "\n";
    dotfile << "START -> q" << nfa.start->id << "[label = START]\n";

    while (!stateStack.empty()) {
        State* state = stateStack.top();
        stateStack.pop();
        if (visited[state->id]) continue;
        visited[state->id] = true;

        for (auto& trans : state->transitions) {
            dotfile << "q" << state->id << " -> " << "q" << trans.second->id 
                    << "[label = " << (trans.first == '\0' ? "ε" : std::string(1, trans.first)) << "]\n";
            stateStack.push(trans.second);
        }
    }

    dotfile << "}\n";
    dotfile.close();
}

void generate_image(const std::string& dotfile, const std::string& imagefile) {
    std::string command = "dot -Tpng " + dotfile + " -o " + imagefile;
    system(command.c_str());
}
