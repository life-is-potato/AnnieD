#ifndef TEXT_H
#define TEXT_H
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

typedef struct{
    SDL_Surface *text;
	SDL_Rect pos;
	SDL_Colour color;
	TTF_Font* font;
}txt;

void load_txt(txt* txt, int x, int y, int r, int g, int b, char* font, int size);
void print_txt(SDL_Surface* screen, txt* txt, char* message);
void free_txt(txt txt);

#endif