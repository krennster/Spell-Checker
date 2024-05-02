CXX=g++

TARGET := p5.x
SRCS := myspell.cpp

CXXFLAGS := -std=c++11

# Default target
all: clean $(TARGET)

# Dependencies for the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean target
clean:
	rm -f $(TARGET)

.PHONY: all clean