// print_utils.h
#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "dfa.h"
#include "nfa.h"

// Function declarations
void printNFA(NFA &nfa);
void printDFA(DFA &dfa);
void printeClosure(const NFA &nfa,
                   std::unordered_map<int, std::unordered_set<int>> &eClosure);
void printMappings(
    std::unordered_map<int, std::unordered_set<int>> &mappedStates);

#endif  // PRINT_UTILS_H
