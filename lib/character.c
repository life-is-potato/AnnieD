#include "functions.h"
#include "character.h"
#include <stdlib.h>
#include <math.h>

void update_camera(img img1, img img2, camera *cam)
{
    cam->x += ((img1.pos.x + img2.pos.x + 50) / 2 - cam->x) / 20;
    cam->y += ((img1.pos.y + img2.pos.y) / 2 - cam->y) / 20;
    // cam->x=img.pos.x;
    // cam->y=img.pos.y;
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

            if (event.key.keysym.sym == p1->key.jump)
                p1->jump.pressed = 1;
            if (event.key.keysym.sym == p1->key.right)
                p1->right.pressed = 1;
            if (event.key.keysym.sym == p1->key.left)
                p1->left.pressed = 1;
            if (event.key.keysym.sym == p1->key.up)
                p1->up.pressed = 1;
            if (event.key.keysym.sym == p1->key.down)
                p1->down.pressed = 1;
            if (event.key.keysym.sym == p1->key.dash)
                p1->dash.pressed = 1;
            if (event.key.keysym.sym == p2->key.jump)
                p2->jump.pressed = 1;
            if (event.key.keysym.sym == p2->key.right)
                p2->right.pressed = 1;
            if (event.key.keysym.sym == p2->key.left)
                p2->left.pressed = 1;
            if (event.key.keysym.sym == p2->key.up)
                p2->up.pressed = 1;
            if (event.key.keysym.sym == p2->key.down)
                p2->down.pressed = 1;
            if (event.key.keysym.sym == p2->key.dash)
                p2->dash.pressed = 1;
        }
        else if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == p1->key.jump)
            {
                p1->jump.released = 1;
                p1->jump.pressed = 0;
            }
            if (event.key.keysym.sym == p1->key.right)
                p1->right.pressed = 0;
            if (event.key.keysym.sym == p1->key.left)
                p1->left.pressed = 0;
            if (event.key.keysym.sym == p1->key.dash)
                p1->dash.pressed = 0;
            if (event.key.keysym.sym == p1->key.up)
                p1->up.pressed = 0;
            if (event.key.keysym.sym == p1->key.down)
                p1->down.pressed = 0;

            if (event.key.keysym.sym == p2->key.jump)
            {
                p2->jump.released = 1;
                p2->jump.pressed = 0;
            }
            if (event.key.keysym.sym == p2->key.right)
                p2->right.pressed = 0;
            if (event.key.keysym.sym == p2->key.left)
                p2->left.pressed = 0;
            if (event.key.keysym.sym == p2->key.dash)
                p2->dash.pressed = 0;
            if (event.key.keysym.sym == p2->key.up)
                p2->up.pressed = 0;
            if (event.key.keysym.sym == p2->key.down)
                p2->down.pressed = 0;
        }
    }
}

void player_create(player *p, char *spritesheet,save savefile)
{
    load_img(&p->sprite, spritesheet, savefile.x1, savefile.y1);
    load_img(&p->spritemirrored, "img/Potato_walking-mirrored-export.png", savefile.x1, savefile.y1);
    p->jump_spd = -7;
    p->canjump = 99999;
    p->key.jump = SDLK_w;
    p->key.right = SDLK_RIGHT;
    p->key.left = SDLK_LEFT;
    p->key.up = SDLK_UP;
    p->key.down = SDLK_DOWN;
    p->key.dash = SDLK_c;
    p->facing = 1;
    p->jump.released = 1;
    p->dash_spd = 12;
    p->wlk_spd = 4;
    p->jumping = 0;
    p->dashing = 0;
    p->frame_height = 48;
    p->frame_width = 50;
    p->framepos.y = 0;
    p->framepos.x = 0;
    p->framepos.h = p->frame_height;
    p->framepos.w = p->frame_width;
    p->framestart = 0;
    p->frames = 0;
}

