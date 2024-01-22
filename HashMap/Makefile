.PHONY: all clean

SHELL := /bin/sh
CC := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Werror -pedantic -g -fsanitize=address
objects := obj/main.o obj/linked_list.o obj/hashmap.o
executable := bin/main

all: $(executable)
	@./$(executable)

clean:
	@rm -rf bin obj

$(executable): $(objects) | bin
	@$(CC) $(CXXFLAGS) $(objects) -o $(executable)

obj/%.o: %.cpp | obj
	@$(CC) $(CXXFLAGS) -c $< -o $@

bin obj:
	@mkdir -p $@

