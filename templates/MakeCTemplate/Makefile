# TODO: cmake style ordering and comments thingy

# Specify the shell explicitly
SHELL := /bin/sh

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99
LIBS :=

# Directories
OBJ_DIR := obj
BIN_DIR := bin
TARGET := $(BIN_DIR)/main

# Find source and object files
SRC_FILES := $(wildcard *.c)
OBJ_FILES := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Phony targets
.PHONY: all clean run

# Default target
.DEFAULT_GOAL := all

# Rule to build all
all: $(TARGET)

# Rule to link object files into executable
$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean target
clean:
	-rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run target
run: $(TARGET)
	./$(TARGET)

