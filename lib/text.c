#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "text.h"

void load_txt(txt *txt, int x, int y, int r, int g, int b, char *font, int size){
    txt->font=TTF_OpenFont(font,size);
    txt->color.r=r;
    txt->color.g=g;
    txt->color.b=b;
    txt->pos.x=x;
    txt->pos.y=y;
}

void print_txt(SDL_Surface *screen, txt *txt, char *message){
    txt->text=TTF_RenderText_Blended(txt->font,message,txt->color);
    SDL_BlitSurface(txt->text,NULL,screen,&txt->pos);
}

void free_txt(txt txt){
    SDL_FreeSurface(txt.text);
	TTF_CloseFont(txt.font);
}