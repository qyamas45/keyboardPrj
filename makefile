ifeq ($(OS), Darwin)
	GLFW_PREFIX := $(shell brew --prefix glfw)
	FREETYPE_PREFIX := $(shell brew --prefix freetype)
 
endif 
#Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -Wextra -std=c++11

# Linker flags for OpenGL and GLFW

 
# Linker flags for OpenGL and GLFW 
ifeq ($(OS), Darwin) 
	LDFLAGS = -L$(GLFW_PREFIX)/lib \ 
			  -L$(FREETYPE_PREFIX)/lib \ 
			  -lglfw -lfreetype \ 
			  -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo else LDFLAGS = -Llibs -lopengl32 -lglfw3dll freetype/objs/freetype.a endif
else
	 
	LDFLAGS = -Llibs -lopengl32 -lglfw3dll freetype/objs/freetype.a 
endif
# Include directories
INCLUDES = -Iinclude -I$(GLFW_PREFIX)/include -I$(FREETYPE_PREFIX)/include -Icamera.h

# Target executable
TARGET = program

# Source files
SRCS =  src/main.cpp glad.c src/camera.h

# Object files	
OBJS = src/main.o  glad.o

# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Rule to compile C++ source files
src/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to compile C source files
glad.o: glad.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
