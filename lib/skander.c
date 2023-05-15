#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "skander.h"

void initialiser_image(image *image, char path[],int x,int y)
{
	//Chargement de l'image
	(*image).url=path;
	(*image).img=IMG_Load((*image).url);
	if((*image).img==NULL)
	{
		printf("Unable to load background image %s \n",SDL_GetError());
	}
	(*image).pos_img_ecran.x=x;
	(*image).pos_img_ecran.y=y;
	(*image).pos_img_affiche.x=0;
	(*image).pos_img_affiche.y=0;
	(*image).pos_img_affiche.h=SCREEN_H;
	(*image).pos_img_affiche.w=SCREEN_W;
}

void afficher_imageBMP(SDL_Surface *screen,image imge)
{
	//Coller et afficher l'image du back dans screen
	SDL_BlitSurface(imge.img, &imge.pos_img_affiche, screen, &imge.pos_img_ecran);
}

void afficher_image(SDL_Surface *screen,image imge)
{
	SDL_BlitSurface(imge.img, NULL, screen, &imge.pos_img_ecran);
}




void initialiser_audio(Mix_Music *music)
{
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
	{
		printf("%s",SDL_GetError());
	}
	music=Mix_LoadMUS("music/fond.mp3");
	Mix_PlayMusic(music,-1); //Jouer la musique à l'infini
	Mix_VolumeMusic(MIX_MAX_VOLUME);
}

void liberer_musique(Mix_Music *music)
{
	Mix_FreeMusic(music);
}

void initialiser_audiobref(Mix_Chunk *music)
{
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	music=Mix_LoadWAV("music/button_sfx.wav");
	Mix_PlayChannel(1,music,0); 
	if(music==NULL) 
		printf("%s",SDL_GetError());
}

void liberer_musiquebref(Mix_Chunk *music)
{
	Mix_FreeChunk(music);
}

void initialiser_texte(texte *txte, char police[],int taille,int red,int green,int blue, int x, int y)
{
	TTF_Init(); //Initialiser SDL_ttf
	(*txte).police = TTF_OpenFont(police,taille);
	(*txte).color_txt.r=red;
	(*txte).color_txt.g=green;
	(*txte).color_txt.b=blue;
	(*txte).pos_txt.x=x;
	(*txte).pos_txt.y=y;
}


void afficher_texte(SDL_Surface *screen, texte txte, char message[])
{

	txte.txt=TTF_RenderText_Blended(txte.police,message,txte.color_txt);
	SDL_BlitSurface(txte.txt,NULL,screen,&txte.pos_txt);
}

void afficher_texte2(SDL_Surface *screen, texte txte, int vol)
{
	char tmp[20];
	sprintf(tmp,"%d",vol);
	txte.txt=TTF_RenderText_Blended(txte.police,tmp,txte.color_txt);
	SDL_BlitSurface(txte.txt,NULL,screen,&txte.pos_txt);
}

void liberer_texte(texte txte)
{
	SDL_FreeSurface(txte.txt);
	TTF_CloseFont(txte.police);
	TTF_Quit();
}
