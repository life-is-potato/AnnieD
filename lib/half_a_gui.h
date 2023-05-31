#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


void cleanup(SDL_Surface* screen, SDL_Surface* textSurface, TTF_Font* font);

void renderText(SDL_Surface* screen,SDL_Surface* textSurface, TTF_Font* font,int textLength, char* text);


char* textgui(SDL_Surface* screen);
