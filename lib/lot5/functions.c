#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h> 
#include <time.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>  
#include <SDL/SDL_ttf.h>
#include "functions.h"



void generate_afficher (int *alea)
{
	int test=*alea ;
       srand(SDL_GetTicks());    

 	do
 	{
  		*alea = 1+ rand()%12; 
	}while(*alea==test); 
}



void init_enigme(enigme *e, char *nomfichier)
{ 
	int j,y;
	int i=1;
	char nomimage[20];
		

	e->p.x=0;
	e->p.y=0;
	e->img=NULL;
	 
	generate_afficher(&e->num_enigme);

	FILE *f=fopen("enigme.txt","r");
	if(f!=NULL)
	{

		while(fscanf(f,"%s %d\n",nomimage,&e->reponsevrai)!=EOF && i!=e->num_enigme)
		{
			i++;
		}
		e->img=IMG_Load(nomimage);
		fclose(f);
	}
	else printf("ERROR !");
	
	e->timer[0] =IMG_Load("timer/0.gif");
    	e->timer[1] =IMG_Load("timer/1.gif");
    	e->timer[2] =IMG_Load("timer/2.gif");
    	e->timer[3] =IMG_Load("timer/3.gif");
    	e->timer[4] =IMG_Load("timer/4.gif");
    	e->timer[5] =IMG_Load("timer/5.gif");
    	e->timer[6] =IMG_Load("timer/6.gif");
    	e->timer[7] =IMG_Load("timer/7.gif");
    	e->timer[8] =IMG_Load("timer/8.gif");
    	e->timer[9] =IMG_Load("timer/9.gif");

    	e->pos_timer.x = 560;
    	e->pos_timer.y= 14;
    	
    	for(i=0; i<10; i++)
    	{
        	if (e->timer[i]==NULL)
        	{
         	   printf ("erreurtimer");
        	    return ;
        	}


    	}
} 

 


void afficherEnigme(enigme e, SDL_Surface * screen)
{
	SDL_BlitSurface(e.img,NULL,screen,&e.p); 
}




/*int resolution (int *running,int *boucle )
{
        //Mix_Chunk *son; 
	SDL_Event event ;
        int r=0 ;
	SDL_PollEvent(&event);
	//son= Mix_LoadWAV( "click_effect.wav" );
	switch(event.type)
	{
		case SDL_QUIT:
			*running= 0 ;
              		*boucle = 0;
			break ;

       	case SDL_KEYDOWN :
            		switch( event.key.keysym.sym )
                	{
				case  SDLK_a:
					//Mix_PlayChannel( -1, son, 0 ); 
			   		r= 1;
			   		*running= 1 ;
			   		break ;
			   	case  SDLK_z:
					//Mix_PlayChannel( -1, son, 0 ); 
			   		r= 2;
			   		*running= 1 ;
			   		break;
			   	case SDLK_e:
					//Mix_PlayChannel( -1, son, 0 ); 
			   		r=3 ;
			   		*running= 1 ;
			   		break;
			   	case SDLK_r:
					//Mix_PlayChannel( -1, son, 0 ); 
			   		r=4 ;
			   		*running= 1 ;
			   		break;

			}
       		break ;
	}
  	return r ;
}*/


 void afficher_resultat (SDL_Surface * screen,int s,int r,enigme *en)
 {

 	if (r==s)
 	{
 		en->img=IMG_Load("win.jpg");
 		SDL_BlitSurface(en->img, NULL, screen, &(en->p)) ;
        SDL_Flip(screen);
        SDL_FreeSurface(en->img);
 	}
 	else
 	{
 		en->img=IMG_Load("lose.jpg");
 		SDL_BlitSurface(en->img, NULL, screen, &(en->p)) ;
        SDL_Flip(screen);
        SDL_FreeSurface(en->img);
 	}
 }
 
void initexte(text *A)
{
    A->position.x=610;
    A->position.y=30;
    A->textColor.r=255;
    A->textColor.g=255;
    A->textColor.b=255;

    A->font = TTF_OpenFont( "police.ttf", 20 );
}


void displayText(text t,SDL_Surface *screen,char cc[30])
{
    t.surfaceTexte = TTF_RenderText_Solid(t.font, cc, t.textColor );
    SDL_BlitSurface(t.surfaceTexte, NULL, screen,&t.position);
}

void jouerEnigme(SDL_Surface *screen, int *state)
{
	enigme  e;
	Mix_Music *music ; 
        e.num_enigme=-1;
	int s,r=0;
	int running=0;
	int alea;
	int boucle=1;
	char image[30]="";
	SDL_Event event;
	
	int t=0;
	time_t start,end;
    	start=clock();
    	char cc[20];
    	text tt;
	 

	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
	{
		printf("%s",Mix_GetError()); 
	}
	
	music = Mix_LoadMUS("sound.mp3");
	Mix_PlayMusic(music,-1); 
	
	init_enigme(&e,"enigme.txt");
	initexte(&tt);
	
	while(boucle)
	{
		
		
             	afficherEnigme(e,screen);
         
             	sprintf(cc, ":0%d", t);
             	SDL_BlitSurface (e.timer[t],NULL,screen,&e.pos_timer);
        	displayText(tt,screen,cc);
        	SDL_Flip(screen);
        
        	end=clock();
        	t=(end-start)/CLOCKS_PER_SEC;

        	if(t==10)
        	{
         	   running=1;
        	}

	     	SDL_PollEvent(&event);
        	switch(event.type)
        	{
            		case SDL_QUIT:
                		boucle = 0;
	        		break ;
        	}


        	  	
    		SDL_PollEvent(&event);
		//son= Mix_LoadWAV( "click_effect.wav" );
		switch(event.type)
		{
			case SDL_QUIT:
				running= 0 ;
              			boucle = 0;
				break ;

       		case SDL_KEYDOWN :
            			switch( event.key.keysym.sym )
                		{
					case  SDLK_a:
						//Mix_PlayChannel( -1, son, 0 ); 
			   			r= 1;
			   			running= 1 ;
			   			break ;
			   		case  SDLK_z:
						//Mix_PlayChannel( -1, son, 0 ); 
			   			r= 2;
			   			running= 1 ;
			   			break;
			   		case SDLK_e:
						//Mix_PlayChannel( -1, son, 0 ); 
			   			r=3 ;
			   			running= 1 ;
			   			break;
			   		case SDLK_r:
						//Mix_PlayChannel( -1, son, 0 ); 
			   			r=4 ;
			   			running= 1 ;
			   			break;

				}
       			break ;
       	}

			
      		while(running)
      		{
          		afficher_resultat(screen,e.reponsevrai,r,&e);
          
			SDL_WaitEvent(&event);
        		switch(event.type)
            		{
				case SDL_QUIT :
                        		running =0 ;
					boucle=0 ;
					break ;

            			case SDL_KEYDOWN :
					switch( event.key.keysym.sym )
                			{
	             				case  SDLK_ESCAPE: 
		        				running= 0;
		        				boucle=0;
			            			break;			   
			    		}
            		}
				
		}
 }
	 
      SDL_FreeSurface(screen);
      SDL_Quit();
}


