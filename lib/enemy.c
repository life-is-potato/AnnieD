#include "functions.h"
#include <math.h>
#include "enemy.h"
#include <stdlib.h>
#include <time.h>

void enemy_create(enemy *p, char *spritesheet,int x,int y)
{
    srand(time(NULL));
    load_img(&p->sprite, "img/skander_walking-export-sheet.png", x, y);
    load_img(&p->spritemirrored, "img/skander_walking-export-sheet-mirrored.png", 100, 100);
    p->direction = 1;
    p->facing = 1;
    p->wlk_spd = 3;
    p->frame_height = 62;
    p->frame_width = 36;
    p->framepos.y = 0;
    p->framepos.x = 0;
    p->framepos.h = p->frame_height;
    p->framepos.w = p->frame_width;
    p->framestart = 0;
    p->frames = 0;
    p->chasing=0;
}

int enemy_calculate_direction(enemy *e,player p, player p2)
{   
    if(p.sprite.pos.x<(e->facing)*600+e->sprite.pos.x && p.sprite.pos.x>e->sprite.pos.x && p.sprite.pos.y<e->sprite.pos.y+200 && p.sprite.pos.y>e->sprite.pos.y-200 
    &&p2.sprite.pos.x<(e->facing)*600+e->sprite.pos.x && p2.sprite.pos.x>e->sprite.pos.x && p2.sprite.pos.y<e->sprite.pos.y+200 && p2.sprite.pos.y>e->sprite.pos.y-200){
        float p1_distance=sqrt((p.sprite.pos.x-e->sprite.pos.x)*(p.sprite.pos.x-e->sprite.pos.x)+(p.sprite.pos.y-e->sprite.pos.y)*(p.sprite.pos.y-e->sprite.pos.y));
        float p2_distance=sqrt((p2.sprite.pos.x-e->sprite.pos.x)*(p2.sprite.pos.x-e->sprite.pos.x)+(p2.sprite.pos.y-e->sprite.pos.y)*(p2.sprite.pos.y-e->sprite.pos.y));
        if (p1_distance<p2_distance)e->chasing=1;
        else e->chasing=2;
    }
    else if(p.sprite.pos.x<=(e->facing)*600+e->sprite.pos.x && p.sprite.pos.x>=e->sprite.pos.x && p.sprite.pos.y<=e->sprite.pos.y+200 && p.sprite.pos.y>=e->sprite.pos.y-200){
        e->chasing=1;    
    }
    else if(p2.sprite.pos.x<=(e->facing)*600+e->sprite.pos.x && p2.sprite.pos.x>=e->sprite.pos.x && p2.sprite.pos.y<=e->sprite.pos.y+200 && p2.sprite.pos.y>=e->sprite.pos.y-200){
        e->chasing=2;    
    }
    if(e->chasing==1){
        if(p.sprite.pos.x>200+e->sprite.pos.x || p.sprite.pos.x<e->sprite.pos.x-200 || p.sprite.pos.y>e->sprite.pos.y+200 || p.sprite.pos.y<e->sprite.pos.y-200){
        e->chasing=0;    
        }
        if(p.sprite.pos.x>e->sprite.pos.x){
            e->facing=1;
            e->direction=1;
        }
        else {
            e->facing=-1;
            e->direction=-1;
        }
    }
    else if(e->chasing==2){
        if(p2.sprite.pos.x>200+e->sprite.pos.x || p2.sprite.pos.x<e->sprite.pos.x-200 || p2.sprite.pos.y>e->sprite.pos.y+300 || p2.sprite.pos.y<e->sprite.pos.y-300){
        e->chasing=0;    
        }
        if(p2.sprite.pos.x>e->sprite.pos.x){
            e->facing=1;
            e->direction=1;
        }
        else {
            e->facing=-1;
            e->direction=-1;
        }
    }
    else{
    e->random = rand();
    if (e->direction != 0)
    {
        if (e->random % 500 <= 5)
        {
            e->direction = 0;
        }
        else if (e->random % 500 == 11)
        {
            e->direction = -e->direction;
        }
    }
    else
    {
        if (e->random % 150 == 0)
            e->direction = 1;
        else if (e->random % 150 == 1)
            e->direction = -1;
    }
    }
    return(0);
}

void enemy_calculate_speed(enemy *p,player p1,player p2)
{
    enemy_calculate_direction(p,p1,p2);
    if (abs(p->x_spd) > 0.1)
        p->x_spd *= 0.8;
    else
        p->x_spd = 0;
    if (p->direction != 0)
        p->facing = p->direction;
    p->x_spd += (p->direction * p->wlk_spd) / 3;
    p->y_spd += GRV;
    if (p->y_spd > 20)
        p->y_spd = 20;
    if (abs(p->x_spd) > p->wlk_spd)
        p->x_spd = p->direction * p->wlk_spd;
}

