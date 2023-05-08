#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#define SCREEN_H 800
#define SCREEN_W 1200



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
void generate_afficher (int *alea) ; 
void afficherEnigme(enigme e, SDL_Surface * screen); 
int resolution (int * running,int *run); 
void afficher_resultat (SDL_Surface * screen,int s,int r,enigme *en);

void initexte(text *t);
void displayText(text t,SDL_Surface *screen,char cc[30]);

void jouerEnigme(SDL_Surface *screen, int *state);	

#endif

