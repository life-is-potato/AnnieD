#include "functions.h"
#include "character.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int RectInside(SDL_Rect rect1, SDL_Rect rect2)
{
    if (rect1.x >= rect2.x && rect1.y >= rect2.y && rect1.x + rect1.w <= rect2.x + rect2.w && rect1.y + rect1.h <= rect2.y + rect2.h)
    {
        return 1;
    }
    return 0;
}
float calculateDistance(SDL_Rect rect1, SDL_Rect rect2)
{
    int x1 = rect1.x + rect1.w / 2;
    int y1 = rect1.y + rect1.h / 2;
    int x2 = rect2.x + rect2.w / 2;
    int y2 = rect2.y + rect2.h / 2;
    float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    return distance;
}

void update_camera(img img1, img img2, camera *cam, int *mode, int room_width, int room_height, int side)
{
    /*SDL_Rect screen = {
    .x = cam->x - SCREEN_W / 4,
    .y = cam->y - SCREEN_H / 4,
    .w = SCREEN_W / 2,
    .h = SCREEN_H / 2
    };*/
    int var = (abs(img1.pos.x - img2.pos.x) < (SCREEN_W / 2)) && (abs(img1.pos.y - img2.pos.y) < (SCREEN_H / 2));
    if (side == 2)
    {
        if (/*(RectInside(img1.pos,screen) && RectInside(img2.pos,screen)) || */ var)
        {
            if (mode != NULL)
                *mode = 1;
        }
        else
        {
            if (mode != NULL)
                *mode = 2;
        }
    }
    cam->x += ((img1.pos.x + img2.pos.x + 50) / 2 - cam->x) / 20;
    if (side == 2)
    {
        if (cam->x < SCREEN_W / 2)
            cam->x = SCREEN_W / 2;
        if (cam->x > room_width - SCREEN_W / 2)
            cam->x = room_width - SCREEN_W / 2;
    }
    else if (side == 0)
    {
        if (cam->x < SCREEN_W / 4)
            cam->x = SCREEN_W / 4;
    }
    else if (side == 1)
    {
        if (cam->x > room_width - SCREEN_W / 4)
            cam->x = room_width - SCREEN_W / 4;
    }
    cam->y += ((img1.pos.y + img2.pos.y) / 2 - cam->y) / 20;
    if (cam->y < SCREEN_H / 2)
        cam->y = SCREEN_H / 2;
    if (cam->y > room_height - SCREEN_H / 2)
        cam->y = room_height - SCREEN_H / 2;
    /*cam->x += ((img1.pos.x + img2.pos.x + 50) / 2 - cam->x) / 20;
    if(cam->x < SCREEN_W/2/ *mode && side==2) cam->x=SCREEN_W/2 / *mode;
    if(cam->x > room_width - SCREEN_W/2/ * mode && side==2) cam->x= room_width - SCREEN_W/2/ *mode;
    cam->y += ((img1.pos.y + img2.pos.y) / 2 - cam->y) / 20;
    printf("%d\n",cam->y);
    if(cam->y < SCREEN_H/2) cam->y=SCREEN_H/2;
    if(cam->y > room_height - SCREEN_H/2) cam->y= room_height - SCREEN_H/2;*/
}

