cmake_minimum_required(VERSION 3.10)

# Set the project name
project(RegEx2DFA)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory
include_directories(include)

# Add the executable
add_executable(RegEx2DFA src/main.cpp src/nfa.cpp src/utils.cpp src/graphviz_utils.cpp src/dfa.cpp src/print_utils.cpp)

# Link the Graphviz library
target_link_libraries(RegEx2DFA gvc cdt)
