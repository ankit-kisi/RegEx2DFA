#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <cctype>
#include <vector>
#include <fstream>
#include <queue>
#include <iomanip>

// Structure for State in NFA and DFA
struct State {
    int id;
    std::vector<std::pair<char, State*>> transitions;

    State(int id) : id(id) {}
};

// Structure for NFA
struct NFA {
    State* start;
    State* accept;

    NFA(State* start, State* accept) : start(start), accept(accept) {}
};

// Structure for DFA
struct DFA {
    std::vector<int> states;
    std::vector<char> inputSymbols;
    std::unordered_map<int, std::unordered_map<char, int>> transitionFn;
    int startState;
    std::vector<int> finalStates;
};

// Function to return precedence of operators
int precedence(char op) {
    if (op == '+') return 1;
    if (op == '.') return 2; 
    if (op == '*') return 3;
    return 0;
}

// Function to convert infix expression to postfix expression
std::string infixToPostfix(const std::string& exp) {
    std::stack<char> operators;
    std::string postfix;

    for (char ch : exp) {
        if (isalnum(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Remove '(' from stack
        } else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

// Function to generate DOT file from NFA or DFA
void generate_dot(const std::string& filename, State* start, std::vector<int>& states, std::vector<char>& inputSymbols, std::unordered_map<int, std::unordered_map<char, int>>& transitionFn, std::vector<int>& finalStates) {
    std::ofstream dotfile(filename);

    if (!dotfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::stack<State*> stateStack;
    stateStack.push(start);
    std::vector<bool> visited(states.size(), false);

    dotfile << "digraph automaton{\n";
    dotfile << "rankdir=LR;\n";
    dotfile << "node [shape = point ]; start;\n";
    dotfile << "node [shape = doublecircle]; ";
    for (int state : finalStates) {
        dotfile << "q" << state << " ";
    }
    dotfile << ";\n";
    dotfile << "node [shape = circle];\n";
    dotfile << "start -> q" << start->id << ";\n";

    while (!stateStack.empty()) {
        State* state = stateStack.top();
        stateStack.pop();
        if (visited[state->id]) continue;
        visited[state->id] = true;

        for (auto& trans : state->transitions) {
            dotfile << "q" << state->id << " -> q" << trans.second->id 
                    << " [label=\"" << (trans.first == '\0' ? "ε" : std::string(1, trans.first)) << "\"];\n";
            stateStack.push(trans.second);
        }
    }

    dotfile << "}\n";
    dotfile.close();
}

// Function to generate an image from a DOT file using Graphviz
void generate_image(const std::string& dotfile, const std::string& imagefile) {
    std::string command = "dot -Tpng " + dotfile + " -o " + imagefile;
    system(command.c_str());
}

// Function to create a basic NFA for a single character
NFA basic(char c) {
    State* start = new State(0);
    State* accept = new State(1);
    start->transitions.push_back({c, accept});
    return NFA(start, accept);
}

// Function to create an NFA for the union (a + b)
NFA unionNFA(NFA a, NFA b) {
    State* start = new State(0);
    State* accept = new State(1);
    start->transitions.push_back({'\0', a.start});
    start->transitions.push_back({'\0', b.start});
    a.accept->transitions.push_back({'\0', accept});
    b.accept->transitions.push_back({'\0', accept});
    return NFA(start, accept);
}

// Function to create an NFA for concatenation (ab)
NFA concatNFA(NFA a, NFA b) {
    a.accept->transitions.push_back({'\0', b.start});
    return NFA(a.start, b.accept);
}

// Function to create an NFA for Kleene star (a*)
NFA kleeneStarNFA(NFA a) {
    State* start = new State(0);
    State* accept = new State(1);
    start->transitions.push_back({'\0', a.start});
    start->transitions.push_back({'\0', accept});
    a.accept->transitions.push_back({'\0', a.start});
    a.accept->transitions.push_back({'\0', accept});
    a.accept->transitions.push_back({'\0', start});
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

DFA convertNFAtoDFA(const NFA& nfa) {
    // Implement your DFA conversion here, as per the previous code provided
    // ...
    DFA dfa;
    // Implement DFA conversion logic here
    // ...
    return dfa;
}

int main() {
    std::cout << "--- Conversion of Regular Expression to NFA and DFA ---\n";
    std::cout << "Enter the regular expression: ";
    std::string regex;
    std::cin >> regex;

    // Convert regex to postfix
    std::string postfix = infixToPostfix(regex);

    // Construct NFA from postfix expression
    NFA nfa = constructNFA(postfix);

    // Generate DOT file and image for NFA
    std::string nfa_dotfile = "nfa.dot";
    std::string nfa_imagefile = "nfa.png";
    generate_dot(nfa_dotfile, nfa.start, nfa.states, nfa.inputSymbols, nfa.transitionFn, nfa.finalStates);
    generate_image(nfa_dotfile, nfa_imagefile);
    std::cout << "NFA graph has been generated and saved as " << nfa_imagefile << std::endl;

    // Convert NFA to DFA
    DFA dfa = convertNFAtoDFA(nfa);

    // Generate DOT file and image for DFA
    std::string dfa_dotfile = "dfa.dot";
    std::string dfa_imagefile = "dfa.png";
    generate_dot(dfa_dotfile, nullptr, dfa.states, dfa.inputSymbols, dfa.transitionFn, dfa.finalStates);
    generate_image(dfa_dotfile, dfa_imagefile);
    std::cout << "DFA graph has been generated and saved as " << dfa_imagefile << std::endl;

    return 0;
}
