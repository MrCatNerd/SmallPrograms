.PHONY: default compile run clean

default: run

run: compile
	./OpenGLProject # executable name

compile: build
	cmake -B build -S .
	make -C build

clean:
	rm OpenGLProject
	rm compile_commands.json
	rm -r build
	rm CMakeCache.txt
	rm -r .cache


compile_commands.json: build
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B build -S .
	cp build/compile_commands.json .

build:
	@mkdir build

