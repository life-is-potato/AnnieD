CFLAGS = -Wall -Wextra -g `sdl-config --cflags`
LIBS = -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lm
CONF = `sdl-config --libs` 
CC = gcc
LDFLAGS = $(CONF) $(LIBS)

$(shell mkdir -p build)
$(shell mkdir -p build/obj)

all: AnnieD

build/obj/%.o: lib/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

build/obj/%.o: lib/lot5/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

build/obj/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

AnnieD: build/obj/main.o $(patsubst lib/%.c, build/obj/%.o, $(wildcard lib/*.c)) $(patsubst lib/lot5/%.c, build/obj/%.o, $(wildcard lib/lot5/*.c))
	$(CC) $(CFLAGS) $^ -o AnnieD $(LDFLAGS)

# Clean object files
clean:
	rm -f -r build