void player_create2(player *p, char *spritesheet, save savefile)
{
    load_img(&p->sprite, spritesheet, savefile.x2, savefile.y2);
    load_img(&p->spritemirrored, "img/Potato_walking-mirrored-export.png", savefile.x2, savefile.y2);
    p->jump_spd = -7;
    p->canjump = 99999;
    p->key.jump = SDLK_j;
    p->key.right = SDLK_d;
    p->key.left = SDLK_q;
    p->key.up = SDLK_z;
    p->key.down = SDLK_s;
    p->key.dash = SDLK_k;
    p->facing = 1;
    p->jump.released = 1;
    p->dash_spd = 12;
    p->wlk_spd = 4;
    p->jumping = 0;
    p->dashing = 0;
    p->frame_height = 48;
    p->frame_width = 50;
    p->framepos.y = 0;
    p->framepos.x = 0;
    p->framepos.h = p->frame_height;
    p->framepos.w = p->frame_width;
    p->framestart = 0;
    p->frames = 0;
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
    if (p->dash.pressed && p->candash && !p->dashing)
    {
        p->jumping = 0;
        // p->canjump-=1;
        p->dashing = 10;
        p->dashdirx = p->right.pressed - p->left.pressed;
        p->dashdiry = p->down.pressed - p->up.pressed;
        if (!p->dashdiry)
            p->dashdirx = p->facing;
    }
    if (player_dash(p))
        ;
    else
    {
        if (abs(p->x_spd) > 0.1)
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
        else
            (p->y_spd += GRV);
        if (p->y_spd > 20)
            p->y_spd = 20;
        if (abs(p->x_spd) > p->wlk_spd)
            p->x_spd = p->direction * p->wlk_spd;
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

void player_check_collision(player *p, camera cam, img *tiles, int size)
{
    int i = 0;
    SDL_Rect pl = p->sprite.pos;
    pl.h = p->frame_height;
    pl.w = p->frame_width;
    for (i = 1; i <= size; i++)
    {
        tiles[i].pos.w = tiles[i].image->w;
        tiles[i].pos.h = tiles[i].image->h;
        if (rect_meeting(p->x_spd + p->sprite.pos.x, p->sprite.pos.y, pl, tiles[i].pos))
        {
            if (p->dashing)
            {
                p->dashing = 0;
                p->candash = 0;
            }
            if (tiles[i].pos.x > pl.x)
                p->sprite.pos.x = tiles[i].pos.x - p->frame_width;
            else
                p->sprite.pos.x = tiles[i].pos.x + tiles[i].pos.w;
            p->x_spd = 0;
            p->sprite.pos.x += p->x_spd;
        }
        if (rect_meeting(p->sprite.pos.x, p->y_spd + p->sprite.pos.y, pl, tiles[i].pos))
        {
            if (p->dashing)
            {
                p->dashing = 0;
                p->candash = 0;
            }
            if (tiles[i].pos.y > pl.y)
                p->sprite.pos.y = tiles[i].pos.y - p->frame_height;
            else
                p->sprite.pos.y = tiles[i].pos.y + tiles[i].pos.h;
            if (p->y_spd > 0)
            {
                p->canjump = 2;
                p->candash = 1;
            }
            p->y_spd = 0;
            p->sprite.pos.y += p->y_spd;
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

void player_step(player *p, camera cam, img *tiles, int size)
{
    player_calculate_speed(p);
    player_check_collision(p, cam, tiles, size);
    player_pos_update(p);
    player_animate(p);
}

void player_animate(player *p)
{
    if (p->dashing >= 12)
    {
        p->framepos.x = 0;
        p->framepos.y = 96;
    }
    else if (p->dashing > 0)
    {
        p->framepos.x = 50;
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
            if (abs(p->x_spd) > 1 && p->y_spd == 0)
            {
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

void player_draw(player p, SDL_Surface *screen, camera cam)
{
    p.sprite.pos.x -= cam.x - SCREEN_W / 2;
    p.sprite.pos.y -= cam.y - SCREEN_H / 2;
    if (p.x_spd > 0)
        SDL_BlitSurface(p.sprite.image, &p.framepos, screen, &p.sprite.pos);
    else if (p.x_spd < 0)
    {
        p.sprite.pos.x -= 10;
        SDL_BlitSurface(p.spritemirrored.image, &p.framepos, screen, &p.sprite.pos);
    }
    else
    {
        if (p.facing != -1)
            SDL_BlitSurface(p.sprite.image, &p.framepos, screen, &p.sprite.pos);
        else
        {
            p.sprite.pos.x -= 10;
            SDL_BlitSurface(p.spritemirrored.image, &p.framepos, screen, &p.sprite.pos);
        }
    }
}

int player_collide(player p, img i)
{
    SDL_Rect rect1;
    rect1.x = p.sprite.pos.x;
    rect1.y = p.sprite.pos.y;
    rect1.w = p.frame_width;
    rect1.h = p.frame_height;
    return (place_meeting(i.pos, rect1));
}

void display_sprite(SDL_Surface *screen, img i, camera cam)
{
    i.pos.x -= cam.x - SCREEN_W / 2;
    i.pos.y -= cam.y - SCREEN_H / 2;
    SDL_BlitSurface(i.image, NULL, screen, &i.pos);
}

void parse_tiles(char *map, img *tab, int *size)
{
    int i = -1, j = 0;
    char n;
    FILE *f = fopen(map, "r");
    if (f != NULL)
    {
        for (; fscanf(f, "%c ", &n) == 1;)
        {
            i++;
            if (n == '1')
            {
                *size += 1;
                load_img(&tab[*size], "wall.png", i * 53, j * 50);
            }
            else if (n == 'q')
            {
                i = -1;
                j++;
            }
        }
        fclose(f);
    }
    /*for(i=0;i<x;i++){
        for(j=0;j<y;j++){
            if(map[i][j]==1){
                load_img(&tm[n],"wall.png",i*53,j*50);
                n++;
            }
        }
    }
    */
}

void display_tiles(SDL_Surface *screen, img *tm, camera cam, int size)
{
    for (int i = 0; i <= size; i++)
    {
        display_sprite(screen, tm[i], cam);
    }
}