void players_get_inputs(player *p1, player *p2, int *boucle)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            *boucle = 0;
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                *boucle = 0;
            if ((int)event.key.keysym.sym == p1->key.jump)
                p1->jump.pressed = 1;
            if ((int)event.key.keysym.sym == p1->key.right)
                p1->right.pressed = 1;
            if ((int)event.key.keysym.sym == p1->key.left)
                p1->left.pressed = 1;
            if ((int)event.key.keysym.sym == p1->key.up)
                p1->up.pressed = 1;
            if ((int)event.key.keysym.sym == p1->key.down)
                p1->down.pressed = 1;
            if ((int)event.key.keysym.sym == p1->key.dash)
                p1->dash.pressed = 1;
            if ((int)event.key.keysym.sym == p2->key.jump)
                p2->jump.pressed = 1;
            if ((int)event.key.keysym.sym == p2->key.right)
                p2->right.pressed = 1;
            if ((int)event.key.keysym.sym == p2->key.left)
                p2->left.pressed = 1;
            if ((int)event.key.keysym.sym == p2->key.up)
                p2->up.pressed = 1;
            if ((int)event.key.keysym.sym == p2->key.down)
                p2->down.pressed = 1;
            if ((int)event.key.keysym.sym == p2->key.dash)
                p2->dash.pressed = 1;
        }
        else if (event.type == SDL_KEYUP)
        {
            if ((int)event.key.keysym.sym == p1->key.jump)
            {
                p1->jump.released = 1;
                p1->jump.pressed = 0;
            }
            if ((int)event.key.keysym.sym == p1->key.right)
                p1->right.pressed = 0;
            if ((int)event.key.keysym.sym == p1->key.left)
                p1->left.pressed = 0;
            if ((int)event.key.keysym.sym == p1->key.dash)
                p1->dash.pressed = 0;
            p1->dash.released = 1;
            if ((int)event.key.keysym.sym == p1->key.up)
                p1->up.pressed = 0;
            if ((int)event.key.keysym.sym == p1->key.down)
                p1->down.pressed = 0;

            if ((int)event.key.keysym.sym == p2->key.jump)
            {
                p2->jump.released = 1;
                p2->jump.pressed = 0;
            }
            if ((int)event.key.keysym.sym == p2->key.right)
                p2->right.pressed = 0;
            if ((int)event.key.keysym.sym == p2->key.left)
                p2->left.pressed = 0;
            if ((int)event.key.keysym.sym == p2->key.dash)
                p2->dash.pressed = 0;
            p2->dash.released = 1;
            if ((int)event.key.keysym.sym == p2->key.up)
                p2->up.pressed = 0;
            if ((int)event.key.keysym.sym == p2->key.down)
                p2->down.pressed = 0;
        }
    }
}

void player_create(player *p, char *spritesheet/*, char* savefile*/)
{
    save s;
    FILE *f = fopen("keys1.txt", "r");
    if (f != NULL)
    {
        fscanf(f, "%d ", &p->key.jump);
        fscanf(f, "%d ", &p->key.right);
        fscanf(f, "%d ", &p->key.left);
        fscanf(f, "%d ", &p->key.dash);
        fscanf(f, "%d ", &p->key.down);
        fscanf(f, "%d ", &p->key.up);
        fclose(f);
    }
    else
    {
        p->key.jump = SDLK_KP1;
        p->key.right = SDLK_RIGHT;
        p->key.left = SDLK_LEFT;
        p->key.up = SDLK_UP;
        p->key.down = SDLK_DOWN;
        p->key.dash = SDLK_KP2;
    }
    load_img(&p->sprite, spritesheet,0,0);
    load_img(&p->spritemirrored, "img/Potato_walking-mirrored-export.png", 0, 0);
    f = fopen("save.bin", "rb");
    p->lives=3;
    if (f != NULL)
    {
        fread(&s, sizeof(save), 1, f);
        p->lives = s.lives;
        p->respawn_x = s.x1;
        p->respawn_y = s.y1;
        fclose(f);
    }
    p->jump_spd = -7;
    p->canjump = 99999;
    p->facing = 1;
    p->jump.released = 1;
    p->dash.released = 1;
    p->dash_spd = 12;
    p->wlk_spd = 4;
    p->jumping = 0;
    p->dashing = 0;
    p->frame_height = 48;
    p->frame_width = 50;
    p->sprite.pos.w = p->frame_width;
    p->sprite.pos.h = p->frame_height;
    p->framepos.y = 0;
    p->framepos.x = 0;
    p->landing=0;
    p->framepos.h = p->frame_height;
    p->framepos.w = p->frame_width;
    p->framestart = 0;
    p->frames = 0;
    p->wallgrab=0;
}

