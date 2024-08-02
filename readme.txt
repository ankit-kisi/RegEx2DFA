g++ -std=c++11 -I/path/to/graphviz/include -I./include -c src/main.cpp -o src/main.o
g++ -std=c++11 -I/path/to/graphviz/include -I./include -c src/nfa.cpp -o src/nfa.o
g++ -std=c++11 -I/path/to/graphviz/include -I./include -c src/regEx.cpp -o src/regEx.o
g++ -std=c++11 -I/path/to/graphviz/include -I./include -c src/graphviz_utils.cpp -o src/graphviz_utils.o
g++ -std=c++11 -I/path/to/graphviz/include -I./include -c src/dfa.cpp -o src/dfa.o
g++ -std=c++11 -I/path/to/graphviz/include -I./include -c src/print_utils.cpp -o src/print_utils.o
g++ -std=c++11 -I/path/to/graphviz/include -I./include -c src/windowManagement.cpp -o src/windowManagement.o


g++ src/main.o src/nfa.o src/regEx.o src/graphviz_utils.o src/dfa.o src/print_utils.o src/windowManagement.o -o main -L/path/to/graphviz/lib -lgvc -lcdt