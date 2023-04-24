#ifndef MINI_H
#define MINI_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "img.h"
#include "enemy.h"
#include "text.h"
typedef struct {
    img img;
}minimap;
typedef struct {
    img img;
}miniplayer;
void init_minimap(minimap *mm, char *path, SDL_Surface *screen);
void init_miniplayer(miniplayer *mp, char *path);
void update_miniplayer(minimap *mm, miniplayer *mp, player* player, SDL_Surface *screen);
void update_time(int pause, minimap *mm, Uint32 *start_time, txt* timertxt,SDL_Surface* screen);
void update_minienemy(minimap *mm, miniplayer *mp, enemy *player, SDL_Surface *screen);
void minimap_maker(minimap *mm, SDL_Surface *screen, img *Tiles, int TilesNum, int pause);
#endif