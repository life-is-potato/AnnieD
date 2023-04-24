#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_ttf.h>
#include "fonction.h"
#include "string.h"
int main()
{
	SDL_Surface *screen;
	SDL_Event event;
	texte *txte;
	Mix_Music *music;
	background b,image;
	int boucle=1;
	int a=0;
	int direction=0;
	TTF_Init();	
	char* fichier="filesecore";
	scoreinfo tab[3];
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)==-1)
	{
		printf("Could not initialize SDL : %s.\n",SDL_GetError());
		return -1;
	}
	screen=SDL_SetVideoMode(600,600,32,SDL_SWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
	initBack(&b);
	init_animerBack (& image, screen);
		while(boucle)
	{
		aficherBack( b, screen);
		affiche (&image,screen);
		animerBack( &image,&a);
		//meilleur_score(fichier,tab,screen);
		//initialiser_audio(music);
		while(SDL_PollEvent(&event))
		{    	
		 
			switch(event.type)
			{
				case SDL_KEYDOWN:
				    switch(event.key.keysym.sym)
				    {
				        case SDLK_RIGHT:
				            direction= 1;
				            break;
				            
				        case SDLK_LEFT:
				            direction= -1;
				            break;
				        case (SDLK_q):
					boucle=0;
					break;
					case SDLK_DOWN:
				            direction= 2;
				            break;
				        case SDLK_UP:
				            direction = -2;
				            break;
				    }
				    
				    break;
				    
				
				  
				case SDL_QUIT:
				boucle=0;
				break;	
			}
			
		}
		scrolling(&b,direction);
		SDL_Flip(screen); //Raffraichir l'ecran
	}
	
	//Libreation des surfaces
	
	SDL_QUIT;


return 0;
}
