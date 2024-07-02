#ifndef GRAPHVIZ_UTILS_H
#define GRAPHVIZ_UTILS_H

#include "nfa.h"
#include <string>

void generate_dot(const NFA& nfa, const std::string& filename);
void generate_image(const std::string& dotfile, const std::string& imagefile);

#endif // GRAPHVIZ_UTILS_H
