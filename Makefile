# Output files
TARGET = bin/SuperTicTacToe
TEST_TARGET = bin/Test_SuperTicTacToe

# Compilation flags
CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -pedantic -O2 -flto -march=native -std=c++11

# Directories
SRCDIR = src
INCDIR = include
TESTDIR = tests
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SOURCES))

# End rule
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Object files rule
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test compilation rule
$(OBJDIR)/test_%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Creating test program rule
$(TEST_TARGET): $(OBJECTS) $(TEST_OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) $(TEST_OBJECTS) -o $(TEST_TARGET)

# Running tests
.PHONY: test
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Cleaning
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Run rule
.PHONY: run
run: $(TARGET)
	./$(TARGET)
