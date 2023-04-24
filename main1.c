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
#include "lot2/bg.h"
//#include "lib/enemy.h"
#define MAX_FPS 60
int main(){
SDL_Surface* screen;
SDL_Event event;
int boucle=1;
char* spritesheet1="img/Potato_walking-export.png";
char* spritesheet2="img/Potato_walking-export.png";
char* minimappath="smol_bg.png";
char* miniplayerpath="smol.png";
camera cam;
cam.x=0;
cam.y=0;
minimap mm;
miniplayer mp,mp2,me;
player p1,p2;
img bg,dummy,nothing;
txt timertxt;
int starttime;
int endtime=0;
float wait;
float deltat;
Uint32 time=0;


//Intializing SDL
if(init()==-1){
    return -1;
}


TTF_Init();
txt frm,frm2,frm3;
char xspd[20],yspd[20],frames[20];
load_txt(&frm,100,100,0,0,0,"pixel_arial.ttf",20);
load_txt(&frm2,100,150,0,0,0,"pixel_arial.ttf",20);
load_txt(&frm3,100,200,0,0,0,"pixel_arial.ttf",20);
load_txt(&timertxt, 10, 10, 0, 255, 0, "fonts/pixel_arial.ttf", 50);
screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
init_minimap(&mm, minimappath,screen);
init_miniplayer(&mp, miniplayerpath);
init_miniplayer(&mp2,miniplayerpath);
init_miniplayer(&me, miniplayerpath);
player_create(&p1,spritesheet1);
player_create2(&p2,spritesheet2);
enemy urmom;
/*char tab[9][9]={
    {1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1}
};*/
static img tm[50];
int size=0;
parse_tiles("map.txt",tm,&size);
enemy_create(&urmom,spritesheet1);
load_img(&bg,"lot2/background.jpg",0,0);
load_img(&dummy,"lot2/background.jpg",0,0);
load_img(&nothing,"void.png",-1000,-1000);
img car;
load_img(&car,"lot2/object.png",100,100);
int k=0;
if(screen==NULL)return -1;


while(boucle){

    //commentaires en français pour Skander <3

    starttime=SDL_GetTicks();
    players_get_inputs(&p1,&p2,&boucle);

    //Execute la logique des joueurs et des ennemis, et met à jour la position de la camera

    player_step(&p1,cam,tm,size);
    player_step(&p2,cam,tm,size);
    enemy_step(&urmom,cam,tm,size);
    update_camera(p1.sprite,p2.sprite,&cam); 
    
    //Dessine les arrière-plans, les ennemis, les joueurs, et les objets

    bg.pos.x=-(cam.x-SCREEN_W/2);
    bg.pos.y=-(cam.y-SCREEN_H/2);
    SDL_BlitSurface(nothing.image, NULL, screen, &nothing.pos);
    display_img(screen,bg);
    animerBack(&car,&k);
    display_sprite(screen,car,cam);
    display_tiles(screen,tm,cam,size);
    player_draw(p1,screen,cam);
    player_draw(p2,screen,cam);
    enemy_draw(urmom,screen,cam);
    SDL_BlitSurface(mm.img.image, NULL, screen, &dummy.pos);

    //Dessine la minimap

    update_miniplayer(&mm,&mp, &p1, screen);
    update_miniplayer(&mm,&mp2, &p2, screen);
    update_minienemy(&mm,&me,&urmom,screen);
    update_time(0,&mm,&time,&timertxt,screen);
    SDL_Flip(screen);
    endtime=SDL_GetTicks();
    deltat=(endtime-starttime)/(float)1000;
    wait=((float)1/(float)MAX_FPS)-deltat;
    if(wait>0) SDL_Delay(1000*wait);
    }
    SDL_FreeSurface(screen);
    free_img(bg);
    free_img(p1.sprite);
    free_img(p2.sprite);
    free_img(mp.img);
    free_img(mp2.img);
    free_img(dummy);
    free_img(nothing);
    free_txt(timertxt);
}