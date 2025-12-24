# Makefile for Hello World in C++

# The compiler to use
CXX = g++

# The compiler flags (you can add debugging info with -g)
CXXFLAGS = -Wall -std=c++11

# The name of the final executable
TARGET = unroll

# The source files
SRC = main.cpp

# The object files (they are the compiled .o files)
OBJ = $(SRC:.cpp=.o)

# Default rule
all: $(TARGET)

# How to build the target from the object files
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Rule to generate the object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the generated files
clean:
	rm -f $(OBJ) $(TARGET)

# Install rule
install: $(TARGET)
	# Make sure we have proper permissions to copy to /bin (or /usr/local/bin)
	# We may need sudo for system-wide installation
	install -m 755 $(TARGET) /usr/local/bin/

# Uninstall rule (optional)
uninstall:
	rm -f /usr/local/bin/$(TARGET)
