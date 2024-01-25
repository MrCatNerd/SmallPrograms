CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Og -g
LDFLAGS = -lm
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/main

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

.PHONY: all clean

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

main.cpp:
	touch main.cpp --no-create #to rebuild every time

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.DEFAULT_GOAL := all

