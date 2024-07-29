#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <fstream>
#include <algorithm> 
using namespace std;

class NFA
{
public:
    vector<char> states;
    vector<char> inputSymbols;
    unordered_map<char, unordered_map<char, vector<char>>> transitionFn;
    char startState;
    vector<char> finalStates;

    NFA(vector<char> &states, vector<char> &inputSymbols, unordered_map<char, unordered_map<char, vector<char>>> &transitionFn, char &startState, vector<char> &finalStates)
    {
        this->states = states;
        this->inputSymbols = inputSymbols;
        this->transitionFn = transitionFn;
        this->startState = startState;
        this->finalStates = finalStates;
    }
};

class DFA
{
public:
    vector<int> states;
    vector<char> inputSymbols;
    unordered_map<int, unordered_map<char, int>> transitionFn;
    int startState;
    vector<int> finalStates;
};

unordered_map<char, unordered_set<char>> findeClosure(NFA &nfa)
{
    unordered_map<char, unordered_set<char>> eClosure;
    for (char c : nfa.states)
    {
        queue<char> q;
        unordered_set<char> visited;
        q.push(c);
        visited.insert(c);
        while (!q.empty())
        {
            char srcState = q.front();
            q.pop();
            vector<char> destStates = nfa.transitionFn[srcState]['$'];
            for (char destState : destStates)
            {
                if (visited.find(destState) == visited.end())
                {
                    visited.insert(destState);
                    q.push(destState);
                }
            }
        }
        for (auto eReachableState : visited)
        {
            eClosure[c].insert(eReachableState);
        }
    }

    return eClosure;
}

void printeClosure(NFA &nfa, unordered_map<char, unordered_set<char>> &eClosure)
{
    cout << "Epsilon Closures are:";
    for (char state : nfa.states)
    {
        cout << "\nState " << state << ": ";
        for (char c : eClosure[state])
        {
            cout << c << " ";
        }
    }
}

void printMappings(unordered_map<int, unordered_set<char>> &mappedStates)
{
    cout << "\n\nMapped states are:\n";
    cout << "DFA == NFA\n";
    int n = mappedStates.size();
    for (int i = 0; i < n; i++)
    {
        cout << i << " == ";
        for (auto c : mappedStates[i])
        {
            cout << c << ", ";
        }
        cout << "\b\b \n";
    }
}

DFA convertNFAtoDFA(NFA &nfa)
{
    unordered_map<char, unordered_set<char>> eClosure = findeClosure(nfa);
    printeClosure(nfa, eClosure);

    DFA dfa;
    dfa.inputSymbols = nfa.inputSymbols;
    dfa.startState = 0;
    int noOfDFAStates = 1;
    unordered_map<int, unordered_set<char>> mappedStates;
    queue<int> q;
    q.push(0);
    mappedStates[0] = eClosure[nfa.startState];

    while (!q.empty())
    {
        int dfaState = q.front();
        q.pop();
        for (char symbol : nfa.inputSymbols)
        {
            unordered_set<char> reach;
            unordered_set<char> nfaStates = mappedStates[dfaState];
            for (char srcState : nfaStates)
            {
                vector<char> destStates = nfa.transitionFn[srcState][symbol];
                for (char destState : destStates)
                {
                    unordered_set<char> s = eClosure[destState];
                    reach.insert(s.begin(), s.end());
                }
            }

            int found = -1;
            for (int i = 0; i < noOfDFAStates; i++)
            {
                if (mappedStates[i] == reach)
                {
                    found = i;
                    break;
                }
            }
            if (found != -1)
            {
                dfa.transitionFn[dfaState][symbol] = found;
            }
            else
            {
                dfa.transitionFn[dfaState][symbol] = noOfDFAStates;
                mappedStates[noOfDFAStates] = reach;
                q.push(noOfDFAStates);
                noOfDFAStates++;
            }
        }
    }

    printMappings(mappedStates);
    for (int i = 0; i < noOfDFAStates; i++)
    {
        dfa.states.push_back(i);
    }

    auto &states1 = nfa.finalStates;
    for (int i = 0; i < noOfDFAStates; i++)
    {
        auto &states2 = mappedStates[i];
        for (auto c1 : states1)
        {
            if (states2.find(c1) != states2.end())
            {
                dfa.finalStates.push_back(i);
                break;
            }
        }
    }

    return dfa;
}

