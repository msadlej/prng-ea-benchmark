CXX = g++
CXXFLAGS = -fdiagnostics-color=always -g
BUILDDIR = build

.PHONY: all generators benchmarks algorithms clean clean-all

all: generators benchmarks algorithms

generators: $(BUILDDIR)/linear_congruential $(BUILDDIR)/mersenne_twister

benchmarks:
	@echo "Building CEC-2013..."
	@$(MAKE) -C CEC-2013
	@echo "Building CEC-2021..."
	@$(MAKE) -C CEC-2021

algorithms:
	@echo "Building L-SHADE..."
	@$(MAKE) -C L-SHADE
	@echo "Building CMA-ES..."
	@$(MAKE) -C CMA-ES

$(BUILDDIR)/linear_congruential: linear_congruential.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/mersenne_twister: mersenne_twister.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(BUILDDIR)
	@$(MAKE) -C CEC-2013 clean
	@$(MAKE) -C CEC-2021 clean
	@$(MAKE) -C L-SHADE clean
	@$(MAKE) -C CMA-ES clean
