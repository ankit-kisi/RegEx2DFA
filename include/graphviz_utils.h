#ifndef GRAPHVIZ_UTILS_H
#define GRAPHVIZ_UTILS_H

#include <string>

#include "dfa.h"
#include "nfa.h"

void generate_dot_nfa(const NFA& nfa, const std::string& filename);
void generate_image(const std::string& dotfile, const std::string& imagefile);
void generate_dot_dfa(DFA& dfa, const std::string& filename);

#endif  // GRAPHVIZ_UTILS_H
