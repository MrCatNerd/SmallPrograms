.PHONY: default clean

default: bin obj
	touch main.c --no-create

	gcc -c main.c -o obj/main.o
	gcc -c solution.c -o obj/solution.o
	gcc obj/main.o obj/solution.o -o bin/main

	./bin/main

clean: bin
	rm -rf bin
	rm -rf obj

obj:
	mkdir -p obj

bin:
	mkdir -p bin