void player_create2(player *p, char *spritesheet/*, char* savefile*/)
{
    save s;
    FILE *f = fopen("keys2.txt", "r");
    if (f != NULL)
    {
        fscanf(f, "%d ", &p->key.jump);
        fscanf(f, "%d ", &p->key.right);
        fscanf(f, "%d ", &p->key.left);
        fscanf(f, "%d ", &p->key.dash);
        fscanf(f, "%d ", &p->key.down);
        fscanf(f, "%d ", &p->key.up);
        fclose(f);
    }
    else
    {
        p->key.jump = SDLK_j;
        p->key.right = SDLK_d;
        p->key.left = SDLK_q;
        p->key.up = SDLK_z;
        p->key.down = SDLK_s;
        p->key.dash = SDLK_k;
    }
    load_img(&p->sprite, spritesheet, 0, 0);
    load_img(&p->spritemirrored, "img/Potato_walking-mirrored-export.png", 0, 0);
    f = fopen("save.bin", "rb");
    if (f != NULL)
    {
        fread(&s, sizeof(save), 1, f);
        p->lives = s.lives;
        p->respawn_x = s.x2;
        p->respawn_y = s.y2;
        fclose(f);
    }
    p->jump_spd = -7;
    p->canjump = 99999;
    p->facing = 1;
    p->jump.released = 1;
    p->x_spd = 0;
    p->y_spd = 0;
    p->dash.released = 1;
    p->dash_spd = 12;
    p->wlk_spd = 4;
    p->jumping = 0;
    p->dashing = 0;
    p->landing=0;
    p->frame_height = 48;
    p->frame_width = 50;
    p->framepos.y = 0;
    p->framepos.x = 0;
    p->framepos.h = p->frame_height;
    p->framepos.w = p->frame_width;
    p->framestart = 0;
    p->frames = 0;
    p->wallgrab=0;
}

int player_walljump(player * p) {
        if (p -> wallgrab) {
                if (p -> jump.pressed && p -> jump.released) {

                        p -> jump.pressed = 0;
                        p -> jump.released = 0;
                        p -> jumping = 1;
                        p -> canjump -= 1;
                        // p->y_spd=0;
                }
                if (p -> jumping) {
                        p -> x_spd = 5 * p -> facing;
                        p -> y_spd = p -> jump_spd;
                        p -> jumping += 1;
                        if (p -> jumping >= 12 || p -> jump.released)
                                p -> jumping = 0;
                        return 1;
                }
        }
        return (0);
}

int player_jump(player *p)
{
    if (p->canjump >= 1 && p->jump.pressed && p->jump.released)
    {
        p->jump.pressed = 0;
        p->jump.released = 0;
        if (p->jump.released == 0)
            p->jumping = 1;
        p->canjump -= 1;
        // p->y_spd=0;
    } 

    if (p->jumping)
    {
        p->y_spd = p->jump_spd;
        p->jumping += 1;
        if (p->jumping >= 16 || p->jump.released)
            p->jumping = 0;
        return (1);
    }
    else
    {
        return (0);
    }
}

int player_dash(player *p)
{
    int x = p->dashdirx, y = p->dashdiry;
    if (p->dashing)
    {
        if (x == 0 || y == 0)
        {
            p->x_spd = p->dashdirx * p->dash_spd;
            p->y_spd = p->dashdiry * p->dash_spd;
        }
        else
        {
            p->x_spd = p->dashdirx * sqrt((p->dash_spd * p->dash_spd) / 2);
            p->y_spd = p->dashdiry * sqrt((p->dash_spd * p->dash_spd) / 2);
        }
        p->dashing -= 1;
        if (p->dashing == 0 && p->sprite.pos.y != GROUND)
        {
            p->candash = 0;
            if (p->y_spd < 0)
                p->y_spd = -4;
        }
        return (1);
    }
    else
        return (0);
}

