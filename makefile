# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -Wextra -std=c++11

# Linker flags for OpenGL and GLFW
LDFLAGS = -Llibs -lopengl32 -lglfw3dll freetype/objs/freetype.a

# Include directories
INCLUDES = -Iinclude -I/freetype/include -I/freetype/include/freetype -Icamera.h

# Target executable
TARGET = program

# Source files
SRCS = main.cpp glad.c camera.h

# Object files
OBJS = main.o glad.o

# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Rule to compile C++ source files
main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to compile C source files
glad.o: glad.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
