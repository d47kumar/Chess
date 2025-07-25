CXX = g++
CXXFLAGS = -std=c++2a -Wall -O2 -g -MMD -Werror=vla -I/opt/X11/include
LDFLAGS = -L/opt/X11/lib -lX11
SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = $(OBJECTS:.o=.d)
EXEC = chess

# Default target
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

# Rules for compiling .cc files into .o files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependencies
-include $(DEPENDS)

# Clean target
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(DEPENDS) $(EXEC)
