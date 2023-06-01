#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "img.h"
#include "character.h"

void enemy_create(enemy *p, /*char *spritesheet*/int x,int y);

int enemy_calculate_direction(enemy *e,player p, player p2);

void enemy_calculate_speed(enemy *p,player p1,player p2);

void enemy_check_collision(enemy *p, int size, img *tiles);

void enemy_pos_update(enemy *p);

void enemy_step(enemy *p, player p1, player p2, img *tiles, int size);

void enemy_animate(enemy *p);

void enemy_draw(enemy p, SDL_Surface *screen, camera cam,int a, int mode);

int player_ennemy_colliding(player p, enemy e);