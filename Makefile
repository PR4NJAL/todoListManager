CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = task_manager
SRCDIR = .
OBJDIR = obj

# Source files
SOURCES = main.cpp TaskManager.cpp FileManager.cpp UIHandler.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
HEADERS = Task.h TaskManager.h FileManager.h UIHandler.h

# Default target
all: $(TARGET)

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Link target
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile source files
$(OBJDIR)/%.o: %.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Clean and rebuild
rebuild: clean all

# Create content directory
setup:
	mkdir -p content

# Install (copy to /usr/local/bin - requires sudo)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

.PHONY: all clean rebuild setup install