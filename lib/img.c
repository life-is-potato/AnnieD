#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "img.h"


void load_img(img* img, char* path, int x, int y){
    img->image=IMG_Load(path);
    if(img->image==NULL)printf("Unable to load background image %s \n",SDL_GetError());
    img->pos.x=x;
    img->pos.y=y;
}

void display_img(SDL_Surface *screen, img img){
    SDL_BlitSurface(img.image,NULL,screen,&img.pos);
}

void free_img(img img){
    SDL_FreeSurface(img.image);
}