void player_calculate_speed(player *p)
{
    if (player_walljump(p));
    else{
    if (p->dash.pressed && p->dash.released && p->candash && !p->dashing)
    {
        p->jumping = 0;
        // p->canjump-=1;
        p->dashing = 10;
        p->dashdirx = p->right.pressed - p->left.pressed;
        p->dashdiry = p->down.pressed - p->up.pressed;
        if (!p->dashdiry)
            p->dashdirx = p->facing;
        p->dash.pressed = 0;
        p->dash.released = 0;
    }
    if (player_dash(p))
        ;
    else
    {
        if (fabsf(p->x_spd) > 0.1)
            p->x_spd *= 0.8;
        else
        {
            p->x_spd = 0;
        }
        p->direction = p->right.pressed - p->left.pressed;
        if (p->direction != 0)
            p->facing = p->direction;
        p->x_spd += (p->direction * p->wlk_spd) / 3;
        if (player_jump(p))
            ;
        else if(p->wallgrab){
            p->y_spd += GRV*0.3;
        }
        else
            (p->y_spd += GRV);
        if(p->wallgrab && p->y_spd>6)
            p->y_spd=6;
        if (p->y_spd > 20)
            p->y_spd = 20;
        if (fabsf(p->x_spd) > p->wlk_spd)
            p->x_spd = p->direction * p->wlk_spd;
    }
    p->wallgrab=0;
    }
    
}

int rect_meeting(int x, int y, SDL_Rect rect1, SDL_Rect rect2)
{
    SDL_Rect translated_rect1;
    translated_rect1.h = rect1.h;
    translated_rect1.x = x;
    translated_rect1.w = rect1.w;
    translated_rect1.y = y;
    int collide = (translated_rect1.x < rect2.x + rect2.w &&
                   translated_rect1.x + translated_rect1.w > rect2.x &&
                   translated_rect1.y < rect2.y + rect2.h &&
                   translated_rect1.y + translated_rect1.h > rect2.y);

    return collide;
}

int player_meeting(player p, img i)
{
    SDL_Rect pl = p.sprite.pos;
    pl.h = p.frame_height;
    pl.w = p.frame_width;
    if (rect_meeting(p.x_spd + p.sprite.pos.x, p.sprite.pos.y + p.y_spd, pl, i.pos))
        return 1;
    return 0;
}

int player_collision_object(player *p, img tile)
{
    int c = 0;
    SDL_Rect pl = p->sprite.pos;
    pl.h = p->frame_height;
    pl.w = p->frame_width;
    if (rect_meeting(p->x_spd + p->sprite.pos.x, p->sprite.pos.y, pl, tile.pos) && p->x_spd!=0)
    {
        if (p->dashing)
        {
            p->dashing = 0;
            p->candash = 0;
        }
        else if(p->y_spd>1){
            p->wallgrab=1;
            p->facing=-p->facing;
        }
        if (tile.pos.x > pl.x)
            p->sprite.pos.x = tile.pos.x - p->frame_width;
        else
            p->sprite.pos.x = tile.pos.x + tile.pos.w;
        p->x_spd = 0;
        p->sprite.pos.x += p->x_spd;
        c = 1;
    }
    if (rect_meeting(p->sprite.pos.x, p->y_spd + p->sprite.pos.y, pl, tile.pos))
    {
        if(p->y_spd>0) p->wallgrab=0;
        if (p->dashing)
        {
            p->dashing = 0;
            p->candash = 0;
        }
        if (tile.pos.y > pl.y)
            p->sprite.pos.y = tile.pos.y - p->frame_height;
        else
            p->sprite.pos.y = tile.pos.y + tile.pos.h;
        if (p->y_spd > 0)
        {
            if(p->canjump<2){
            p->frames=1;
            p->landing=1;
            }
            p->canjump = 2;
            p->candash = 1;
        }
        else if (p->y_spd < 0)
        {
            p->jumping = 0;
        }
        if (p->y_spd >= 0)
        {
            p->respawn_x = p->sprite.pos.x;
            p->respawn_y = p->sprite.pos.y;
        }
        p->y_spd = 0;
        p->sprite.pos.y += p->y_spd;
        c = 1;
    }
    return (c);
}

