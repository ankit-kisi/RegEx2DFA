#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <cctype>
#include <vector>

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
            // If the character is an operand, add it to the postfix expression
            postfix += ch;
        } else if (ch == '(') {
            // If the character is '(', push it to the stack
            operators.push(ch);
        } else if (ch == ')') {
            // If the character is ')', pop and output from the stack until an '(' is encountered
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Remove '(' from stack
        } else {
            // An operator is encountered
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }

    // Pop all the operators from the stack
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

// Structure for NFA state
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

int stateId = 0;

// Function to create a basic NFA for a single character
NFA basic(char c) {
    State* start = new State(stateId++);
    State* accept = new State(stateId++);
    start->transitions.push_back({c, accept});
    return NFA(start, accept);
}

// Function to create an NFA for the union (a + b)
NFA unionNFA(NFA a, NFA b) {
    State* start = new State(stateId++);
    State* accept = new State(stateId++);
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

int main() {
    std::cout<<"Enter the expression: ";
    std::string infix;
    std::cin>>infix;
    std::string postfix = infixToPostfix(infix);
    NFA nfa = constructNFA(postfix);

    // std::cout << "Start State: " << nfa.start->id << std::endl;
    // std::cout << "Accept State: " << nfa.accept->id << std::endl;
    // Printing transitions (for debugging purposes)
    std::stack<State*> stateStack;
    stateStack.push(nfa.start);
    std::vector<bool> visited(stateId, false);
    std::cout<< "digraph nfa{ \nnode[shape = point] START";
    std::cout<<"\nnode[shape = circle] ";
    for (int i= 0; i<nfa.accept->id; i++){
        std::cout<< i << " ";
    }
    std::cout<<"\nnode[shape = doublecircle] "<< nfa.accept->id;
    std::cout<<"\nSTART -> "<<nfa.start->id<<"[label = ""START""]"<<std::endl;
    while (!stateStack.empty()) {
        State* state = stateStack.top();
        stateStack.pop();
        if (visited[state->id]) continue;
        visited[state->id] = true;


        
        for (auto& trans : state->transitions) {
            std::cout<<std::endl<< state->id <<"->"<<trans.second->id <<"[ label = "<< (trans.first =='\0' ? "e" : std::string(1, trans.first))<< "]"<<std::endl;
            // std::cout << "State " << state->id << " --" << (trans.first == '\0' ? "ε" : std::string(1, trans.first)) << "--> State " << trans.second->id << std::endl;
            stateStack.push(trans.second);

        }
    }
    std::cout<<"\n}";
    return 0;
}
