# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -I./include

# Linker flags
LDFLAGS = -L./graphviz/lib -lgvc -lcdt

# Source and header directories
SRC_DIR = src
INC_DIR = include

# Source files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/nfa.cpp $(SRC_DIR)/utils.cpp $(SRC_DIR)/graphviz_utils.cpp $(SRC_DIR)/dfa.cpp $(SRC_DIR)/print_utils.cpp

# Header files
HEADERS = $(INC_DIR)/nfa.h $(INC_DIR)/utils.h $(INC_DIR)/graphviz_utils.h $(INC_DIR)/dfa.h $(INC_DIR)/print_utils.h

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)

# Executable name
TARGET = RegEx2DFA

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile each source file to an object file
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(OBJS) $(TARGET)
	rm -f *.dot *.png

# Phony targets
.PHONY: all clean
