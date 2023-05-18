#include "mapmaker.h"

int mapmaker(SDL_Surface* screen)
{
    int rc;
    SDL_Rect fs;
    fs.x=0;
    fs.y=0;
    fs.w=SCREEN_W;
    fs.h=SCREEN_H;
    SDL_Rect clip;
    clip.x=0;
    clip.y=100;
    clip.w=SCREEN_W;
    clip.h=SCREEN_H-100;
    int counter;
    button keys[4];
    for(int i=0;i<4;i++){
        keys[i].pressed=0;
        keys[i].released=0;
    }
    img selectable_tiles[20];
    img tiles[1000];
    int exist[1000];
    for (int i=0;i<1000;i++){
        exist[i]=0;
    }
    printf("a\n");
    int size=0;
    int selected=-1;
    camera cam;
    camera mouse;
    cam.x=SCREEN_W/2;
    cam.y=SCREEN_H/2+100;
    int boucle = 1;
    img blackbar, bg;
    load_img(&blackbar, "img/topbar.png", 0, 0);
    load_img(&bg, "img/bgexp.png", 0, 0);
    load_img(&selectable_tiles[0],"img/wall_left.png",10,10);
    load_img(&selectable_tiles[1],"img/wall_middle.png",70,10);
    load_img(&selectable_tiles[2],"img/wall_right.png",130,10);
    load_img(&selectable_tiles[3],"img/liquid_tube_bottom.png",190,10);
    load_img(&selectable_tiles[4],"img/liquid_tube_top.png",250,10);
    load_img(&selectable_tiles[5],"img/pipe_bottom_left.png",310,10);
    load_img(&selectable_tiles[6],"img/pipe_bottom_right.png",370,10);
    load_img(&selectable_tiles[7],"img/pipe_top_left.png",430,10);
    load_img(&selectable_tiles[8],"img/pipe_top_right.png",490,10);
    load_img(&selectable_tiles[9],"img/pipe_head_top.png",550,10);
    load_img(&selectable_tiles[10],"img/pipe_head_down.png",610,10);
    load_img(&selectable_tiles[11],"img/pipe_head_left.png",670,10);
    load_img(&selectable_tiles[12],"img/pipe_head_right.png",730,10);
    load_img(&selectable_tiles[13],"img/pipe_horizontal.png",790,10);
    load_img(&selectable_tiles[14],"img/pipe_vertical.png",850,10);
    load_img(&selectable_tiles[15],"img/enigme_objet.png",910,10);
    load_img(&selectable_tiles[16],"img/spike.png",970,10);
    SDL_Event event;
    while (boucle)
    {
        mouse.x=-1;
        mouse.y=-1;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button==SDL_BUTTON_RIGHT) rc=1;
                else rc=0;
                mouse.x=event.motion.x;
                mouse.y=event.motion.y;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_RIGHT:keys[0].pressed=1;keys[0].released=1;break;
                    case SDLK_LEFT:keys[1].pressed=1;keys[1].released=1;break;
                    case SDLK_UP:keys[2].pressed=1;keys[1].released=1;break;
                    case SDLK_DOWN:keys[3].pressed=1;keys[1].released=1;break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym){
                    case SDLK_RIGHT:keys[0].released=1;keys[0].pressed=0;break;
                    case SDLK_LEFT:keys[1].released=1;keys[1].pressed=0;break;
                    case SDLK_UP:keys[2].released=1;keys[2].pressed=0;break;
                    case SDLK_DOWN:keys[3].released=1;keys[3].pressed=0;break;
                }
            }
        }

        //handling camera
        if (keys[0].pressed==1)cam.x+=2;
        if (keys[1].pressed==1)cam.x-=2;
        if (keys[2].pressed==1)cam.y-=2;
        if (keys[3].pressed==1)cam.y+=2;
        if(cam.x>bg.image->w-SCREEN_W/2)cam.x=bg.image->w-SCREEN_W/2;
        else if(cam.x<SCREEN_W/2)cam.x=SCREEN_W/2;
        if(cam.y>bg.image->h-SCREEN_H/2)cam.y=bg.image->h-SCREEN_H/2;
        else if(cam.y<(100+SCREEN_H/2))cam.y=100+SCREEN_H/2;   

        //handling mouse clicks

        if(mouse.x!=-1 && mouse.y !=-1){
            for(int i=0;i<17;i++){
                if (check_point_collision(selectable_tiles[i],mouse.x,mouse.y)){
                    selected=i;
                    break;
                }
            }
            if (mouse.x>970+50){
                selected=-1;
            }
            
            camera mousecam;
            mousecam.x=mouse.x+cam.x-SCREEN_W/2;
            mousecam.y=mouse.y+cam.y-SCREEN_H/2;
            mousecam.x=(mousecam.x/52)*52;
            mousecam.y=(mousecam.y/50)*50;
            if(mouse.y>100 && selected==-1){
                for(counter=0;counter<size;counter++){
                    if(mousecam.x==tiles[counter].pos.x && mousecam.y==tiles[counter].pos.y){
                        for(int i=counter;i<size;i++){
                            tiles[i]=tiles[i+1];
                            exist[i]=exist[i+1];
                        }
                        size--;
                        break;
                    }
                }
            }
            else if(mouse.y>100 && selected!=-1){
                for(counter=0;counter<size;counter++){
                    if(mousecam.x==tiles[counter].pos.x && mousecam.y==tiles[counter].pos.y){
                        break;
                    }
                }
                //load_img(&tiles[counter],"img/wall_left.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                //free_img(tiles[counter]);
                if(selected==0)load_img(&tiles[counter],"img/wall_left.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==1)load_img(&tiles[counter],"img/wall_middle.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==2)load_img(&tiles[counter],"img/wall_right.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==3)load_img(&tiles[counter],"img/liquid_tube_bottom.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==4)load_img(&tiles[counter],"img/liquid_tube_top.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==5)load_img(&tiles[counter],"img/pipe_bottom_left.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==6)load_img(&tiles[counter],"img/pipe_bottom_right.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==7)load_img(&tiles[counter],"img/pipe_top_left.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==8)load_img(&tiles[counter],"img/pipe_top_right.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==9)load_img(&tiles[counter],"img/pipe_head_top.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==10)load_img(&tiles[counter],"img/pipe_head_down.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==11)load_img(&tiles[counter],"img/pipe_head_left.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==12)load_img(&tiles[counter],"img/pipe_head_right.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==13)load_img(&tiles[counter],"img/pipe_horizontal.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==14)load_img(&tiles[counter],"img/pipe_vertical.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==15)load_img(&tiles[counter],"img/enigme_objet.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                else if(selected==16)load_img(&tiles[counter],"img/spike.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                if (counter==size)size++;
                exist[size]=selected;
            }
        }


        //displaying stuff
        SDL_SetClipRect(screen,&fs);
        display_sprite(screen,bg,cam,1,0);
        display_tiles(screen,tiles,cam,size,1,0);
        SDL_SetClipRect(screen,NULL);
        display_img(screen,blackbar);
        for(int i=0;i<17;i++){
            display_img(screen,selectable_tiles[i]);
        }
        SDL_Flip(screen);
    }
}