#include "nfa.h"
#include <stack>

int stateId = 0;  // Definition of stateId

State::State(int id) : id(id) {}

NFA::NFA(State* start, State* accept) : start(start), accept(accept) {}

NFA basic(char c) {
    State* start = new State(stateId++);
    State* accept = new State(stateId++);
    start->transitions.push_back({c, accept});
    return NFA(start, accept);
}

NFA unionNFA(NFA a, NFA b) {
    State* start = new State(stateId++);
    State* accept = new State(stateId++);
    start->transitions.push_back({'\0', a.start});
    start->transitions.push_back({'\0', b.start});
    a.accept->transitions.push_back({'\0', accept});
    b.accept->transitions.push_back({'\0', accept});
    return NFA(start, accept);
}

NFA concatNFA(NFA a, NFA b) {
    a.accept->transitions.push_back({'\0', b.start});
    return NFA(a.start, b.accept);
}

NFA kleeneStarNFA(NFA a) {
    State* start = new State(stateId++);
    State* accept = new State(stateId++);
    start->transitions.push_back({'\0', a.start});
    start->transitions.push_back({'\0', accept});
    a.accept->transitions.push_back({'\0', a.start});
    a.accept->transitions.push_back({'\0', accept});
    return NFA(start, accept);
}

NFA constructNFA(const std::string& postfix) {
    std::stack<NFA> nfaStack;
    for (char ch : postfix) {
        if (isalnum(ch)) {
            nfaStack.push(basic(ch));
        } else if (ch == '+') {
            NFA b = nfaStack.top(); nfaStack.pop();
            NFA a = nfaStack.top(); nfaStack.pop();
            nfaStack.push(unionNFA(a, b));
        } else if (ch == '.') {
            NFA b = nfaStack.top(); nfaStack.pop();
            NFA a = nfaStack.top(); nfaStack.pop();
            nfaStack.push(concatNFA(a, b));
        } else if (ch == '*') {
            NFA a = nfaStack.top(); nfaStack.pop();
            nfaStack.push(kleeneStarNFA(a));
        }
    }
    return nfaStack.top();
}
