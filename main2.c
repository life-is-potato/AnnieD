#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "lib/img.h"
#include "lib/text.h"
#include "lib/functions.h"
#include "lib/mini.h"
#include "lib/bg.h"
#include "lib/game.h"
// #include "lib/enemy.h"
#define MAX_FPS 60

int main()
{
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    if (init() == -1)
    {
        return -1;
    }
    gameloop(screen);
    SDL_Quit();
}