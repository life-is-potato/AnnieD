all: compile_app debug_app

compile_app:
	gcc -D_FORTIFY_SOURCE=2 -fsanitize=address lib/*.c *.c -o run.exe -L"C:\MinGW\lib\SDL*" -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -g
debug_app:
	gdb ./run