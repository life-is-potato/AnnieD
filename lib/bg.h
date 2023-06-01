#ifndef FONCTION_H
#define FONCTION_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <SDL/SDL_mixer.h> 
#include <SDL/SDL_ttf.h> 	
#include "./img.h"
#include "skander.h"
typedef struct 
{
    char *url;
    SDL_Rect camera_pos;
    SDL_Rect pos_ecran;
    SDL_Surface *affichebackground;
    int speed;
    int level;
    SDL_Surface *img;
}background;
typedef struct
{
	Mix_Music *music;
	int vol;
}music;
typedef struct 
{
	int score;
	int temps;
	char playername[30];
}scoreinfo;

void init_animerBack (background* image);
void initBack(background * b);
void aficherBack(background b, SDL_Surface * screen);
void scrolling (background * b, int direction ); 
void animerBack (img* b,int* a) ;
void affiche (background* image,SDL_Surface* screen);
void liberer_image(background b);
void savescore(scoreinfo s,char filename[]);
void meilleur_score(char filename[],scoreinfo tab[],SDL_Surface *screen);
#endif //CODE_SOURCE_FONCTION_H