void player_check_collision(player *p, img *tiles, int size, img *spikes, int size2)
{
    int i = 0;
    /*SDL_Rect pl = p->sprite.pos;
    pl.h = p->frame_height;
    pl.w = p->frame_width;*/
    for (i = 0; i < size; i++)
    {
        player_collision_object(p, tiles[i]);
    }
    for (i = 0; i < size2; i++)
    {
        if (pixel_perfect_collision(p, &spikes[i]))
        {
            p->x_spd = 0;
            p->y_spd = 0;
            p->dashing = 0;
            p->sprite.pos.x = p->respawn_x;
            p->sprite.pos.y = p->respawn_y;
            break;
        }
    }
    /*if(p->y_spd+p->sprite.pos.y>GROUND){
        p->sprite.pos.y=GROUND;
        p->canjump=2;
        p->candash=1;
        p->y_spd=0;
    }
    else if(p->y_spd+p->sprite.pos.y<0){
        p->sprite.pos.y=0;
        p->y_spd=0;
    }
    if(p->x_spd+p->sprite.pos.x + p->framepos.w >SCREEN_W){
        p->sprite.pos.x=SCREEN_W-p->framepos.w;
        p->x_spd=0;
    }
    else if(p->x_spd+p->sprite.pos.x<0){
        p->sprite.pos.x=0;
        p->x_spd=0;
    }*/
}

void player_pos_update(player *p)
{
    p->sprite.pos.x += p->x_spd;
    p->sprite.pos.y += p->y_spd;
}

void player_step(player *p, img *tiles, int size, img *spikes, int size2)
{
    player_calculate_speed(p);
    player_check_collision(p, tiles, size, spikes, size2);
    player_pos_update(p);
    player_animate(p);
}

void player_animate(player *p)
{
    if (p->dashing >= 9 && p->dashing)
    {
        p->framepos.x = 400;
        p->framepos.y = 48;
    }
    else if (p->dashing > 0)
    {
        p->framepos.y = 96;
        p->framepos.x = 0;
    }
    else if (p->wallgrab && p->y_spd>0){
        p->framepos.x=0;
        p->framepos.y=48*3;
    }
    else
    {
        if (p->y_spd < -6)
        {
            p->framepos.x = 100;
            p->framepos.y = 48;
        }
        else if (p->y_spd < -4)
        {
            p->framepos.x = 150;
            p->framepos.y = 48;
        }
        else if (p->y_spd < -2)
        {
            p->framepos.x = 200;
            p->framepos.y = 48;
        }
        else if (p->y_spd <= 0 && p->canjump < 2)
        {
            p->framepos.x = 250;
            p->framepos.y = 48;
        }
        else if (p->y_spd > 2)
        {
            p->framepos.x = 300;
            p->framepos.y = 48;
        }
        else if (p->y_spd > 4)
        {
            p->framepos.x = 350;
            p->framepos.y = 48;
        }
        else
        {
            if (p->x_spd == 0 && p->y_spd == 0 && !p->jumping)
            {
                if (p->landing==1){
                    if(p->frames<=3){
                        p->framepos.y=48;
                        p->framepos.x=350;
                    }
                    else if (p->frames<=8){
                        p->framepos.x=400;
                        p->framepos.x=350;
                    }
                    p->frames+=1;
                    if(p->frames>=9){
                        p->frames=0;
                        p->landing=0;
                    }
                }
                else{
                if (p->frames % 40 >= 19)
                {
                    p->framepos.y = 0;
                    p->framepos.x = 0;
                }
                else
                {
                    p->framepos.y = 48;
                    p->framepos.x = 0;
                }
                p->frames++;
                }
            }
            if (fabsf(p->x_spd) > 1 && p->y_spd == 0)
            {
                //p->landing=0;
                if (p->frames - p->framestart >= 4)
                {
                    p->framepos.y = 0;
                    p->framepos.x = (p->framepos.x + p->frame_width) % 250;
                    p->frames = 0;
                }
                p->frames++;
            }
        }
    }
}

