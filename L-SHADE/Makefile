CXX = g++
CXXFLAGS = -fdiagnostics-color=always -g -std=c++11
INCLUDES = -I.. -I../CEC-2013
BUILDDIR = build

SOURCES = main.cpp lshade.cpp search_algorithm.cpp ../CEC-2013/cec2013_func.c
TARGET = $(BUILDDIR)/main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET)

clean:
	rm -rf $(BUILDDIR)
