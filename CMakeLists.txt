cmake_minimum_required(VERSION 3.10)
project(RegEx2DFA)

set(CMAKE_CXX_STANDARD 11)

find_package(Graphviz REQUIRED)

include_directories(${GRAPHVIZ_INCLUDE_DIRS})

add_executable(RegEx2DFA
    src/main.cpp
    src/nfa.cpp
    src/utils.cpp
    src/graphviz_utils.cpp
    src/dfa.cpp
    src/print_utils.cpp
)

target_link_libraries(RegEx2DFA ${GRAPHVIZ_LIBRARIES})
