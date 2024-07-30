# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -I./graphviz/include

# Linker flags
LDFLAGS = -L./graphviz/lib -lgvc -lcdt

# Source files
SRCS = main.cpp nfa.cpp utils.cpp graphviz_utils.cpp dfa.cpp

# Header files
HEADERS = nfa.h utils.h graphviz_utils.h dfa.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = main

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile each source file to an object file
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
