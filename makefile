# Omer Cohen
# omer7530@gmail.com

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -g

# Valgrind flags
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

# Target executables
TARGET = tree
TEST_TARGET = test

# Source files
SRCS = main.cpp
TEST_SRCS = test.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Header files
HEADERS = node.hpp tree.hpp complex.hpp

# Run the target executable
run: $(TARGET)
	./$(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Rule to run valgrind
valgrind: $(TARGET)
	valgrind $(VALGRIND_FLAGS) ./$(TARGET)
	valgrind $(VALGRIND_FLAGS) ./$(TEST_TARGET)
	make clean

# Phony targets
.PHONY: all run test valgrind clean

# Rule to clean the build directory
clean:
	rm -f *.o *.dot *.png tree test