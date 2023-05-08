prog:functions.o main.o
	gcc functions.o main.o -o prog -g -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer 
main.o:main.c 
	gcc -c main.c -g
functions.o:functions.c 
	gcc -c functions.c -g
