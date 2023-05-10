#include "functions.h"

typedef struct 
{
    SDL_Surface *img,*timer[10];
    SDL_Rect p,pos_timer; 
    int reponsevrai; 
    int reponsejoueur;
    int num_enigme; 

}enigme;

typedef struct 
{ 
SDL_Rect position;
	TTF_Font *font;
	SDL_Surface * surfaceTexte;
	SDL_Color textColor;
	char texte [50];
}text;

void init_enigme(enigme * e, char *nomfichier); 

void afficherEnigme(enigme e, SDL_Surface * screen); 

int enigme_play(SDL_Surface* screen);