void player_draw(player p, SDL_Surface *screen, camera cam, int a, int mode)
{
    p.sprite.pos.x -= cam.x - (SCREEN_W + ((float)a / 2) * SCREEN_W) / 2 / mode;
    p.sprite.pos.y -= cam.y - SCREEN_H / 2;
    if (p.x_spd > 0)
        SDL_BlitSurface(p.sprite.image, &p.framepos, screen, &p.sprite.pos);
    else if (p.x_spd < 0)
    {
        //p.sprite.pos.x -= 10;
        SDL_BlitSurface(p.spritemirrored.image, &p.framepos, screen, &p.sprite.pos);
    }
    else
    {
        if (p.facing != -1)
            SDL_BlitSurface(p.sprite.image, &p.framepos, screen, &p.sprite.pos);
        else
        {
            //p.sprite.pos.x -= 10;
            SDL_BlitSurface(p.spritemirrored.image, &p.framepos, screen, &p.sprite.pos);
        }
    }
}

void display_sprite(SDL_Surface *screen, img i, camera cam, int mode, int p)
{
    i.pos.x -= cam.x - (SCREEN_W + ((float)p / 2) * SCREEN_W) / 2 / mode;
    i.pos.y -= cam.y - SCREEN_H / 2;
    SDL_BlitSurface(i.image, NULL, screen, &i.pos);
}

void display_sprite_rect(SDL_Surface *screen, img i, camera cam, SDL_Rect rect)
{
    i.pos.x -= cam.x - (rect.w) / 2 + rect.x;
    i.pos.y -= cam.y - (rect.h) / 2 + rect.y;
    SDL_BlitSurface(i.image, NULL, screen, &i.pos);
}

