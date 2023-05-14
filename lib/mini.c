#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "functions.h"
#include "img.h"
#include "mini.h"
#include "text.h"

void init_minimap(minimap *mm, char *path, SDL_Surface *screen)
{
    mm->img.image = IMG_Load(path);
    if (mm->img.image == NULL)
        printf("Unable to load image %s \n", SDL_GetError());
    mm->img.pos.x = screen->w - mm->img.image->w;
    mm->img.pos.y = screen->w - mm->img.image->w;
    SDL_SetAlpha(mm->img.image,SDL_SRCALPHA,128);
}

void init_miniplayer(miniplayer *mp, char *path)
{
    mp->img.image = IMG_Load(path);
    if (mp->img.image == NULL)
        printf("Unable to load image %s \n", SDL_GetError());
}

void update_miniplayer(minimap *mm, miniplayer *mp, player *player, SDL_Surface *screen, camera cam)
{
    float scale_factor = (float)mm->img.image->w / (float)screen->w;
    // mp->img.pos.x = player->sprite.pos.x * scale_factor + mm->img.pos.x;
    // mp->img.pos.y = player->sprite.pos.y * scale_factor + mm->img.pos.y;
    mp->img.pos.x = (player->sprite.pos.x -(cam.x - SCREEN_W/2)) * scale_factor;
    mp->img.pos.y = (player->sprite.pos.y -(cam.y - SCREEN_H/2)) * scale_factor;
    SDL_BlitSurface(mp->img.image, NULL, screen, &mp->img.pos);
}

void update_minienemy(minimap *mm, miniplayer *mp, enemy *player, SDL_Surface *screen, camera cam)
{
    float scale_factor = (float)mm->img.image->w / (float)screen->w;
    // mp->img.pos.x = player->sprite.pos.x * scale_factor + mm->img.pos.x;
    // mp->img.pos.y = player->sprite.pos.y * scale_factor + mm->img.pos.y;
    mp->img.pos.x = (player->sprite.pos.x-(cam.x - SCREEN_W/2)) * scale_factor;
    mp->img.pos.y = (player->sprite.pos.y-(cam.y - SCREEN_H/2)) * scale_factor;
    SDL_BlitSurface(mp->img.image, NULL, screen, &mp->img.pos);
}


void update_tiles(minimap *mm, miniplayer* tile, int size, img* tm, SDL_Surface *screen, camera cam)
{
    float scale_factor = (float)mm->img.image->w / (float)screen->w;
    // mp->img.pos.x = player->sprite.pos.x * scale_factor + mm->img.pos.x;
    // mp->img.pos.y = player->sprite.pos.y * scale_factor + mm->img.pos.y;
    for(int i=0;i<size;i++){
    tile->img.pos.x = (tm[i].pos.x -(cam.x - SCREEN_W/2)) * scale_factor;
    tile->img.pos.y = (tm[i].pos.y -(cam.y - SCREEN_H/2)) * scale_factor;
    SDL_BlitSurface(tile->img.image, NULL, screen, &tile->img.pos);
    }
}

/*void update_minienemy(minimap *mm, player *enemy, int NumEn, int pause, SDL_Surface *screen){
    float scale_factor = (float) mm->img.image->w / (float) screen->w;
    if(!pause){
        SDL_Rect enemy_pos;
        for (int i = 0; i < NumEn; i++) {
            enemy_pos.x = (int)(enemy[i].sprite.pos.x / scale_factor);
            enemy_pos.y = (int)(enemy[i].sprite.pos.y / scale_factor);
            enemy_pos.w = (int)(enemy[i].sprite.image->w / scale_factor);
            enemy_pos.h = (int)(enemy[i].sprite.image->h / scale_factor);

            SDL_Surface* minimap_surf = mm->img.image;
            Uint32 red_color = SDL_MapRGB(minimap_surf->format, 255, 0, 0);
            filledCircleColor(minimap_surf, enemy_pos.x + enemy_pos.w / 2, enemy_pos.y + enemy_pos.h / 2, enemy_pos.w / 2, red_color);
        }

        SDL_BlitSurface(mm->img.image, NULL, screen, &mm->img.pos);
    }
}*/

void update_time(int pause, minimap *mm, Uint32 *start_time, txt *timertxt, SDL_Surface *screen, save savefile, Uint32 starttime2)
{
    char time_str[20];
    if (!pause)
    {
        Uint32 current_time = SDL_GetTicks()-starttime2;
        Uint32 elapsed_time = (savefile.time + (current_time - (*start_time))) / 1000;
        sprintf(time_str, "%02d:%02d", elapsed_time / 60, elapsed_time % 60);
        print_txt(screen, timertxt, time_str);
    }
    else
    {
        (*start_time) = SDL_GetTicks();
    }
}

void minimap_maker(minimap *mm, SDL_Surface *screen, img *Tiles, int TilesNum, int pause)
{
    float scale_factor = (float)mm->img.image->w / (float)screen->w;
    if (!pause)
    {
        for (int i = 0; i < TilesNum; i++)
        {
            int x = (int)(Tiles[i].pos.x / scale_factor);
            int y = (int)(Tiles[i].pos.y / scale_factor);
            int w = (int)(Tiles[i].image->w / scale_factor);
            int h = (int)(Tiles[i].image->h / scale_factor);
            SDL_Rect tile_rect = {x, y, w, h};
            SDL_FillRect(mm->img.image, &tile_rect, SDL_MapRGB(screen->format, 0, 255, 0));
        }
        SDL_BlitSurface(mm->img.image, NULL, screen, &(mm->img.pos));
    }
}
