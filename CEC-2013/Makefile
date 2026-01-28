CXX = gcc
CXXFLAGS = -c -fPIC
BUILDDIR = build
TARGET = $(BUILDDIR)/cec2013_func.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): cec2013_func.c
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BUILDDIR)
