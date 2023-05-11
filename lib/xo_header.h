#ifndef HEADER_H
#define HEADER_H

#include <SDL/SDL.h>

#define SCREEN_WIDTH 850
#define SCREEN_HEIGHT 413
#define SCREEN_BPP 32

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3
#define BOARD_SIZE (BOARD_WIDTH * BOARD_HEIGHT)
#define EMPTY_CELL 0
#define PLAYER_X 1
#define PLAYER_O 2
#define PLAYER_TURN 0
#define PLAYER_X_TURN 1
#define PLAYER_O_TURN 2

#define CELL_WIDTH (SCREEN_WIDTH / BOARD_WIDTH)
#define CELL_HEIGHT (SCREEN_HEIGHT / BOARD_HEIGHT)

#define NO_WINNER 0

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

int load_files(SDL_Surface** x_img, SDL_Surface** o_img, SDL_Surface** bg_img);

int handle_events(SDL_Surface* screen, SDL_Surface* x_img, SDL_Surface* o_img, SDL_Surface* bg_img, int* board, int* turn);

void draw_board(SDL_Surface* screen, SDL_Surface* x_img, SDL_Surface* o_img, SDL_Surface* bg_img, int* board);

int check_win(int* board);

void clean_up(SDL_Surface* x_img, SDL_Surface* o_img, SDL_Surface* bg_img);
int xo(SDL_Surface *screen);
#endif