# Compiler and common flags
CXX = g++
COMMON_CFLAGS = -Wall -fdiagnostics-color=auto
LIBS = -lglfw -lGLEW -lGLU -lGL

# Specific flags for different build profiles
CFLAGS_NORMAL = $(COMMON_CFLAGS) -O2
CFLAGS_DEBUG = $(COMMON_CFLAGS) -Og -g -fstack-protector
CFLAGS_RELEASE = $(COMMON_CFLAGS) -O2 -finline-functions -march=native -fno-strict-aliasing
CFLAGS_FAST = $(COMMON_CFLAGS) -Ofast -finline-functions -march=native \
    -funroll-loops -ftree-vectorize -fprofile-generate -flto \
    -ffast-math -fno-math-errno -fuse-linker-plugin -fomit-frame-pointer \
    -fno-strict-aliasing

# Source files and executable
SRC = main.cpp
EXECUTABLE = bin/main

.PHONY: all clean run-normal run-debug run-fast run-release

# aliases
.PHONY: r run rund runf runr

# Default target
all: normal debug fast release

r: run-debug
run: run-normal
rund: run-debug
runf: run-fast
runr: run-release

# Create bin directory
bin:
	mkdir -p bin

main.cpp:
	touch main.cpp --no-create


# Build rules with lowercase as first argument and uppercase as second argument
define build_rule
$(1): bin $(SRC)
	$$(CXX) $($(2)) $(SRC) -o $$(EXECUTABLE)_$(1) $$(LIBS)
endef

$(foreach target, normal debug fast release, $(eval $(call build_rule,$(target),CFLAGS_$(shell echo $(target) | tr '[:lower:]' '[:upper:]'))))


# Run rules
define run_rule
run-$(1): $(1)
	./$$(EXECUTABLE)_$(1)
endef

$(foreach target, normal debug fast release, $(eval $(call run_rule,$(target))))

# Clean rules
define clean_rule
clean-$(1):
	rm -f $$(EXECUTABLE)_$(1)
endef

$(foreach target, normal debug fast release, $(eval $(call clean_rule,$(target))))

clean: clean-normal clean-debug clean-fast clean-release


