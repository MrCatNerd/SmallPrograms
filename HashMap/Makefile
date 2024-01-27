CC = gcc
# CFLAGS = -Wall -Wextra -pedantic -std=c99 -Og -g -fdiagnostics-color=auto
CFLAGS = -Wall -Wextra -pedantic -std=c99 -O0 -g -fdiagnostics-color=auto # for valgrind cuz -O0
LDFLAGS = -lm
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/main

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

.PHONY: all clean

all: $(TARGET)
	touch main.c --no-create # to rebuild every time
	./$(TARGET)

$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.DEFAULT_GOAL := all

