#include "game.h"


int gameloop(SDL_Surface* screen)
{
    int boucle = 1;
    char *spritesheet1 = "img/Potato_walking-export.png";
    char *spritesheet2 = "img/Potato_walking-export.png";
    char *minimappath = "smol_bg.png";
    char *miniplayerpath = "smol.png";
    camera cam, cam2;
    minimap mm;
    miniplayer mp, mp2, me;
    player p1, p2;
    img bg, dummy, nothing;
    txt timertxt;
    int mode=0;
    int starttime;
    int endtime = 0;
    float wait;
    float deltat;
    Uint32 time = 0;
    save savefile;
    savefile.time=0;
    savefile.x1=100;
    savefile.x2=200;
    savefile.y1=400;
    savefile.y2=400;
    FILE* f=fopen("save.bin","rb");
    time = 0;
    if(f!=NULL){
        fread(&savefile, sizeof(save),1,f);
        fclose(f);
    }

    //initializing camera

    cam.x = (savefile.x1+savefile.x2)/2;
    cam.y = (savefile.y1+savefile.y2)/2;

    printf("\n%d %d\n", cam.x, cam.y);

    load_txt(&timertxt, 10, 10, 0, 255, 0, "fonts/pixel_arial.ttf", 50);
    init_minimap(&mm, minimappath, screen);
    init_miniplayer(&mp, miniplayerpath);
    init_miniplayer(&mp2, miniplayerpath);
    init_miniplayer(&me, miniplayerpath);
    player_create(&p1, spritesheet1,savefile);
    p1.x_spd=0;
    printf("%f\n",p1.x_spd);
    player_create2(&p2, spritesheet2,savefile);
    enemy urmom;
    img tm[1000];
    int size = 0;
    parse_tiles("map.txt", tm, &size);
    enemy_create(&urmom, spritesheet1);
    load_img(&bg, "img/background.jpg", 0, 0);
    load_img(&dummy, "img/background.jpg", 0, 0);
    load_img(&nothing, "void.png", -1000, -1000);
    img car;
    load_img(&car, "img/object.png", 100, 100);
    int k = 0;
    if (screen == NULL)
        return -1;

    while (boucle)
    {
        // commentaires en français pour Skander <3

        starttime = SDL_GetTicks();
        players_get_inputs(&p1, &p2, &boucle);

        // Execute la logique des joueurs et des ennemis, et met à jour la position de la camera

        player_step(&p1, cam, tm, size);
        player_step(&p2, cam, tm, size);
        enemy_step(&urmom, cam, tm, size);
        update_camera(p1.sprite, p2.sprite, &cam,&mode);

        // Dessine les arrière-plans, les ennemis, les joueurs, et les objets

        bg.pos.x = -(cam.x - SCREEN_W / 2);
        bg.pos.y = -(cam.y - SCREEN_H / 2);
        SDL_BlitSurface(nothing.image, NULL, screen, &nothing.pos);
        display_img(screen, bg);
        animerBack(&car, &k);
        display_sprite(screen, car, cam);
        display_tiles(screen, tm, cam, size);
        player_draw(p1, screen, cam);
        player_draw(p2, screen, cam);
        enemy_draw(urmom, screen, cam);
        SDL_BlitSurface(mm.img.image, NULL, screen, &dummy.pos);

        // Dessine la minimap

        update_miniplayer(&mm, &mp, &p1, screen,cam);
        update_miniplayer(&mm, &mp2, &p2, screen,cam);
        update_minienemy(&mm, &me, &urmom, screen,cam);
        update_time(0, &mm, &time, &timertxt, screen, savefile);
        SDL_Flip(screen);
        endtime = SDL_GetTicks();
        deltat = (endtime - starttime) / (float)1000;
        wait = ((float)1 / (float)MAX_FPS) - deltat;
        if (wait > 0)
            SDL_Delay(1000 * wait);
    }
    savefile.time=SDL_GetTicks()+savefile.time;
    savefile.x1=p1.sprite.pos.x;
    savefile.x2=p2.sprite.pos.x;
    savefile.y1=p1.sprite.pos.y;
    savefile.y2=p2.sprite.pos.y;
    printf("%d %d %d",savefile.x1,savefile.y1,savefile.time);
    f=fopen("save.bin","wb");
    if(f!=NULL){
        fwrite(&savefile,sizeof(save),1,f);
        fclose(f);
    }
    SDL_FreeSurface(screen);
    free_img(bg);
    free_img(p1.sprite);
    free_img(p2.sprite);
    free_img(mp.img);
    free_img(mp2.img);
    free_img(dummy);
    free_img(nothing);
    free_txt(timertxt);
    return(1);
}