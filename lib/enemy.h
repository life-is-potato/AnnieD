#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "img.h"
#include "character.h"

typedef struct
{
    img sprite, spritemirrored;
    float x_spd, y_spd;
    int direction;
    int wlk_spd;
    int frame_width, frame_height;
    int framestart;
    int frames;
    int facing;
    int random;
    int chasing;
    SDL_Rect framepos;
} enemy;

void enemy_create(enemy *p, char *spritesheet,int x,int y);

int enemy_calculate_direction(enemy *e,player p, player p2);

void enemy_calculate_speed(enemy *p,player p1,player p2);

int enemy_check_collision(enemy *p, camera cam, int size, img *tiles);

void enemy_pos_update(enemy *p);

void enemy_step(enemy *p, camera cam, player p1, player p2, img *tiles, int size);

void enemy_animate(enemy *p);

void enemy_draw(enemy p, SDL_Surface *screen, camera cam,int a, int mode);

int player_ennemy_colliding(player p, enemy e);