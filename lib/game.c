#include "game.h"
#include "enigme.h"
int gameloop(SDL_Surface *screen, char* level)
{
    int room_width, room_height;
    int boucle = 1;
    char *spritesheet1 = "img/Potato_walking-export.png";
    char *spritesheet2 = "img/Potato_walking-export.png";
    char *minimappath = "smol_bg.png";
    char *miniplayerpath = "smol.png";
    int penalty = 0;
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
    img bg,/* dummy,*/ nothing, enigmeobj, life;
    txt timertxt;
    int mode = 1;
    int starttime;
    int endtime = 0;
    float wait;
    float deltat;
    Uint32 time = 0;
    save savefile;
    savefile.time = 0;
    savefile.e1 = 1;
    savefile.lives = 3;

    // initializing camera

    cam.x = (savefile.x1 + savefile.x2) / 2;
    cam.y = (savefile.y1 + savefile.y2) / 2;
    load_txt(&timertxt, 10, 10, 0, 255, 0, "fonts/pixel_arial.ttf", 50);
    init_minimap(&mm, minimappath);
    init_miniplayer(&mp, miniplayerpath);
    SDL_SetAlpha(mp.img.image, SDL_SRCALPHA, 128);
    init_miniplayer(&mp2, miniplayerpath);
    SDL_SetAlpha(mp2.img.image, SDL_SRCALPHA, 128);
    init_miniplayer(&me, miniplayerpath);
    SDL_SetAlpha(me.img.image, SDL_SRCALPHA, 128);
    init_miniplayer(&minitile, "img/wall_smol.png");
    SDL_SetAlpha(minitile.img.image, SDL_SRCALPHA, 128);
    
    p1.x_spd = 0;
    // printf("%f\n", p1.x_spd);
    
    enemy urmom;
    img spk[10000];
    img tm[10000];
    img dec[10000];
    img eng[10];
    int size = 0, size2 = 0, size3 = 0, size4=0;
    enemy_create(&urmom,0,0);
    parse_tiles(&p1, &p2, &urmom, level, tm, &size, dec, &size2, eng, &size3, spk, &size4,  &room_width, &room_height);
    player_create(&p1, spritesheet1);
    player_create2(&p2, spritesheet2);
    p1.sprite.pos.x=p1.respawn_x;
    p1.sprite.pos.y=p1.respawn_y;
    p2.sprite.pos.x=p2.respawn_x;
    p2.sprite.pos.y=p2.respawn_y;
    FILE *f = fopen("save.bin", "rb");
    time = 0;
    if (f != NULL)
    {
        fread(&savefile, sizeof(save), 1, f);
        fclose(f);
    }
    load_img(&bg, "img/bgexp.png", 0, 0);
    // load_img(&dummy, "img/bgexp.png",-300, 0);
    load_img(&nothing, "void.png", -1000, -1000);
    load_img(&life, "img/lives.png", 0, 20);
    load_img(&enigmeobj, "img/enigme_objet.png", 250, 510);
    enigmeobj.pos.w = 25;
    img car;
    load_img(&car, "img/object.png", 100, 100);
    //int k = 0;
    cam1.x = cam.x;
    cam1.y = cam.y;
    cam2.x = cam.x;
    cam2.y = cam.y;
    if (screen == NULL)
        return -1;

    while (boucle)
    {  
        if (p1.lives<=0){
            f=fopen("save.bin","w");
            fclose(f);
            system("rm -r save.bin");
            return(1);
        }
        if (size3<=0){ 
            f=fopen("save.bin","w");
            fclose(f);
            system("rm -r save.bin");
            return(2);
        }
        // commentaires en français pour Skander <3

        starttime = SDL_GetTicks();
        players_get_inputs(&p1, &p2, &boucle);

        // Execute la logique des joueurs et des ennemis, et met à jour la position de la camera

        player_step(&p1, tm, size,spk,size4);
        player_step(&p2, tm, size,spk,size4);
        enemy_step(&urmom, p1, p2, tm, size);
        if (player_ennemy_colliding(p1, urmom) || player_ennemy_colliding(p2, urmom))
            penalty++;

        // Handles enigmes
        for (int counter = 0; counter < size3; counter++)
        {
            if (pixel_perfect_collision(&p1, &eng[counter]) || pixel_perfect_collision(&p2, &eng[counter]))
            {
                SDL_Delay(100);
                if (enigme_play(screen))
                {
                    savefile.e1 = 0;
                    for (int counter2 = counter; counter2 < size3 - 1; counter2++)
                    {
                        eng[counter2] = eng[counter2 + 1];
                    }
                    size3--;
                }
                else
                    p1.lives -= 1;
                if (player_meeting(p1, eng[counter]))
                {
                    p1.sprite.pos.x = p1.respawn_x;
                    p1.sprite.pos.y = p1.respawn_y;
                    p1.x_spd = 0;
                    p1.y_spd = 0;
                    p1.facing = -p1.facing;
                    p1.direction = -p1.direction;
                    p1.right.pressed = 0;
                    p1.left.pressed = 0;
                    p1.dashing = 0;
                }
                else if (player_meeting(p2, eng[counter]))
                {
                    p2.sprite.pos.x = p2.respawn_x;
                    p2.sprite.pos.y = p2.respawn_y;
                    p2.x_spd = 0;
                    p2.y_spd = 0;
                    p2.facing = -p2.facing;
                    p2.direction = -p2.direction;
                    p2.right.pressed = 0;
                    p2.left.pressed = 0;
                    p2.dashing = 0;
                }
                break;
            }
        }

        update_camera(p1.sprite, p2.sprite, &cam, &mode, room_width, room_height, 2);
        // Dessine les arrière-plans, les ennemis, les joueurs, et les objets
        if (mode == 1)
        {
            SDL_BlitSurface(nothing.image, NULL, screen, &nothing.pos);
            display_sprite(screen, bg, cam, mode, 0);
            display_tiles(screen, tm, cam, size, mode, 0);
            display_dec(screen, dec, cam, size2, mode, 0);
            display_tiles(screen, eng, cam, size3, mode, 0);
            display_tiles(screen, spk, cam, size4,mode,0);
            // if(savefile.e1)display_sprite(screen, enigmeobj, cam, mode, 0);
            player_draw(p1, screen, cam, 0, mode);
            player_draw(p2, screen, cam, 0, mode);
            enemy_draw(urmom, screen, cam, 0, mode);
        }
        else
        if(1==1)
        {
            mode = 1;
            if (p1.sprite.pos.x < p2.sprite.pos.x)
            {
                update_camera(p1.sprite, p1.sprite, &cam1, &mode, room_width, room_height, 0);
                update_camera(p2.sprite, p2.sprite, &cam2, &mode, room_width, room_height, 1);
            }
            else
            {
                update_camera(p1.sprite, p1.sprite, &cam2, &mode, room_width, room_height, 1);
                update_camera(p2.sprite, p2.sprite, &cam1, &mode, room_width, room_height, 0);
            }
            SDL_BlitSurface(nothing.image, NULL, screen, &nothing.pos);
            SDL_SetClipRect(screen, &scr2);
            display_sprite(screen, bg, cam2, mode, 1);
            display_tiles(screen, tm, cam2, size, mode, 1);
            display_dec(screen, dec, cam2, size2, mode, 1);
            display_tiles(screen, eng, cam2, size3, mode, 1);
            display_tiles(screen, spk, cam2, size4, mode, 1);
            // if(savefile.e1)display_sprite(screen, enigmeobj, cam2, mode, 1);
            player_draw(p1, screen, cam2, 1, mode);
            player_draw(p2, screen, cam2, 1, mode);
            enemy_draw(urmom, screen, cam2, 1, mode);
            //
            SDL_SetClipRect(screen, &scr1);
            display_sprite(screen, bg, cam1, mode, -1);
            display_tiles(screen, tm, cam1, size, mode, -1);
            display_dec(screen, dec, cam1, size2, mode, -1);
            display_tiles(screen, eng, cam1, size3, mode, -1);
            display_tiles(screen, spk, cam1, size4, mode, -1);
            // if(savefile.e1)display_sprite(screen, enigmeobj, cam1, mode, -1);
            player_draw(p1, screen, cam1, -1, mode);
            player_draw(p2, screen, cam1, -1, mode);
            enemy_draw(urmom, screen, cam1, -1, mode);
        }
        // Dessine la minimap
        SDL_SetClipRect(screen, &mm.img.pos);
        SDL_BlitSurface(mm.img.image, NULL, screen, &mm.img.pos);
        update_miniplayer(&mm, &mp, &p1, screen, cam);
        update_miniplayer(&mm, &mp2, &p2, screen, cam);
        update_minienemy(&mm, &me, &urmom, screen, cam);
        update_tiles(&mm, &minitile, size, tm, screen, cam);
        SDL_SetClipRect(screen, &scr);
        display_lives(p1, screen, life);
        update_time(0, &time, &timertxt, screen, savefile, starttime2);
        SDL_Flip(screen);
        endtime = SDL_GetTicks();
        deltat = (endtime - starttime) / (float)1000;
        wait = ((float)1 / (float)MAX_FPS)- deltat;
        if (wait > 0)
            SDL_Delay(1000 * wait);
    }
    printf("\nlevel finished in %d seconds\n", penalty + (SDL_GetTicks() - starttime2) / 1000);
    savefile.time = SDL_GetTicks() - starttime2 + savefile.time;
    savefile.x1 = p1.respawn_x;
    savefile.x2 = p2.respawn_x;
    savefile.y1 = p1.respawn_y;
    savefile.y2 = p2.respawn_y;
    f = fopen("save.bin", "wb");
    if (f != NULL)
    {
        fwrite(&savefile, sizeof(save), 1, f);
        fclose(f);
    }
    return (0);
}