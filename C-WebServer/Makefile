# Compiler and common flags
CXX = gcc

# Specific flags for different build profiles
COMMON_CFLAGS = -Wall -fdiagnostics-color=auto
LIBS =

# Just a normal thingy
CFLAGS_NORMAL = $(COMMON_CFLAGS) -O2

# For debugging
CFLAGS_DEBUG = $(COMMON_CFLAGS) -Og -g -fstack-protector

# Optimized for release
CFLAGS_RELEASE = $(COMMON_CFLAGS) -O3 -fno-math-errno -fomit-frame-pointer -fno-strict-aliasing \
    -flto -fuse-linker-plugin

# Fast but unstable for release
CFLAGS_FAST = $(COMMON_CFLAGS) -Ofast -march=native -fno-math-errno -fomit-frame-pointer -fno-strict-aliasing \
    -flto -fuse-linker-plugin -fprefetch-loop-arrays -ftree-vectorize

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

#=============================================================================
# Source files and object files
SRCDIR = src
OBJDIR = obj
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
EXECUTABLE = bin/main

#=============================================================================
# Default target rule
default: run-debug
.PHONY: default

# Build all
all: normal debug fast release
.PHONY: all

#=============================================================================
# Build target rules
define build_rule
$(1): bin $(OBJDIR) $(OBJ)
	$$(CXX) $($(2)) $(OBJ) -o $$(EXECUTABLE)_$(1) $$(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$$(CXX) -c $$< -o $$@ $($(2))
endef

$(foreach target, normal debug fast release, $(eval $(call build_rule,$(target),CFLAGS_$(shell echo $(target) | tr '[:lower:]' '[:upper:]'))))

#=============================================================================
# Run target rules
define run_rule
run-$(1): $(1)
	./$$(EXECUTABLE)_$(1)
endef

$(foreach target, normal debug fast release, $(eval $(call run_rule,$(target))))

.PHONY: run-normal run-debug run-fast run-release

# Run aliases
r: run-debug
run: run-normal
rund: run-debug
runf: run-fast
runr: run-release
.PHONY: r run rund runf runr

#=============================================================================
# Clean rules
define clean_rule
clean-$(1):
	rm -f $$(EXECUTABLE)_$(1)
endef

$(foreach target, normal debug fast release, $(eval $(call clean_rule,$(target))))

clean:
	rm -rf bin
	rm -rf $(OBJDIR)

.PHONY: clean clean-normal clean-debug clean-fast clean-release clean-obj

#=============================================================================
# Create stuff if not existing

# Directories
bin:
	mkdir -p bin

$(OBJDIR):
	mkdir -p $(OBJDIR)

