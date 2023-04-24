#ifndef IMG_H
#define IMG_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

typedef struct{
    SDL_Rect pos;
    SDL_Surface* image;
}img;

void load_img(img* img, char* path, int x, int y);
void display_img(SDL_Surface* screen, img img);
void free_img(img img);

#endif