#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "functions.h"
#include <math.h>
int init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1)
    { 
        printf("Could not initialize SDL : %s.\n", SDL_GetError());
        return -1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("Could not open audio : %s\n", SDL_GetError());
        return -1;
    }
    if (TTF_Init() == -1)
    {
        printf("Could not initialize TTF : %s.\n", SDL_GetError());
        return -1;
    }
    return 1;
}

int check_mouse_collision(img img)
{
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    if (mx >= img.pos.x && mx <= img.pos.x + img.image->w && my >= img.pos.y && my <= img.pos.y + img.image->h)
        return (1);
    return (0);
}

int check_point_collision(img img, int x, int y)
{
    if (x >= img.pos.x && x <= img.pos.x + img.image->w && y >= img.pos.y && y <= img.pos.y + img.image->h)
        return (1);
    return 0;
}

int check_button_change(img img, int x, int y)
{
    // checks if the button currently pressed changed, for sound playing purposes
    if (check_mouse_collision(img) != check_point_collision(img, x, y))
        return 1;
    return 0;
}

int place_meeting(SDL_Rect rect1, SDL_Rect rect2)
{
    if (rect1.x - rect2.x <= rect2.w && rect1.y - rect2.y <= rect2.h)
        return (1);
    if (rect1.x + rect1.w - rect2.x <= rect2.w && rect1.y - rect2.y <= rect2.h)
        return (1);
    if (rect1.x - rect2.x <= rect2.w && rect1.y + rect1.h - rect2.y <= rect2.h)
        return (1);
    if (rect1.x + rect1.w - rect2.x <= rect2.w && rect1.y + rect1.h - rect2.y <= rect2.h)
        return (1);
    return (0);
}