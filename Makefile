# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -O3 -Iclasses/

# Source files
SRC_DIR := .
CLASSES_DIR := classes
SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(CLASSES_DIR)/*.cpp)

# Object files
OBJS := $(SRCS:.cpp=.o)

# Executable name
TARGET := build/matching_engine

# Default target
all: $(TARGET)

# Link all objects
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean