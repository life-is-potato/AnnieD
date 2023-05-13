#include "game.h"
#include "enigme.h"
int gameloop(SDL_Surface *screen)
{
    int boucle = 1;
    char *spritesheet1 = "img/Potato_walking-export.png";
    char *spritesheet2 = "img/Potato_walking-export.png";
    char *minimappath = "smol_bg.png";
    char *miniplayerpath = "smol.png";

    SDL_Rect scr;
    scr.x = 0;
    scr.y = 0;
    scr.h = SCREEN_H;
    scr.w = SCREEN_W;
    Uint32 starttime2 = SDL_GetTicks();

    SDL_Rect scr1;
    scr1.x = 0;
    scr1.y = 0;
    scr1.w = SCREEN_W / 2;
    scr1.h = SCREEN_H;
    SDL_Rect scr2;
    scr2.x = SCREEN_W / 2;
    scr2.y = 0;
    scr2.w = SCREEN_W / 2;
    scr2.h = SCREEN_H;
    camera cam, cam1, cam2;
    minimap mm;
    miniplayer mp, mp2, me, minitile;
    player p1, p2;
    img bg, dummy, nothing, enigmeobj;
    txt timertxt;
    int mode = 1;
    int starttime;
    int endtime = 0;
    float wait;
    float deltat;
    Uint32 time = 0;
    save savefile;
    savefile.time = 0;
    savefile.x1 = 100;
    savefile.x2 = 200;
    savefile.y1 = 400;
    savefile.y2 = 400;
    savefile.e1 = 1;
    FILE *f = fopen("save.bin", "rb");
    time = 0;
    if (f != NULL)
    {
        fread(&savefile, sizeof(save), 1, f);
        fclose(f);
    }

    // initializing camera

    cam.x = (savefile.x1 + savefile.x2) / 2;
    cam.y = (savefile.y1 + savefile.y2) / 2;

    load_txt(&timertxt, 10, 10, 0, 255, 0, "fonts/pixel_arial.ttf", 50);
    init_minimap(&mm, minimappath, screen);
    init_miniplayer(&mp, miniplayerpath);
    init_miniplayer(&mp2, miniplayerpath);
    init_miniplayer(&me, miniplayerpath);
    init_miniplayer(&minitile, "img/wall_smol.png");
    player_create(&p1, spritesheet1, savefile);
    p1.x_spd = 0;
    //printf("%f\n", p1.x_spd);
    player_create2(&p2, spritesheet2, savefile);
    enemy urmom;
    img tm[1000];
    img dec[1000];
    int size = 0, size2=0;
    parse_tiles("map.txt", tm, &size, dec, &size2);
    enemy_create(&urmom, spritesheet1);
    load_img(&bg, "img/background.jpg", 0, 0);
    load_img(&dummy, "img/background.jpg", 0, 0);
    load_img(&nothing, "void.png", -1000, -1000);
    load_img(&enigmeobj, "img/enigme_objet.png", 290, 240);
    enigmeobj.pos.w=25;
    img car;
    load_img(&car, "img/object.png", 100, 100);
    int k = 0;
    cam1.x = cam.x;
    cam1.y = cam.y;
    cam2.x = cam.x;
    cam2.y = cam.y;
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
        enemy_step(&urmom, cam, p1, p2, tm, size);
        if (savefile.e1 && (player_meeting(p1, enigmeobj) || player_meeting(p2, enigmeobj)))
        {
            SDL_Delay(100);
            if(enigme_play(screen))savefile.e1 = 0;
            if(player_meeting(p1, enigmeobj)) {p1.sprite.pos.x-=3*p1.x_spd;p1.x_spd=0;p1.facing=-p1.facing;p1.direction=-p1.direction;p1.right.pressed=0;p1.left.pressed=0;}
            else{p2.sprite.pos.x-=3*p2.x_spd;p2.x_spd=0;p2.facing=-p2.facing;p2.direction=-p2.direction;p2.right.pressed=0;p2.left.pressed=0;}
        }
        update_camera(p1.sprite, p2.sprite, &cam, &mode);
        // Dessine les arrière-plans, les ennemis, les joueurs, et les objets
        if (mode == 1)
        {
            SDL_BlitSurface(nothing.image, NULL, screen, &nothing.pos);
            display_sprite(screen, bg, cam, mode, 0);
            animerBack(&car, &k);
            display_sprite(screen, car, cam, mode, 0);
            display_tiles(screen, tm, cam, size, mode, 0);
            display_dec(screen, dec, cam, size2, mode, 0);
            if(savefile.e1)display_sprite(screen, enigmeobj, cam, mode, 0);
            player_draw(p1, screen, cam, 0, mode);
            player_draw(p2, screen, cam, 0, mode);
            enemy_draw(urmom, screen, cam, 0, mode);
            SDL_BlitSurface(mm.img.image, NULL, screen, &dummy.pos);
        }
        else
        {
            if (p1.sprite.pos.x < p2.sprite.pos.x)
            {
                update_camera(p1.sprite, p1.sprite, &cam1, &mode);
                update_camera(p2.sprite, p2.sprite, &cam2, &mode);
            }
            else
            {
                update_camera(p1.sprite, p1.sprite, &cam2, &mode);
                update_camera(p2.sprite, p2.sprite, &cam1, &mode);
            }
            SDL_BlitSurface(nothing.image, NULL, screen, &nothing.pos);
            SDL_SetClipRect(screen, &scr2);
            display_sprite(screen, bg, cam2, mode, 1);
            display_sprite(screen, car, cam2, mode, 1);
            display_tiles(screen, tm, cam2, size, mode, 1);
            display_dec(screen, dec, cam2, size2, mode, 1);
            if(savefile.e1)display_sprite(screen, enigmeobj, cam2, mode, 1);
            player_draw(p1, screen, cam2, 1, mode);
            player_draw(p2, screen, cam2, 1, mode);
            enemy_draw(urmom, screen, cam2, 1, mode);
            //
            SDL_SetClipRect(screen, &scr1);
            display_sprite(screen, bg, cam1, mode, -1);
            animerBack(&car, &k);
            display_sprite(screen, car, cam1, mode, -1);
            display_tiles(screen, tm, cam1, size, mode, -1);
            display_dec(screen, dec, cam1, size2, mode, -1);
            if(savefile.e1)display_sprite(screen, enigmeobj, cam1, mode, -1);
            player_draw(p1, screen, cam1, -1, mode);
            player_draw(p2, screen, cam1, -1, mode);
            enemy_draw(urmom, screen, cam1, -1, mode);
            SDL_BlitSurface(mm.img.image, NULL, screen, &dummy.pos);
        }
        // Dessine la minimap
        SDL_SetClipRect(screen, &dummy.pos);
        update_miniplayer(&mm, &mp, &p1, screen, cam);
        update_miniplayer(&mm, &mp2, &p2, screen, cam);
        update_minienemy(&mm, &me, &urmom, screen, cam);
        update_tiles(&mm,&minitile,size,tm,screen,cam);
        SDL_SetClipRect(screen, &scr);
        update_time(0, &mm, &time, &timertxt, screen, savefile, starttime2);
        SDL_Flip(screen);
        endtime = SDL_GetTicks();
        deltat = (endtime - starttime) / (float)1000;
        wait = ((float)1 / (float)MAX_FPS) - deltat;
        if (wait > 0)
            SDL_Delay(1000 * wait);
    }
    savefile.time = SDL_GetTicks() - starttime2 + savefile.time;
    savefile.x1 = p1.sprite.pos.x;
    savefile.x2 = p2.sprite.pos.x;
    savefile.y1 = p1.sprite.pos.y;
    savefile.y2 = p2.sprite.pos.y;
    f = fopen("save.bin", "wb");
    if (f != NULL)
    {
        fwrite(&savefile, sizeof(save), 1, f);
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
    return (4);
}