void printNFA(NFA &nfa)
{
    int width = 6;
    cout << "Given NFA:\n";
    cout << "States: ";
    for (char c : nfa.states)
    {
        cout << c << ", ";
    }

    cout << "\b\b \nInput symbols: ";
    for (char c : nfa.inputSymbols)
    {
        cout << c << ", ";
    }

    cout << "\b\b \nTransition Function:\n";
    cout << setw(width) << "";
    for (char c : nfa.inputSymbols)
    {
        cout << setw(width) << c;
    }
    cout << setw(width) << "$" << endl;
    for (char srcState : nfa.states)
    {
        cout << setw(width) << srcState;
        for (char symbol : nfa.inputSymbols)
        {
            vector<char> destStates = nfa.transitionFn[srcState][symbol];
            string str = "";
            for (char state : destStates)
            {
                str += state;
            }
            cout << setw(width) << str;
        }
        vector<char> destStates = nfa.transitionFn[srcState]['$'];
        string str = "";
        for (char state : destStates)
        {
            str += state;
        }
        cout << setw(width) << str << endl;
    }

    cout << "Start State: " << nfa.startState;
    cout << "\nFinal States: ";
    for (char c : nfa.finalStates)
    {
        cout << c << ", ";
    }
    cout << "\b\b \n\n";
}

void printDFA(DFA &dfa)
{
    int width = 6;
    cout << "\n\nThe converted DFA is:\n";
    cout << "States: ";
    for (int i : dfa.states)
    {
        cout << i << ", ";
    }

    cout << "\b\b \nInput symbols: ";
    for (char c : dfa.inputSymbols)
    {
        cout << c << ", ";
    }

    cout << "\b\b \nTransition Function:\n";
    cout << setw(width) << "";
    for (char c : dfa.inputSymbols)
    {
        cout << setw(width) << c;
    }
    for (int srcState : dfa.states)
    {
        cout << endl
             << setw(width) << srcState;
        for (char symbol : dfa.inputSymbols)
        {
            int destState = dfa.transitionFn[srcState][symbol];
            cout << setw(width) << destState;
        }
    }

    cout << "\nStart State: " << dfa.startState;
    cout << "\nFinal States: ";
    for (int c : dfa.finalStates)
    {
        cout << c << ", ";
    }
    cout << "\b\b \n\n";
}

void generateDotFile(DFA &dfa, const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    file << "digraph DFA {\n";
    file << "    node [shape = point] START;\n";
    
    // Print the regular states
    file << "    node [shape = circle] ";
    for (int state : dfa.states)
    {
        // Only print if it's not a final state
        if (find(dfa.finalStates.begin(), dfa.finalStates.end(), state) == dfa.finalStates.end())
        {
            file << "q" << state << " ";
        }
    }
    file << ";\n";
    
    // Print the final states
    file << "    node [shape = doublecircle] ";
    for (int finalState : dfa.finalStates)
    {
        file << "q" << finalState << " ";
    }
    file << ";\n";
    
    // Print the start state
    file << "    START -> q" << dfa.startState << " [label=\"START\"];\n";
    
    // Print the transitions
    for (int srcState : dfa.states)
    {
        for (char symbol : dfa.inputSymbols)
        {
            int destState = dfa.transitionFn[srcState][symbol];
            if (destState != -1)
            {
                file << "    q" << srcState << " -> q" << destState << " [label=\"" << symbol << "\"];\n";
            }
        }
    }
    file << "}\n";
    file.close();

    cout << "DFA graph description has been written to " << filename << endl;
}


int main()
{
    vector<char> states = {'A', 'B', 'C'};
    vector<char> inputSymbols = {'0', '1'};
    unordered_map<char, unordered_map<char, vector<char>>> transitionFn;
    transitionFn['A']['0'] = {'A'};
    transitionFn['A']['1'] = {};
    transitionFn['A']['$'] = {'B'};
    transitionFn['B']['0'] = {};
    transitionFn['B']['1'] = {'B'};
    transitionFn['B']['$'] = {'C'};
    transitionFn['C']['0'] = {'C'};
    transitionFn['C']['1'] = {'C'};
    transitionFn['C']['$'] = {};

    char startState = 'A';
    vector<char> finalStates = {'C'};

    NFA nfa(states, inputSymbols, transitionFn, startState, finalStates);
    printNFA(nfa);

    DFA dfa = convertNFAtoDFA(nfa);
    printDFA(dfa);

    generateDotFile(dfa, "dfa_true_output.dot");

    return 0;
}
