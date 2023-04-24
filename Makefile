CFLAGS = -Wall -Wextra -g `sdl-config --cflags`
LIBS = -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lm
CONF = `sdl-config --libs` 
CC = gcc
LDFLAGS = $(CONF) $(LIBS)
$(shell mkdir -p obj)

all: AnnieD

obj/%.o: lib/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

obj/main1.o: main1.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

lot2/bg.o: lot2/bg.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

AnnieD: obj/main1.o lot2/bg.o $(patsubst lib/%.c, obj/%.o, $(wildcard lib/*.c))
	$(CC) $(CFLAGS) $^ -o AnnieD $(LDFLAGS)

# Clean object files
clean:
	rm -f -r .o* obj/
cleanall:
	rm -f -r .*o obj/ AnnieD