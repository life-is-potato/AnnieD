#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#define GROUND 300

typedef struct {
    Uint32 time;
    int x1,y1,x2,y2;
}save;

typedef struct
{
    int x, y;
} camera;

typedef struct
{
    int pressed, released;
} button;

typedef struct
{
    int up, down, left, right, jump, dash, interact;
} controls;

typedef struct
{
    controls key;
    img sprite, spritemirrored;
    button right, left, jump, down, up, dash, interact;
    float x_spd, y_spd;
    int canjump, direction;
    int jump_spd, wlk_spd, dash_spd;
    int jumping;
    int dashing;
    int candash;
    int dashdirx, dashdiry;
    int frame_width, frame_height;
    int framestart;
    int frames;
    int facing;
    SDL_Rect framepos;
} player;

int rect_meeting(int x, int y, SDL_Rect rect1, SDL_Rect rect2);

void update_camera(img img1, img img2, camera *cam, int* mode);

void players_get_inputs(player *p1, player *p2, int *boucle);

void player_import_controls(player *p, char *url);

void player_create(player *p, char *spritesheet, save savefile);

void player_create2(player *p, char *spritesheet, save savefile);

void player_calculate_speed(player *p);

void player_check_collision(player *p, camera cam, img *tiles, int size);

void player_pos_update(player *p);

void player_step(player *p, camera cam, img *tiles, int size);

void player_animate(player *p);

void player_draw(player p, SDL_Surface *screen, camera cam, int a, int mode);

void display_sprite(SDL_Surface *screen, img i, camera cam, int mode, int p);

void parse_tiles(char *map, img *tab, int *size);

void display_tiles(SDL_Surface *screen, img *tm, camera cam, int size, int mode, int p);