all:
	clang src/main.c -o build/OMAACS

clean:
	rm -rf build/OMAACS