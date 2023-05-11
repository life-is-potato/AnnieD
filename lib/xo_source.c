#include "xo_header.h"
#include <SDL/SDL_ttf.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL/SDL_keysym.h>
#include <stdbool.h>

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, clip, destination, &offset);
}

int load_files(SDL_Surface** x_img, SDL_Surface** o_img, SDL_Surface** bg_img)
{
    *x_img = IMG_Load("img/x.png");
    if (*x_img == NULL)
    {
        fprintf(stderr, "Error loading X image: %s\n", SDL_GetError());
        return 1;
    }

    *o_img = IMG_Load("img/o.png");
    if (*o_img == NULL)
    {
        fprintf(stderr, "Error loading O image: %s\n", SDL_GetError());
        return 1;
    }

    *bg_img = IMG_Load("img/bg_2.jpg");
    if (*bg_img == NULL)
    {
        fprintf(stderr, "Error loading background image: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

int handle_events(SDL_Surface* screen, SDL_Surface* x_img, SDL_Surface* o_img, SDL_Surface* bg_img, int* board, int* turn)
{
    int quit = 0;
    SDL_Event event;
    int mouse_x = 0, mouse_y = 0;
    int play_x = -1, play_y = -1;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                mouse_x = event.button.x;
                mouse_y = event.button.y;
                play_x = (mouse_x) / CELL_WIDTH;
                play_y = (mouse_y) / CELL_HEIGHT;
            }
        }

        if (*turn == PLAYER_X_TURN && play_x >= 0 && play_y >= 0 && board[play_x + play_y * BOARD_WIDTH] == EMPTY_CELL)
        {
            board[play_x + play_y * BOARD_WIDTH] = PLAYER_X;
            *turn = PLAYER_O_TURN;
            play_x = -1;
            play_y = -1;
        }
        else if (*turn == PLAYER_O_TURN)
        {
            int empty_count = 0;
            for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
            {
                if (board[i] == EMPTY_CELL)
                {
                    empty_count++;
                }
            }
            if (empty_count == 0)
            {
                quit = 1;
            }
            else
            {
                int random_index = rand() % empty_count;
                int index = 0;
                for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
                {
                    if (board[i] == EMPTY_CELL)
                    {
                        if (index == random_index)
                        {
                            board[i] = PLAYER_O;
                            *turn = PLAYER_X_TURN;
                            break;
                        }
                        index++;
                    }
                }
            }
        }

        draw_board(screen, x_img, o_img, bg_img, board);

        int winner = check_win(board);
        if (winner != EMPTY_CELL)
        {
            quit = 1;
            if (winner == PLAYER_X)
            {
                printf("Player X wins!\n");
            }
            else if (winner == PLAYER_O)
            {
                printf("Player O wins!\n");
            }
            else
            {
                printf("It's a draw!\n");
            }
        }

        SDL_UpdateRect(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_Delay(10);
    }

    return 0;
}

void draw_board(SDL_Surface* screen, SDL_Surface* x_img, SDL_Surface* o_img, SDL_Surface* bg_img, int* board)
{
    apply_surface(0, 0, bg_img, screen, NULL);
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int cell = board[row * 3 + col];
            if (cell == 1)
            {
                apply_surface(col * (SCREEN_WIDTH / 3)+50, row * (SCREEN_HEIGHT / 3)+50, x_img, screen, NULL);
            }
            else if (cell == 2)
            {
                apply_surface(col * (SCREEN_WIDTH / 3)+50, row * (SCREEN_HEIGHT / 3)+50, o_img, screen, NULL);
            }
        }
    }
}

int check_win(int* board)
{
    for (int row = 0; row < 3; row++)
    {
        if (board[row * 3] != 0 && board[row * 3] == board[row * 3 + 1] && board[row * 3] == board[row * 3 + 2])
        {
            return board[row * 3];
        }
    }
    for (int col = 0; col < 3; col++)
    {
        if (board[col] != 0 && board[col] == board[col + 3] && board[col] == board[col + 6])
        {
            return board[col];
        }
    }
    if (board[0] != 0 && board[0] == board[4] && board[0] == board[8])
    {
        return board[0];
    }
    if (board[2] != 0 && board[2] == board[4] && board[2] == board[6])
    {
        return board[2];
    }
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 0)
        {
            return 0;
        }
    }
    return -1;
}

void clean_up(SDL_Surface* x_img, SDL_Surface* o_img, SDL_Surface* bg_img)
{
    if (x_img != NULL)
    {
        SDL_FreeSurface(x_img);
        x_img = NULL;
    }
    if (o_img != NULL)
    {
        SDL_FreeSurface(o_img);
        o_img = NULL;
    }
    if (bg_img != NULL)
    {
        SDL_FreeSurface(bg_img);
        bg_img = NULL;
    }
    SDL_Quit();
}

int xo(SDL_Surface *screen) {
    SDL_Surface* x_img = NULL;
    SDL_Surface* o_img = NULL;
    SDL_Surface* bg_img = NULL;
    if (load_files(&x_img, &o_img, &bg_img) == -1) {
        clean_up(x_img, o_img, bg_img);
        return 1;
    }

    int board[9] = {0};
    int turn = 1;

    int quit = 0;
    while (!quit) {
        quit = handle_events(screen, x_img, o_img, bg_img, board, &turn);

        draw_board(screen, x_img, o_img, bg_img, board);

        int winner = check_win(board);
        if (winner != 0) {
            SDL_Delay(1000);
            char message[30];
            if (winner == 1) {
                sprintf(message, "X wins!");
            }
            else if (winner == 2) {
                sprintf(message, "O wins!");
            }
            else {
                sprintf(message, "Tie game!");
            }
            SDL_WM_SetCaption(message, NULL);
            SDL_Delay(1000);
            quit = 1;
        }
        if (SDL_Flip(screen) == -1) {
            quit = 1;
        }
    }
    //clean_up(x_img, o_img, bg_img);
    return 1;
}