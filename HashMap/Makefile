CC := gcc
# CFLAGS := -Wall -Wextra -pedantic -std=c99 -Og -g -fdiagnostics-color=auto
CFLAGS := -Wall -Wextra -pedantic -std=c99 -O0 -g -fdiagnostics-color=auto # for valgrind cuz -O0
LDFLAGS := -lm
OBJ_DIR := obj
BIN_DIR := bin

TARGET = $(BIN_DIR)/main

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

#=============================================================================
# Build
all: $(TARGET)
	./$(TARGET)
.PHONY: all

# A rule to build the targets
$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# A rule to build the object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
#=============================================================================
# Create stuff if it doesn't exist

# Directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

#=============================================================================
# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
.PHONY: clean

.DEFAULT_GOAL := all

