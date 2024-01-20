.PHONY: all clean

SHELL = /bin/sh
CFLAGS = -Wall -Werror
objects = obj/main.o obj/linked_list.o

all: bin/main
	./bin/main

clean:
	rm bin/*
	rm obj/*.o

bin/main: $(objects)
	gcc $(CFLAGS) $(objects) -o bin/main

obj/main.o: main.c  obj
	gcc $(CFLAGS) -c main.c -o obj/main.o

obj/linked_list.o: linked_list.c  obj
	gcc $(CFLAGS) -c linked_list.c -o obj/linked_list.o

bin:
	mkdir -p bin

obj:
	mkdir -p obj
