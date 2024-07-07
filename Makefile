# Output files
TARGET = bin/SuperTicTacToe
TEST_TARGET = bin/Test_SuperTicTacToe

# Compilation flags
CXX = g++
CXXFLAGS = -Iinclude -Iengine/include -Iutils -Iutils/bot_utils -O3  -std=c++17

# Directories
SRCDIR = src
INCDIR = include
ENGINE_SRCDIR = engine/src
UTILS_SRCDIR = utils
BOT_UTILS_SRCDIR = utils/bot_utils
TESTDIR = tests
OBJDIR = obj
BINDIR = bin

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(ENGINE_SRCDIR)/*.cpp) $(wildcard $(UTILS_SRCDIR)/*.cpp) $(wildcard $(BOT_UTILS_SRCDIR)/*.cpp)
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)
OBJECTS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SOURCES)))
TEST_OBJECTS = $(patsubst %.cpp,$(OBJDIR)/test_%.o,$(notdir $(TEST_SOURCES)))

# End rule
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Object files rule
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(ENGINE_SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(UTILS_SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(BOT_UTILS_SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test object files rule
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