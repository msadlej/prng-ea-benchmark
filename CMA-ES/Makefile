CXX = g++
CXXFLAGS = -std=c++11 -g -fopenmp
INCLUDES = -I$(HOME)/.local/include -I/usr/include/eigen3 -I.. -I../CEC-2013
LDFLAGS = -L$(HOME)/.local/lib -Wl,-rpath,$(HOME)/.local/lib
LIBS = -lcmaes -lm
BUILDDIR = build

SOURCES = main.cpp
TARGET = $(BUILDDIR)/main
CEC2013_SRC = ../CEC-2013/cec2013_func.c

.PHONY: all clean libcmaes

all: libcmaes $(TARGET)

libcmaes:
	@if [ ! -f $(HOME)/.local/lib/libcmaes.so ] && [ ! -f $(HOME)/.local/lib/libcmaes.a ]; then \
		echo "libcmaes not found. Building..."; \
		cd ../libcmaes && mkdir -p build && cd build && \
		cmake .. -DCMAKE_INSTALL_PREFIX=$(HOME)/.local/ \
		         -DLIBCMAES_ENABLE_SURROG=OFF \
		         -DCMAKE_CXX_FLAGS="-I$(abspath ..)" && \
		make -j$$(nproc) && make install; \
	else \
		echo "libcmaes already installed."; \
	fi

$(TARGET): $(SOURCES) $(CEC2013_SRC)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) $(CEC2013_SRC) -o $(TARGET) $(LDFLAGS) $(LIBS)

clean:
	rm -rf $(BUILDDIR)

clean-all: clean
	@echo "Cleaning libcmaes..."
	@rm -rf ../libcmaes/build
