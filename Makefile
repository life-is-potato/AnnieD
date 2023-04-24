all:
	gcc main1.c lib/img.c lib/text.c lib/functions.c lib/character.c lib/mini.c lib/enemy.c lot2/bg.c -o prog -lSDL -lSDL_ttf -lSDL -lSDL_image -lSDL_mixer -lm
clean:
	rm prog
