#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct
{

	char *url;
	SDL_Rect pos_img_affiche; //Partie de l'image qui doit etre affichée
	SDL_Rect pos_img_ecran; //Position de l'image par rapport à l'écran
	SDL_Surface *img;
}image;


typedef struct
{
	SDL_Surface *txt;
	SDL_Rect pos_txt;
	SDL_Colour color_txt;
	TTF_Font *police;
}texte;
 	
//Image

void initialiser_image(image *imge,char path[],int x,int y);

void afficher_imageBMP(SDL_Surface *screen, image imge);
void afficher_image(SDL_Surface *screen, image imge);

// Audio

void initialiser_audio(Mix_Music *music);
void liberer_musique(Mix_Music *music);

void initialiser_audiobref(Mix_Chunk *music);
void liberer_musiquebref(Mix_Chunk *music);

// Texte

void initialiser_texte(texte *txte, char police[],int taille,int red,int green,int blue, int x, int y);
void afficher_texte(SDL_Surface *screen, texte txte,char message[]);
void liberer_texte(texte txte);

void afficher_texte2(SDL_Surface *screen, texte txte, int vol);

#endif

