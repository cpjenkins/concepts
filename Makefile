# a makefile.
INCDIRS := -Iinc/

# compiler configuration
CXXOPTS := -std=c++11 -O3 -Wall -Wextra $(INCDIRS) $(CXXOPTS)

# debug, if requested
ifeq ($(DEBUG),1)
    override CXXOPTS += -g3 -O0
endif

# enable fast math on gcc - yolo
ifeq ($(CXX),g++)
    override CXXOPTS +=-ffast-math
endif

PROJECT_NAME := concepts
PROJECT_HELP := "a collection of concepts"

# compile programs
PROGRAMS := $(patsubst src/%.cc, bin/%, $(shell echo `find src/ | grep .cc$$`))

# dependency configuration
DEPDIR := .deps
DEPOPT  = -MT $@ -MM -MP -MF $(DEPDIR)/$*.d

# make sure $(DEPDIR) and bin exist
$(shell mkdir -p $(DEPDIR) >/dev/null)
$(shell mkdir -p bin >/dev/null)

#---[ define targets

## (default target) build everything
all: $(PROGRAMS) benchmarks  

include bench/Makefile.bench

# generic c++ target
bin/% : src/%.cc Makefile $(DEPDIR)/%.d
	@$(CXX) $(CXXOPTS) $(DEPOPT) $<
	$(CXX) $(CXXOPTS) $< -o $@ $(LDOPTS)

# ---[ remove dependency info
depclean: 
	@rm -rf $(DEPDIR)

# remove normal build artifacts (not deps)
clean: bench_clean
	@rm -f $(PROGRAMS)
	@rm -f $(LIBRARIES)
	@rm -f build.log	

# clean it with fire
purge: clean depclean             

# include dependency info
$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d
-include $(wildcard $(patsubst bin/%,$(DEPDIR)/%.d,$(PROGRAMS)))
