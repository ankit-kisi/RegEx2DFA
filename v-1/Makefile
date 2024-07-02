# Define variables
CXX = g++
CXXFLAGS = -std=c++11 -I./graphviz/include
LDFLAGS = -L./graphviz/lib -lgvc -lcdt

# Define the target executable
TARGET = main

# Define the source files
SOURCES = main.cpp

# Define the object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target to build the executable
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Rule to build the object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build
clean:
	rm -f $(TARGET) $(OBJECTS)
