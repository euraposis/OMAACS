OMAACS_NUM_PATH = libs/OMAACS_NUM/OMAACS_NUM/src

all:
	mkdir -p build
	clang src/main.c $(OMAACS_NUM_PATH)/vector.c -o build/OMAACS -lm -I src/Interface -I src/OrbitalMechanics -I libs/OMAACS_NUM/OMAACS_NUM/src

clean:
	rm -rf build/OMAACS