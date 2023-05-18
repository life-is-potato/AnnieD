#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <math.h>
#include "lib/xo_header.h"
#include "lib/game.h"
#include "lib/enigme.h"

int main()
{
    int fps = 31;
    float frames = 0;
    char sframes[10];
    SDL_Surface *screen;
    SDL_Event event;
    Uint32 time, lasttime = 0;
    float dt;

    // images

    img bg, bg2, play, play_s, settings, settings_s, quit, quit_s, gamelogo, settingsbg, bar, back, fullscreen, windowed, ball;

    // text

    txt frm;

    // music/audio

    Mix_Chunk *buttonsfx;
    Mix_Music *maintheme;

    // game variables

    int state = 1;
    int key = 0;
    int mouse_x, mouse_y;
    int sfxplayed_x = 450, sfxplayed_y = 170;
    // Intializing SDL
    if (init() == -1)
    {
        return -1;
    }

    screen = SDL_SetVideoMode(1200, 800, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL)
        return -1;

    // Loading images

    load_img(&bg, "img/bg.png", 0, 0);
    load_img(&bg2, "img/bg2.png", 0, 0);
    load_img(&play, "img/play.png", 450, 170);
    load_img(&play_s, "img/play_s.png", 450, 170);
    load_img(&settings, "img/settings.png", 450, 310);
    load_img(&settings_s, "img/settings_s.png", 450, 310);
    load_img(&quit, "img/quit.png", 450, 430);
    load_img(&quit_s, "img/quit_s.png", 450, 430);
    load_img(&gamelogo, "img/gamelogo.png", 390, 10);
    load_img(&settingsbg, "img/SetBack.png", 430, 120);
    load_img(&bar, "img/barre_volume.png", 440, 350);
    load_img(&back, "img/back.png", 570, 550);
    load_img(&fullscreen, "img/FS.png", 460, 400);
    load_img(&windowed, "img/FS.png", 460, 470);
    load_img(&ball, "img/Boule.png", 730, 345);

    // Loading text

    load_txt(&frm, 100, 100, 255, 255, 255, "fonts/pixel_arial.ttf", 20);

    // Loading music/sounds

    buttonsfx = Mix_LoadWAV("music/SFX_1.wav");
    maintheme = Mix_LoadMUS("music/main_theme.mp3");

    // play main theme

    Mix_PlayMusic(maintheme, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME);

    // gameloop

    while (state)
    {

        // animating and displaying the bg

        time = SDL_GetTicks();
        dt = (time - lasttime) / (float)1000;
        frames += dt * fps;
        sprintf(sframes, "%.00f", frames);
        if ((int)frames % 30 > (fps / 2))
        {
            display_img(screen, bg2);
        }
        else
        {
            display_img(screen, bg);
        }
        if (frames > 0)
            lasttime = time;
        print_txt(screen, &frm, sframes);

        // SDL QUIT

        if (event.type == SDL_QUIT)
        {
            state = 0;
            break;
        }

        // in menu

        if (state == 1)
        {
            display_img(screen, gamelogo);
            if (check_mouse_collision(play) || key == 0)
            {
                display_img(screen, play_s);
                key = 0;
            }
            else
                display_img(screen, play);
            if (check_mouse_collision(settings) || key == 1)
            {
                display_img(screen, settings_s);
                key = 1;
            }
            else
                display_img(screen, settings);
            if (check_mouse_collision(quit) || key == 2)
            {
                display_img(screen, quit_s);
                key = 2;
            }
            else
                display_img(screen, quit);
            while (SDL_PollEvent(&event))
            {

                // On left click

                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (check_mouse_collision(quit))
                    {
                        state = 0;
                        break;
                    }
                    if (check_mouse_collision(play))
                    {
                        state = 2;
                    }
                    if (check_mouse_collision(settings))
                    {
                        state = 3;
                    }
                }

                // On mouse movement

                if (event.type == SDL_MOUSEMOTION)
                {
                    if ((check_mouse_collision(quit) || check_mouse_collision(play) || check_mouse_collision(settings)))
                    {
                        // the big if checks if the button being selected changed, only method i could think of without making 3 cases
                        if (check_button_change(quit, sfxplayed_x, sfxplayed_y) || check_button_change(play, sfxplayed_x, sfxplayed_y) || check_button_change(settings, sfxplayed_x, sfxplayed_y))
                        {
                            Mix_PlayChannel(MIX_DEFAULT_CHANNELS, buttonsfx, 0);
                            SDL_GetMouseState(&mouse_x, &mouse_y);
                            sfxplayed_x = mouse_x;
                            sfxplayed_y = mouse_y;
                        }
                    }
                }

                // On keyboard press

                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_DOWN)
                        key = (key + 4) % 3;
                    else if (event.key.keysym.sym == SDLK_UP)
                        key = (key + 2) % 3;
                    else if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        if (key == 0)
                            state = 2;
                        else if (key == 1)
                            state = 3;
                        else
                            state = 0;
                    }
                }
            }
        }

        // in settings

        else if (state == 3)
        {
            display_img(screen, settingsbg);
            display_img(screen, bar);
            display_img(screen, ball);
            display_img(screen, back);
            display_img(screen, fullscreen);
            display_img(screen, windowed);
            while (SDL_PollEvent(&event))
            {
            }
        }

        // play button

        else if (state == 2)
        {
            screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
            Mix_FadeOutMusic(1000);
            // SDL_FreeSurface(screen);
            state = gameloop(screen,"map1.txt");
            Mix_FreeMusic(maintheme);
            maintheme = Mix_LoadMUS("music/main_theme.mp3");
            Mix_PlayMusic(maintheme, -1);
            screen = SDL_SetVideoMode(1200, 800, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
        }

        else if (state == 4)
        {
            state = xo(screen);
        }
        // refesh screen

        SDL_Flip(screen);
    }

    // free

    free_img(bg);
    free_img(bg2);
    free_img(play);
    free_img(play_s);
    free_img(settings);
    free_img(settings_s);
    free_img(quit);
    free_img(quit_s);
    free_img(gamelogo);
    free_txt(frm);
    Mix_FreeChunk(buttonsfx);
    Mix_FreeMusic(maintheme);
    SDL_Quit();
    TTF_Quit();
}
