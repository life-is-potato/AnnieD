#include <SDL/SDL.h>
#include <SDL/SDL_image.h> //Pour manipuler des images
#include <SDL/SDL_mixer.h> //Pour manipuler audio
#include <SDL/SDL_ttf.h> //Pour manipuler des textes
#include "bg.h"
#include "img.h"
#include "functions.h"
void initBack(background * b)
{
    b->affichebackground=IMG_Load("../img/background.jpg");
    if(b->affichebackground == NULL)
    {
        printf("Unable to load background image %s \n",SDL_GetError());
        return ;
    }
    b->camera_pos.x=0;
    b->camera_pos.y=0;
    b->camera_pos.w=600;
    b->camera_pos.h=860;
    b->pos_ecran.x=0;
    b->pos_ecran.y=0;
    b->pos_ecran.h=SCREEN_H;
    b->pos_ecran.w=SCREEN_W;
}
void aficherBack(background b, SDL_Surface * screen)
{
    SDL_BlitSurface(b.affichebackground,&(b.camera_pos),screen,&(b.pos_ecran));
}
void scrolling (background * b, int direction )
{
	if(direction==-1)
		b->camera_pos.x--;
	else
	
		if(direction==1){
			b->camera_pos.x++;}
		else 
		
			if(direction==2){
				b->camera_pos.y++;}
			else
			
				if(direction==-2){
				b->camera_pos.y--;
			}	
}

void init_animerBack (background* image,SDL_Surface * screen)
{
	image->img=NULL;
    image->url="../img/object.png";
    image->img=IMG_Load(image->url);  
    if(image->img == NULL)
    {
        printf("Unable to load background image %s \n",SDL_GetError());
        return ;
    }
    image->camera_pos.x=10;
    image->camera_pos.y=10;
    
    image->pos_ecran.x=0;
    image->pos_ecran.y=0;
    image->pos_ecran.h=image->img->h/1;
    image->pos_ecran.w=image->img->w/4;
    
    
 }
void animerBack(img* b,int* a)
{
     if (b->pos.x <= (SCREEN_W-b->image->w) && (*a)==0) 
         b->pos.x += 1;
     if(b->pos.x == (SCREEN_W-b->image->w))
         (*a)=1;
     if (b->pos.x <= (SCREEN_W - b->image->w) && (*a)==1)
     	b->pos.x -= 1;
     if(b->pos.x == 0)
         (*a)=0;
  
}

 void affiche (background* image,SDL_Surface* screen)
 {
     SDL_BlitSurface(image->img,NULL,screen,&image->camera_pos);
 }
 void liberer_image(background b){
    SDL_FreeSurface(b.img);
}
void savescore(scoreinfo s,char filename[])
 {
 	FILE* pf=NULL;
 	pf=fopen(filename,"a");
 	if (pf!=NULL)
 	{
 		fprintf(pf,"%s %d %d",s.playername,s.temps,s.score);
 		fclose(pf);
 	}
 }
void meilleur_score(char filename[],scoreinfo tab[],SDL_Surface *screen)
{
	char message[100];
	texte txte;
 	int i=0;
 	int j,permut,aux; 
 	scoreinfo s;
 	FILE* pf=NULL;
 	pf=fopen(filename,"r");
 	if (pf!=NULL)
 	{
 		while (!feof(pf))
        	{
            		fscanf(pf,"%s %d %d\n",s.playername,&s.temps,&s.score);
            		strcpy(tab[i].playername,s.playername); 	
            		tab[i].temps=s.temps;
            		tab[i].score=s.score;
            		i++;
            	}
            	fclose(pf);
 	}
 	do
	{
		permut = 0;
		for( j=0; j<i-1; j++)
		{
			if (tab[j].score>tab[j+1].score)
			{
				aux = tab[j].score;
				tab[j].score = tab[j+1].score;
				tab[j+1].score= aux ;
				permut = 1;
			}
		}
	}while (permut == 1);	
	
	TTF_Init(); //Initialiser SDL_ttf
	txte.police = TTF_OpenFont("../fonts/pixel_arial.ttf",46);
	txte.color_txt.r=255;
	txte.color_txt.g=0;
	txte.color_txt.b=0;
	txte.pos_txt.x=50;
	txte.pos_txt.y=50;
	strcpy (message,tab[1].playername);
	txte.txt=TTF_RenderText_Blended(txte.police,message,txte.color_txt);
	SDL_BlitSurface(txte.txt,NULL,screen,&txte.pos_txt);
}
