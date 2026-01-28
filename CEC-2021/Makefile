CXX = g++
CXXFLAGS = -c -fPIC
BUILDDIR = build
TARGET = $(BUILDDIR)/cec21_test_func.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): cec21_test_func.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BUILDDIR)
