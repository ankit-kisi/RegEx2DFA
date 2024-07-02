#ifndef NFA_H
#define NFA_H

#include <vector>
#include <utility>
#include <string>

struct State {
    int id;
    std::vector<std::pair<char, State*>> transitions;
    State(int id);
};

struct NFA {
    State* start;
    State* accept;
    NFA(State* start, State* accept);
};

// External declaration of stateId
extern int stateId;

NFA basic(char c);
NFA unionNFA(NFA a, NFA b);
NFA concatNFA(NFA a, NFA b);
NFA kleeneStarNFA(NFA a);
NFA constructNFA(const std::string& postfix);

#endif // NFA_H
