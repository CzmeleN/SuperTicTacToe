# Output files
TARGET = bin/SuperTicTacToe
TEST_TARGET = bin/Test_SuperTicTacToe

# Compilation flags
CXX = g++
CXXFLAGS = -Iinclude -Iengine/include -Iutils -Wall -Wextra -pedantic -O2 -flto -march=native -std=c++17

# Directories
SRCDIR = src
ENGINE_SRCDIR = engine/src
UTILSDIR = utils
INCDIR = include
TESTDIR = tests
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(ENGINE_SRCDIR)/*.cpp) $(wildcard $(UTILSDIR)/*.cpp)
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp)) \
          $(patsubst $(ENGINE_SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(ENGINE_SRCDIR)/*.cpp)) \
          $(patsubst $(UTILSDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(UTILSDIR)/*.cpp))
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SOURCES))

# End rule
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Object files rule for source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Object files rule for engine source files
$(OBJDIR)/%.o: $(ENGINE_SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Object files rule for utils source files
$(OBJDIR)/%.o: $(UTILSDIR)/%.cpp
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
