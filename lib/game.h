#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "img.h"
#include "text.h"
#include "functions.h"
#include "mini.h"
#include "bg.h"
#define MAX_FPS 48

int gameloop(SDL_Surface* screen, char* level);
