#include "mapmaker.h"

int mapmaker(SDL_Surface screen){
    int boucle = 1;
    img blackbar;
    load_img(&blackbar,)
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type){
            case SDL_QUIT:
                SDL_Quit();
                break;
            case SDL_MOUSEBUTTONDOWN:
                break; 
            case SDL_KEYDOWN:
                break;
        }
    }
}