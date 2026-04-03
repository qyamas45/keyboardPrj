# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -Wextra -std=c++11

# Linker flags for OpenGL and GLFW
LDFLAGS = -Llibs -lopengl32 -lglfw3dll freetype/objs/freetype.a 

# Include directories
INCLUDES = -Iinclude -Isrc/objects -Isrc/core -I/freetype/include -I/freetype/include/freetype -Icamera.h -Iobjects 

# Target executable
TARGET = program

# Source files
SRCS = src/main.cpp glad.c   

# Object files
OBJS = $(SRCS:.cpp=.o)
OBJS := $(OBJS:.c=.o)
# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Rule to compile C++ source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to compile C source files
%.o: %.c
	g++ $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