void parse_tiles(player* p1, player *p2, enemy* e, char *map, img *tab, int *size, img *decorations, int *size2, img *enigmes, int *size3, img *spk, int *size4, int *roomwidth, int *roomheight)
{
    //srand(time);
    int i = -1, j = 0;
    char n;
    FILE *f = fopen(map, "r");
    *roomwidth = 0;
    if (f != NULL)
    {
        for (; fscanf(f, "%c ", &n) == 1;)
        {
            i++;
            switch (n)
            {
            case '1':

                load_img(&tab[*size], "img/wall1.png", i * 50, j * 50);
                *size += 1;
                break;
            case '2':

                load_img(&tab[*size], "img/wall2.png", i * 50, j * 50);
                *size += 1;
                break;
            case '3':

                load_img(&tab[*size], "img/wall3.png", i * 50, j * 50);
                *size += 1;
                break;
            case '4':

                load_img(&tab[*size], "img/wall4.png", i * 50, j * 50);
                *size += 1;
                break;
            case '5':

                load_img(&tab[*size], "img/wall5.png", i * 50, j * 50);
                *size += 1;
                break;
            case '6':

                load_img(&tab[*size], "img/wall6.png", i * 50, j * 50);
                *size += 1;
                break;
            case '7':

                load_img(&tab[*size], "img/wall7.png", i * 50, j * 50);
                *size += 1;
                break;
            case '8':

                load_img(&tab[*size], "img/wall8.png", i * 50, j * 50);
                *size += 1;
                break;
            case '9':

                load_img(&tab[*size], "img/wall9.png", i * 50, j * 50);
                *size += 1;
                break;
            case 'r':

                load_img(&decorations[*size2], "img/liquid_tube_bottom.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 's':

                load_img(&decorations[*size2], "img/liquid_tube_top.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 'a':

                load_img(&decorations[*size2], "img/pipe_bottom_left.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 'b':

                load_img(&decorations[*size2], "img/pipe_bottom_right.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 'c':

                load_img(&decorations[*size2], "img/pipe_top_left.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 'd':

                load_img(&decorations[*size2], "img/pipe_top_right.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 'e':

                load_img(&decorations[*size2], "img/pipe_head_top.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 'f':

                load_img(&decorations[*size2], "img/pipe_head_down.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 'g':

                load_img(&decorations[*size2], "img/pipe_head_left.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 'h':

                load_img(&decorations[*size2], "img/pipe_head_right.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 'i':

                load_img(&decorations[*size2], "img/pipe_horizontal.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 'j':

                load_img(&decorations[*size2], "img/pipe_vertical.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 'k':

                load_img(&enigmes[*size3], "img/enigme_objet.png", i * 50, j * 50);
                enigmes[*size3].pos.w = 34;
                enigmes[*size3].pos.h = 58;
                *size3 += 1;
                break;
            case 'n':

                load_img(&spk[*size4], "img/spike.png", i * 50, j * 50);
                spk[*size4].pos.w = 50;
                spk[*size4].pos.h = 50;
                *size4 += 1;
                break;
            case 't':

                load_img(&decorations[*size2], "img/locker.png", i * 50, j * 50);
                *size2 += 1;
                break;
            case 'u':
            
                load_img(&tab[*size], "img/crate.png", i * 50, j * 50);
                *size += 1;
                break;
            case 'q':
                *roomwidth = (*roomwidth > i * 50) ? *roomwidth : i * 50;
                i = -1;
                j++;
                break;
            case 'p':
                p1->respawn_x=i*50;
                p1->x_spd=0;
                p1->y_spd=0;
                p2->respawn_x=i*50;
                p1->respawn_y=j*50;
                p2->respawn_y=j*50;
                p2->x_spd=0;
                p2->y_spd=0;
                break;
            case 'x':
                e->sprite.pos.x=i*50;
                e->sprite.pos.y=j*50;
                break;
            }
        }
        *roomheight = j * 50;
        fclose(f);
    }
}

void display_tiles(SDL_Surface *screen, img *tm, camera cam, int size, int mode, int p)
{
    for (int i = 0; i < size; i++)
    {
        display_sprite(screen, tm[i], cam, mode, p);
    }
}

void display_dec(SDL_Surface *screen, img *tm, camera cam, int size, int mode, int p)
{
    for (int i = 0; i < size; i++)
    {
        display_sprite(screen, tm[i], cam, mode, p);
    }
}

void display_sprite_parallax(SDL_Surface *screen, img i, camera cam, int mode, int p)
{
    i.pos.x -= cam.x / 2 - (SCREEN_W + ((float)p / 2) * SCREEN_W) / 2 / mode;
    i.pos.y -= cam.y - SCREEN_H / 2;
    SDL_BlitSurface(i.image, NULL, screen, &i.pos);
}

void display_lives(player p, SDL_Surface *screen, img im)
{
    for (int i = 0; i < p.lives; i++)
    {
        im.pos.x += 80;
        display_img(screen, im);
    }
}

int pixel_perfect_collision(player *p, img *i)
{
    SDL_Rect player_rect = p->sprite.pos;
    player_rect.w = p->frame_width;
    player_rect.h = p->frame_height;
    player_rect.x += p->x_spd;
    player_rect.y += p->y_spd;
    SDL_Rect image_rect = i->pos;
    if (rect_meeting(player_rect.x, player_rect.y, player_rect, image_rect))
    {

        // Get the pixel data for the player and image.
        Uint8 *player_pixels;
        if (p->facing == 1)
            player_pixels = (Uint8 *)p->sprite.image->pixels;
        else
            player_pixels = (Uint8 *)p->spritemirrored.image->pixels;
        Uint8 *image_pixels = (Uint8 *)i->image->pixels;
        // Loop through each pixel in the player's sprite.
        for (int y = p->framepos.y; y < p->framepos.y + player_rect.h; y++)
        {
            for (int x = p->framepos.x; x < p->framepos.x + player_rect.w; x++)
            {
                // If the current pixel in the player's sprite is not transparent,
                // and the same pixel in the image is not transparent,
                // then there is a collision.
                if (player_pixels[y * player_rect.w + x * p->sprite.image->format->BytesPerPixel] != 0 &&
                    image_pixels[y * image_rect.w + x * p->sprite.image->format->BytesPerPixel] != 0)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}