int enemy_check_collision(enemy *p, camera cam, int size, img *tiles)
{
    int i = 0;
    SDL_Rect pl = p->sprite.pos;
    pl.h = p->frame_height;
    pl.w = p->frame_width;
    for (i = 0; i < size; i++)
    {
        tiles[i].pos.w = tiles[i].image->w;
        tiles[i].pos.h = tiles[i].image->h;
        if (rect_meeting(p->x_spd + p->sprite.pos.x, p->sprite.pos.y, pl, tiles[i].pos))
        {
            p->direction=-p->direction;
            if (tiles[i].pos.x > pl.x)
                p->sprite.pos.x = tiles[i].pos.x - p->frame_width;
            else
                p->sprite.pos.x = tiles[i].pos.x + tiles[i].pos.w;
            p->x_spd = 0;
            p->sprite.pos.x += p->x_spd;
        }
        if (rect_meeting(p->sprite.pos.x, p->y_spd + p->sprite.pos.y, pl, tiles[i].pos))
        {
            if (tiles[i].pos.y > pl.y)
                p->sprite.pos.y = tiles[i].pos.y - p->frame_height;
            else
                p->sprite.pos.y = tiles[i].pos.y + tiles[i].pos.h;
            p->y_spd = 0;
            p->sprite.pos.y += p->y_spd;
        }
    }
    /*if(p->y_spd+p->sprite.pos.y>GROUND){
        p->sprite.pos.y=GROUND;
        p->y_spd=0;
    }
    else if(p->y_spd+p->sprite.pos.y<0){
        p->sprite.pos.y=0;
        p->y_spd=0;
    }
    if(p->x_spd+p->sprite.pos.x + p->framepos.w >SCREEN_W){
        p->sprite.pos.x=SCREEN_W-p->framepos.w;
        p->x_spd=0;
        p->direction=-p->direction;
    }
    else if(p->x_spd+p->sprite.pos.x<0){
        p->sprite.pos.x=0;
        p->x_spd=0;
        p->direction=-p->direction;
    }*/
}

void enemy_pos_update(enemy *p)
{
    p->sprite.pos.x += p->x_spd;
    p->sprite.pos.y += p->y_spd;
}

void enemy_step(enemy *p, camera cam, player p1, player p2, img *tiles, int size)
{
    enemy_calculate_speed(p,p1,p2);
    enemy_check_collision(p, cam, size, tiles);
    enemy_pos_update(p);
    enemy_animate(p);
}

void enemy_animate(enemy *p)
{

    if (p->y_spd > 2)
    {
        p->framepos.x = p->frame_width*5;
        p->framepos.y = 0;
    }
    else
    {
        if (p->x_spd == 0 && p->y_spd == 0)
        {
            if (p->frames % 40 >= 19)
            {
                p->framepos.y = 0;
                p->framepos.x = 0;
            }
            else
            {
                p->framepos.y = 0;
                p->framepos.x = p->frame_width*6;
            }
            p->frames++;
        }
        if (abs(p->x_spd) > 1 && p->y_spd == 0)
        {
            if (p->frames - p->framestart >= 4)
            {
                p->framepos.y = 0;
                p->framepos.x = (p->framepos.x + p->frame_width) % 5*p->frame_width;
                p->frames = 0;
            }
            p->frames++;
        }
    }
}

void enemy_draw(enemy p, SDL_Surface *screen, camera cam, int a, int mode)
{
    p.sprite.pos.x -= cam.x - (SCREEN_W+ ((float)a/2)*SCREEN_W) / 2/mode;
    p.sprite.pos.y -= cam.y - SCREEN_H / 2;
    if (p.facing != -1)
        SDL_BlitSurface(p.sprite.image, &p.framepos, screen, &p.sprite.pos);
    else
    {
        p.sprite.pos.x -= 10;
        SDL_BlitSurface(p.spritemirrored.image, &p.framepos, screen, &p.sprite.pos);
    }
}

int player_ennemy_colliding(player p, enemy e){
    SDL_Rect pl = p.sprite.pos;
    SDL_Rect el= e.sprite.pos;
    pl.h = p.frame_height;
    pl.w = p.frame_width;
    el.h = e.frame_height;
    el.w = e.frame_width;
    if (rect_meeting(p.x_spd + p.sprite.pos.x, p.sprite.pos.y + p.y_spd, pl, el))
        return 1;
    return 0;
}