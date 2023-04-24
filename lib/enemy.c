#include "functions.h"
#include <math.h>
#include "enemy.h"
#include <stdlib.h>
#include <time.h>

void enemy_create(enemy *p,char* spritesheet){
    srand(time(NULL));
    load_img(&p->sprite,spritesheet,400,100);
    load_img(&p->spritemirrored,"img/Potato_walking-mirrored-export.png",100,100);
    p->direction=1;
    p->facing=1;
    p->wlk_spd=3;
    p->frame_height=48;
    p->frame_width=50;
    p->framepos.y=0;
    p->framepos.x=0;
    p->framepos.h=p->frame_height;
    p->framepos.w=p->frame_width;
    p->framestart=0;
    p->frames=0;
}

void enemy_calculate_direction(enemy* e){
    e->random=rand();
    if (e->direction!=0){
        if (e->random%500<=5){
            e->direction=0;
        }
        else if (e->random%500==11){
            e->direction=-e->direction;
        }
    }
    else{
        if(e->random%150==0)e->direction=1;
        else if(e->random%150==1)e->direction=-1;
    }
}

void enemy_calculate_speed(enemy* p){
    enemy_calculate_direction(p);
    if(abs(p->x_spd)>0.1)p->x_spd*=0.8;
    else p->x_spd=0;
    if (p->direction!=0) p->facing=p->direction;
    p->x_spd+=(p->direction * p->wlk_spd)/3;
    p->y_spd+=GRV;
    if(p->y_spd>20)p->y_spd=20;
    if(abs(p->x_spd)>p->wlk_spd)p->x_spd = p->direction* p->wlk_spd;
}

int enemy_check_collision(enemy* p,camera cam){
    if(p->y_spd+p->sprite.pos.y>GROUND){
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
    }
}

void enemy_pos_update(enemy* p){
    p->sprite.pos.x+=p->x_spd;
    p->sprite.pos.y+=p->y_spd;
}

void enemy_step(enemy* p, camera cam){
    enemy_calculate_speed(p);
    enemy_check_collision(p,cam);
    enemy_pos_update(p);
    enemy_animate(p);
}

void enemy_animate(enemy* p){

    if(p->y_spd>2){
        p->framepos.x=300;
        p->framepos.y=48;
    }
    else if(p->y_spd>4){
        p->framepos.x=350;
        p->framepos.y=48;
    }
    else {
        if(p->x_spd==0 && p->y_spd==0){
            if(p->frames%40>=19){
            p->framepos.y=0;
            p->framepos.x=0;
            }
            else {
                p->framepos.y=48;
                p->framepos.x=0;
                }
            p->frames++;
            }
        if(abs(p->x_spd)>1 && p->y_spd==0){
        if(p->frames-p->framestart>=4){
        p->framepos.y=0;
        p->framepos.x=(p->framepos.x+p->frame_width)%250;
        p->frames=0;
        }
        p->frames++;
        }
        }
}

void enemy_draw(enemy p, SDL_Surface* screen, camera cam){
    p.sprite.pos.x-=cam.x-SCREEN_W/2;
    p.sprite.pos.y-=cam.y-SCREEN_H/2;
    if(p.facing!=-1)SDL_BlitSurface(p.sprite.image,&p.framepos,screen,&p.sprite.pos);
    else {
        p.sprite.pos.x-=10;
        SDL_BlitSurface(p.spritemirrored.image,&p.framepos,screen,&p.sprite.pos);
        }
}