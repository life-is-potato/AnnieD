#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "lib/skander.h"
#include <math.h>
#include "lib/functions.h"
#include "lib/xo_header.h"
#include "lib/game.h"
#include "lib/enigme.h"

#define SCREEN_H 720
#define SCREEN_W 1280

int main()
{
	int change_counter=0;
	SDL_Surface *screen;
	image IMAGE, IMAGE2, IMAGE_BTN1, IMAGE_BTN2, IMAGE_BTN3, IMAGE_BTN4, IMAGE_BTN5, IMAGE_BTN6, IMAGE_BTN7, IMAGE_BTN8, IMAGE_BTN9, IMAGE_BTN10, GAME_LOGO, BOULE, BARRE, FULLSCREEN,WINDOW, BACK;
	image SETTINGS_BACK;
	Mix_Music *music;
	FILE *f;
	Mix_Chunk *mus;
	texte txte,pourc,txte3,moins,moins2,plus,plus2,vol_set,start,fullscreen1,fullscreen2,window1,window2,controls1,controls2;
	SDL_Event event;
	
	texte player1,jump1,up1,down1,right1,left1,dash1;

	int boucle=1;
	int son=0;
	int buttonstate=0;
	int state=1;
	int pos_x,pos_y;
	int volume=MIX_MAX_VOLUME, count=100,count1;
	int k=0;
	int cpt1=0;
	int keyb=0;
	int max_volume=730, min_volume=440,pos_boule=730;
	


	
	//Init. de la SDL
	
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)==-1)
	{
		printf("Could not initialize SDL : %s.\n",SDL_GetError());
		return -1;
	}
	
	//Réglage de la fenêtre
	
	screen=SDL_SetVideoMode(1200,800,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
	SDL_WM_SetCaption("S&T GAME", NULL);

	
	//Initialisation
	
	initialiser_image(&IMAGE,"img/fond.png",0,0);
	initialiser_image(&IMAGE2,"img/fond2.png",0,0);
	initialiser_image(&IMAGE_BTN1,"img/PLAY2_NS.png",450,170);
	initialiser_image(&IMAGE_BTN2,"img/SETTINGS2_NS.png",450,310);
	initialiser_image(&IMAGE_BTN3,"img/QUIT2_NS.png",450,430);
	initialiser_image(&IMAGE_BTN4,"img/PLAY2_S.png",450,170);
	initialiser_image(&IMAGE_BTN5,"img/SETTINGS2_S.png",450,310);
	initialiser_image(&IMAGE_BTN6,"img/QUIT2_S.png",450,430);
	initialiser_image(&IMAGE_BTN8,"img/LOAD GAME NS.png",450,330);
	initialiser_image(&IMAGE_BTN7,"img/LOAD GAME.png",450,330);
	initialiser_image(&IMAGE_BTN10,"img/NEW GAME NS.png",450,200);
	initialiser_image(&IMAGE_BTN9,"img/NEW G.png",450,200);
	initialiser_image(&SETTINGS_BACK,"img/SetBack.png",430,120);
	initialiser_image(&GAME_LOGO,"img/JohnQ Logo.png",390,10);
	initialiser_image(&BARRE,"img/barre_volume.png",440,350);
	initialiser_image(&BACK,"img/back.png",570,550);
	initialiser_image(&FULLSCREEN,"img/FS.png",460,400);
	initialiser_image(&WINDOW,"img/FS.png",460,470);
	initialiser_audio(music);
	initialiser_texte(&txte,"fonts/pixel_arial.ttf",70,255,255,255,350,650);
	initialiser_texte(&txte3,"fonts/OriginTech personal use.ttf",75,255,255,255,410,90);
	initialiser_texte(&pourc,"fonts/pixel_arial.ttf",90,255,255,255,550,250);
	initialiser_texte(&moins,"fonts/pixel_arial.ttf",100,255,255,255,500,240);
	initialiser_texte(&moins2,"fonts/pixel_arial.ttf",100,255,0,0,500,240);
	initialiser_texte(&plus,"fonts/pixel_arial.ttf",100,255,255,255,700,245);
	initialiser_texte(&plus2,"fonts/pixel_arial.ttf",100,255,0,0,700,245);
	initialiser_texte(&vol_set,"fonts/pixel_arial.ttf",65,255,255,255,515,190);
	initialiser_texte(&start,"fonts/OriginTech personal use.ttf",70,255,255,255,400,300);
	initialiser_texte(&fullscreen1,"fonts/pixel_arial.ttf",35,255,255,255,488,420);
	initialiser_texte(&fullscreen2,"fonts/pixel_arial.ttf",35,255,0,0,488,420);
	initialiser_texte(&window1,"fonts/pixel_arial.ttf",35,255,255,255,505,490);
	initialiser_texte(&window2,"fonts/pixel_arial.ttf",35,255,0,0,505,490);
	initialiser_texte(&controls1,"fonts/pixel_arial.ttf",35,255,255,255,490,670);
	initialiser_texte(&controls2,"fonts/pixel_arial.ttf",35,255,0,0,490,670);
		
	initialiser_texte(&player1,"fonts/OriginTech personal use.ttf",75,255,255,255,415,90);		
	initialiser_texte(&jump1,"fonts/OriginTech personal use.ttf",50,255,255,255,485,300);
	initialiser_texte(&right1,"fonts/OriginTech personal use.ttf",75,255,255,255,485,300);
	initialiser_texte(&left1,"fonts/OriginTech personal use.ttf",75,255,255,255,485,300);	
	initialiser_texte(&dash1,"fonts/OriginTech personal use.ttf",75,255,255,255,485,300);	
	initialiser_texte(&down1,"fonts/OriginTech personal use.ttf",75,255,255,255,485,300);
	initialiser_texte(&up1,"fonts/OriginTech personal use.ttf",75,255,255,255,485,300);
	

	//Boucle Menu
	
	while(boucle)
	{
		
		if (state==1)
		{
			if(cpt1%30>=15)
			{
				afficher_imageBMP(screen,IMAGE2);
				cpt1++;
			}
			else
			{
				afficher_imageBMP(screen,IMAGE);
				cpt1++;
			}
				
			afficher_image(screen,GAME_LOGO);

			if((event.motion.y<=280 && event.motion.y>=190 && event.motion.x<=750 && event.motion.x>=430)||((k==1)&&(keyb==1)))
			{
				afficher_image(screen,IMAGE_BTN4); 
				if(event.motion.y<=280 && event.motion.y>=190 && event.motion.x<=750 && event.motion.x>=430)keyb=0;
				k=1;
			}
			else
				afficher_image(screen,IMAGE_BTN1); //Afficher Bouton PLAY
		
			if((event.motion.y<=412 && event.motion.y>=322 && event.motion.x<=750 && event.motion.x>=430)||((k==2)&&(keyb==1)))
			{
				afficher_image(screen,IMAGE_BTN5);
				if(event.motion.y<=412 && event.motion.y>=322 && event.motion.x<=750 && event.motion.x>=430)keyb=0; 
				k=2;
			}
			else
				afficher_image(screen,IMAGE_BTN2); //Afficher Bouton SETTINGS
		
			if((event.motion.y<=525 && event.motion.y>=435 && event.motion.x<=750 && event.motion.x>=430)||((k==3)&&(keyb==1)) )
			{
				afficher_image(screen,IMAGE_BTN6); 
				if(event.motion.y<=525 && event.motion.y>=435 && event.motion.x<=750 && event.motion.x>=430)keyb=0;
				k=3;
			}
			else
				afficher_image(screen,IMAGE_BTN3); //Afficher Bouton QUIT
		
			afficher_texte(screen,txte,"Success & Technology");
		
				
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					case SDL_QUIT:
						boucle=0;
						break;
				
					case SDL_MOUSEBUTTONDOWN: //Quitter Menu
						if(event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=525 && event.motion.y>=435 && event.motion.x<=750 && event.motion.x>=430))
							boucle=0;
						else if(event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=412 && event.motion.y>=322 && event.motion.x<=750 && event.motion.x>=430))
							state=2;
						else if(event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=280 && event.motion.y>=190 && event.motion.x<=750 && event.motion.x>=430))
							state=3;
							
							
						break;
				
					case SDL_MOUSEMOTION: //Son Bref
						if((event.motion.y<=525 && event.motion.y>=435 && event.motion.x<=750 && event.motion.x>=430) || (event.motion.y<=412 && event.motion.y>=322 && event.motion.x<=750 && event.motion.x>=430) || (event.motion.y<=280 && event.motion.y>=190 && event.motion.x<=750 && event.motion.x>=430)){
							if(son==0){
								initialiser_audiobref(mus);
								son=1;}}
						else
							son=0;
						break;
						
					case SDL_KEYDOWN:
						if (event.key.keysym.sym==SDLK_UP) 
						{
							keyb=1;
							if(k==1 || k==0 || k==-1)
								k=3;
							else if(k==3)
								k=2;
							else if(k==2)
								k=1;
						}
						if (event.key.keysym.sym==SDLK_DOWN) 
						{
							keyb=1;
							if(k==0||k==3)
								k=1;
							else if(k==1)
								k=2;
							else if(k==2)
								k=3;
						}
						
						if((event.key.keysym.sym==SDLK_RETURN) && k==1)
							state=3;
						else if((event.key.keysym.sym==SDLK_RETURN) && k==2)
							state=2;
						else if((event.key.keysym.sym==SDLK_RETURN) && k==3)
							boucle=0;
							
						if (event.key.keysym.sym==SDLK_p) 
						{
							state=3;
						}
						
						if (event.key.keysym.sym==SDLK_s) 
						{
							state=2;
						}
						if (event.key.keysym.sym==SDLK_q) 
						{
							boucle=0;
						}
						break;
				}
			}
		}
		
		else if(state==2)
		{
			initialiser_image(&BOULE,"img/Boule.png",pos_boule,345); // Min = 440, Max = 730, (730-440)/10=29
		
			if(cpt1%30>=15)
			{
				afficher_imageBMP(screen,IMAGE2);
				cpt1++;
			}
			else
			{
				afficher_imageBMP(screen,IMAGE);
				cpt1++;
			}
			//afficher_image(screen,GAME_LOGO);
			afficher_image(screen,SETTINGS_BACK);
			afficher_image(screen,BARRE);
			afficher_image(screen,BOULE);
			afficher_image(screen,BACK);
			afficher_image(screen,FULLSCREEN);
			afficher_image(screen,WINDOW);
			afficher_texte2(screen,pourc,count);
			if (event.motion.y<=460 && event.motion.y>=400 && event.motion.x<=740 && event.motion.x>=460)
				afficher_texte(screen,fullscreen2,"FULLSCREEN MODE");
			else
				afficher_texte(screen,fullscreen1,"FULLSCREEN MODE");
				
		
			if (event.motion.y<=730 && event.motion.y>=670 && event.motion.x<=770 && event.motion.x>=490)
				afficher_texte(screen,controls2,"CHANGE CONTROLS");
			else
				afficher_texte(screen,controls1,"CHANGE CONTROLS");
				
			if (event.motion.y<=530 && event.motion.y>=470 && event.motion.x<=740 && event.motion.x>=460)
				afficher_texte(screen,window2,"WINDOW MODE");
			else
				afficher_texte(screen,window1,"WINDOW MODE");
			
			
			afficher_texte(screen,txte3,"SETTINGS");
			afficher_texte(screen,vol_set,"VOLUME");
			if(event.motion.y<=290 && event.motion.y>=240 && event.motion.x<=550 && event.motion.x>=500)
			{
				afficher_texte(screen,moins2,"-");
				initialiser_audiobref(mus);
			}
			else
				afficher_texte(screen,moins,"-");
			
			if(event.motion.y<=295 && event.motion.y>=245 && event.motion.x<=750 && event.motion.x>=700)
			{
				afficher_texte(screen,plus2,"+");
				initialiser_audiobref(mus);
			}
			else
				afficher_texte(screen,plus,"+");
				
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					case SDL_QUIT:
					boucle=0;
					break;
					
					case SDL_MOUSEBUTTONDOWN:
						if(event.button.button==SDL_BUTTON_LEFT)
							buttonstate=1;
						
						if(event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=600 && event.motion.y>=550 && event.motion.x<=620 && event.motion.x>=570))
							state=1;
							
						if(event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=730 && event.motion.y>=670 && event.motion.x<=770 && event.motion.x>=490))
							state=5;
						
						if(event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=460 && event.motion.y>=400 && event.motion.x<=740 && event.motion.x>=460))
							screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_FULLSCREEN|SDL_SWSURFACE|SDL_DOUBLEBUF);
						
						if(event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=530 && event.motion.y>=470 && event.motion.x<=740 && event.motion.x>=460))
						{
							screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
						}
						
						break;
						
					case SDL_KEYDOWN:
						if (event.key.keysym.sym==SDLK_ESCAPE) //BACKSPACE to return main menu
						{
							state=1;
						}
						
						if (event.key.keysym.sym==SDLK_f) //BACKSPACE to return main menu
						{
							screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_FULLSCREEN|SDL_SWSURFACE|SDL_DOUBLEBUF);
						}
						
						if (event.key.keysym.sym==SDLK_w) //BACKSPACE to return main menu
						{
							screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_SWSURFACE|SDL_DOUBLEBUF);
						}
					
						
						if (event.key.keysym.sym==SDLK_KP_PLUS)
						{
							volume=volume+(MIX_MAX_VOLUME/10);
							if(volume>MIX_MAX_VOLUME)
								volume=MIX_MAX_VOLUME;
							Mix_VolumeMusic(volume);
							count=count+10;
															
							if(count>100)									
							count=100;
							
							pos_boule=pos_boule+29;
							if(pos_boule>730)
							pos_boule=730;
						}
						
						if (event.key.keysym.sym==SDLK_KP_MINUS)
						{
							volume=volume-(MIX_MAX_VOLUME/10);
							if(volume<0)
								volume=0;
							Mix_VolumeMusic(volume);
							count=count-10;
							
							if(count<0)									
							count=0;
							
							pos_boule=pos_boule-29;
							if(pos_boule<440)
							pos_boule=440;
						}
						break;
						
					default:
						if(buttonstate)
						{
							if(event.button.button==SDL_BUTTON_LEFT && event.type==SDL_MOUSEBUTTONUP)
								buttonstate=1;
							
							if(event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=295 && event.motion.y>=245 && event.motion.x<=750 && event.motion.x>=700))
						{
							volume=volume+(MIX_MAX_VOLUME/10);
							if(volume>MIX_MAX_VOLUME)
								volume=MIX_MAX_VOLUME;
							Mix_VolumeMusic(volume);
							count=count+10;
															
							if(count>100)									
							count=100;
							
							pos_boule=pos_boule+29;
							if(pos_boule>730)
							pos_boule=730;
						}
						else if(event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=290 && event.motion.y>=240 && event.motion.x<=550 && event.motion.x>=500))
						{
							volume=volume-(MIX_MAX_VOLUME/10);
							if(volume<0)
								volume=0;
							Mix_VolumeMusic(volume);
							count=count-10;
							
							if(count<0)									
							count=0;
							
							pos_boule=pos_boule-29;
							if(pos_boule<440)
							pos_boule=440;
						}
						
						else if(event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=380 && event.motion.y>=360 && event.motion.x<=740 && event.motion.x>=440))
						{
							SDL_GetMouseState(&pos_x, &pos_y);
							pos_boule=pos_x-10;
							count1=((pos_x-440)*100)/(740-440);
							
							if(count1>count)
							{
								count=count1;
								volume=((pos_x-440)*MIX_MAX_VOLUME)/(300);
								if(count>100){
									volume=MIX_MAX_VOLUME;
									count=100;
									pos_boule=740;
									}
								Mix_VolumeMusic(volume);
							}
							else if(count1<count)
							{
								count=count1;
								volume=((pos_x-440)*MIX_MAX_VOLUME)/(300);
								if(count<0){
									volume=0;
									count=0;
									pos_boule=440;
									}
								Mix_VolumeMusic(volume);
							}
						}
						}
						break;
				}
			}
			
		}
		else if(state==3)
		{
			if(cpt1%30>=15)
			{
				afficher_imageBMP(screen,IMAGE2);
				cpt1++;
			}
			else
			{
				afficher_imageBMP(screen,IMAGE);
				cpt1++;
			}
			
			//afficher_texte(screen,start,"START GAME");
			afficher_image(screen,BACK);
			
			if((event.motion.y<=280 && event.motion.y>=190 && event.motion.x<=750 && event.motion.x>=430))
				afficher_image(screen,IMAGE_BTN9); 
			else
				afficher_image(screen,IMAGE_BTN10); //Afficher Bouton NEW GAME
		
			if((event.motion.y<=412 && event.motion.y>=322 && event.motion.x<=750 && event.motion.x>=430))
				afficher_image(screen,IMAGE_BTN7);
			else
				afficher_image(screen,IMAGE_BTN8); //Afficher Bouton LOAD GAME
			
			while(SDL_PollEvent(&event))
			{
				switch(event.type)
				{
					case SDL_QUIT:
					boucle=0;
					break;
					
					case SDL_MOUSEBUTTONDOWN: 
						if(event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=600 && event.motion.y>=550 && event.motion.x<=620 && event.motion.x>=570))
							state=1;
						if((event.button.button==SDL_BUTTON_LEFT && event.motion.y<=280 && event.motion.y>=190 && event.motion.x<=750 && event.motion.x>=430)){
							system("rm -r save.bin");
							state=4;
						}
						else if((event.button.button==SDL_BUTTON_LEFT && event.motion.y<=412 && event.motion.y>=322 && event.motion.x<=750 && event.motion.x>=430))state=4;
						break;
						
					case SDL_KEYDOWN:
						if (event.key.keysym.sym==SDLK_ESCAPE) //BACKSPACE to return main menu
						{
							state=1;
						}
						break;
				}
			}	
		}
		else if(state==4){

			screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
            //Mix_FadeOutMusic(1000);
            // SDL_FreeSurface(screen);
            state = gameloop(screen,"map1.txt");
			if (state==2) gameloop(screen,"map2.txt");
			if (state==2) gameloop(screen,"map3.txt");
			state=1;
            //Mix_FreeMusic(music);
            //music = Mix_LoadMUS("music/main_theme.mp3");
            //Mix_PlayMusic(music, -1);
            screen = SDL_SetVideoMode(1200, 800, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
		}
		
		else if(state==5)
		{
			if(cpt1%30>=15)
			{
				afficher_imageBMP(screen,IMAGE2);
				cpt1++;
			}
			else
			{
				afficher_imageBMP(screen,IMAGE);
				cpt1++;
			}
			afficher_image(screen,SETTINGS_BACK);
			
			afficher_texte(screen,player1,"PLAYER 1");
			
			if(change_counter==0) f = fopen("keys1.txt", "w");
			
			if(f!=NULL)
			{
				if(change_counter==0)afficher_texte(screen,jump1,"JUMP ?");
				if(change_counter==1)afficher_texte(screen,right1,"RIGHT ?");
				if(change_counter==2)afficher_texte(screen,left1,"LEFT ?");
				if(change_counter==3)afficher_texte(screen,dash1,"DASH ?");
				if(change_counter==4)afficher_texte(screen,down1,"DOWN ?");
				if(change_counter==5)afficher_texte(screen,up1,"UP ?");
				if(change_counter==6){change_counter=0;state=6;fclose(f);}
				else{
				while(SDL_PollEvent(&event))
				{
				if (event.type == SDL_KEYDOWN)
        			{
						printf("%d\n",event.key.keysym.sym);
         				fprintf(f,"%d ",event.key.keysym.sym);
						change_counter++;
					}
      				else if (event.type == SDL_QUIT)
      				{
       				boucle=0;
       			}
       			}
				}	
    			
			}
		}
		
		else if(state==6)
		{
			if(cpt1%30>=15)
			{
				afficher_imageBMP(screen,IMAGE2);
				cpt1++;
			}
			else
			{
				afficher_imageBMP(screen,IMAGE);
				cpt1++;
			}
			afficher_image(screen,SETTINGS_BACK);
			
			afficher_texte(screen,player1,"PLAYER 2");
			
			if(change_counter==0) f = fopen("keys2.txt", "w");
			
			if(f!=NULL)
			{
				if(change_counter==0)afficher_texte(screen,jump1,"JUMP ?");
				if(change_counter==1)afficher_texte(screen,right1,"RIGHT ?");
				if(change_counter==2)afficher_texte(screen,left1,"LEFT ?");
				if(change_counter==3)afficher_texte(screen,dash1,"DASH ?");
				if(change_counter==4)afficher_texte(screen,down1,"DOWN ?");
				if(change_counter==5)afficher_texte(screen,up1,"UP ?");
				if(change_counter==6){change_counter=0;state=2;fclose(f);}
				else{
				while(SDL_PollEvent(&event))
				{
				if (event.type == SDL_KEYDOWN)
        			{
						printf("%d\n",event.key.keysym.sym);
         				fprintf(f,"%d ",event.key.keysym.sym);
						change_counter++;
					}
      				else if (event.type == SDL_QUIT)
      				{
       				boucle=0;
       			}
       			}
				}	
    			
			}
		}
		
		SDL_Flip(screen); //Raffraichir l'ecran
	}
	
	//Libreation des surfaces
	
	SDL_FreeSurface(IMAGE.img);
	SDL_FreeSurface(IMAGE2.img);
	SDL_FreeSurface(IMAGE_BTN1.img);
	SDL_FreeSurface(IMAGE_BTN2.img);
	SDL_FreeSurface(IMAGE_BTN3.img);
	SDL_FreeSurface(IMAGE_BTN4.img);
	SDL_FreeSurface(IMAGE_BTN5.img);
	SDL_FreeSurface(IMAGE_BTN6.img);
	SDL_FreeSurface(IMAGE_BTN7.img);
	SDL_FreeSurface(IMAGE_BTN8.img);
	SDL_FreeSurface(IMAGE_BTN9.img);
	SDL_FreeSurface(IMAGE_BTN10.img);
	SDL_FreeSurface(BACK.img);
	SDL_FreeSurface(FULLSCREEN.img);
	SDL_FreeSurface(WINDOW.img);
	SDL_FreeSurface(GAME_LOGO.img);
	SDL_FreeSurface(SETTINGS_BACK.img);
	SDL_FreeSurface(BARRE.img);
	SDL_FreeSurface(BOULE.img);
	//liberer_musique(music);
	liberer_texte(txte);
	liberer_texte(pourc);
	liberer_texte(txte3);
	liberer_texte(moins);
	liberer_texte(moins2);
	liberer_texte(plus);
	liberer_texte(plus2);
	liberer_texte(vol_set);
	liberer_texte(start);
	liberer_texte(fullscreen1);
	liberer_texte(fullscreen2);
	liberer_texte(window1);
	liberer_texte(window2);
	liberer_texte(jump1);
	liberer_texte(left1);
	liberer_texte(dash1);
	liberer_texte(up1);
	liberer_texte(down1);
	liberer_texte(right1);
	liberer_texte(controls1);
	liberer_texte(controls2);
	liberer_texte(player1);

	return 0;
}
	
	

