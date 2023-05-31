#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TEXT_SIZE 24

void cleanup(SDL_Surface* screen, SDL_Surface* textSurface, TTF_Font* font) {
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

void renderText(SDL_Surface* screen,SDL_Surface* textSurface, TTF_Font* font,int textLength, char* text) {
    SDL_Color textColor = { 255, 255, 255 , 0}; // White color

    if (textSurface) {
        SDL_FreeSurface(textSurface);
        textSurface = NULL;
    }

    if (textLength > 0) {
        textSurface = TTF_RenderText_Solid(font, text, textColor);
        if (!textSurface) {
            printf("Error rendering text: %s\n", TTF_GetError());
            cleanup(screen,textSurface,font);
            exit(1);
        }
    }

    SDL_Rect textPosition;
    textPosition.x = (SCREEN_WIDTH - (textSurface ? textSurface->w : 0)) / 2;
    textPosition.y = (SCREEN_HEIGHT - (textSurface ? textSurface->h : 0)) / 2;

    SDL_FillRect(screen, NULL, 0);
    if (textSurface) {
        SDL_BlitSurface(textSurface, NULL, screen, &textPosition);
    }
    SDL_Flip(screen);
} 


char* textgui(SDL_Surface* screen) {
    SDL_Surface* textSurface = NULL;
    TTF_Font* font = NULL;
    SDL_Event event;
    bool running = true;
    char* text = NULL;
    int textLength = 0;
    font = TTF_OpenFont("fonts/pixel_arial.ttf", TEXT_SIZE);
    if (!font) {
        printf("Error loading font: %s\n", TTF_GetError());
        cleanup(screen,textSurface,font);
        return NULL;
    }

    text = (char*)malloc(sizeof(char) * (textLength + 1));
    if (!text) {
        printf("Error allocating memory for text.\n");
        cleanup(screen,textSurface,font);
        return NULL;
    }
    text[0] = '\0'; // Initialize as empty string

    renderText(screen,textSurface,font,textLength,text);

    while (running) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    if (textLength > 0) {
                        textLength--;
                        text[textLength] = '\0';
                        renderText(screen,textSurface,font,textLength,text);
                    }
                }
                else if (event.key.keysym.sym == SDLK_RETURN) {
                    running=0;
                }
                else if (event.key.keysym.sym >= SDLK_SPACE && event.key.keysym.sym <= SDLK_z) {
                    if (textLength < SCREEN_WIDTH / (TEXT_SIZE / 2)) {
                        textLength++;
                        text = (char*)realloc(text, sizeof(char) * (textLength + 1));
                        if (!text) {
                            printf("Error reallocating memory for text.\n");
                            cleanup(screen,textSurface,font);
                            return NULL;
                        }
                        strncat(text, (char*)&event.key.keysym.sym, 1);
                        renderText(screen,textSurface,font,textLength,text);
                    }
                }
            }
        }
    }
    cleanup(screen,textSurface,font);
    return(text);
    return 0;
}
