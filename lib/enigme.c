#include "functions.h"
#include "enigme.h"
#include <time.h>

void initexte(text *A)
{
    A->position.x = 610;
    A->position.y = 30;
    A->textColor.r = 255;
    A->textColor.g = 255;
    A->textColor.b = 255;

    A->font = TTF_OpenFont("fonts/police.ttf", 20);
}

void displayText(text t, SDL_Surface *screen, const char* cc)
{
    t.surfaceTexte = TTF_RenderText_Solid(t.font, cc, t.textColor);
    SDL_BlitSurface(t.surfaceTexte, NULL, screen, &t.position);
}

void afficher_resultat(SDL_Surface *screen, int s, int r, enigme *en)
{

    if (r == s)
    {
        en->img = IMG_Load("img/win.jpg");
        SDL_BlitSurface(en->img, NULL, screen, &(en->p));
        SDL_Flip(screen);
        SDL_FreeSurface(en->img);
    }
    else
    {
        en->img = IMG_Load("img/lose.jpg");
        SDL_BlitSurface(en->img, NULL, screen, &(en->p));
        SDL_Flip(screen);
        SDL_FreeSurface(en->img);
    }
}

void generate_afficher(int *alea)
{
    int test = *alea;
    srand(SDL_GetTicks());

    do
    {
        *alea = 1 + rand() % 12;
    } while (*alea == test);
}

void init_enigme(enigme *e/*, char *nomfichier*/)
{
    //int j, y;
    int i = 1;
    char nomimage[20];

    e->p.x = 0;
    e->p.y = 0;
    e->img = NULL;

    generate_afficher(&e->num_enigme);

    FILE *f = fopen("enigme.txt", "r");
    if (f != NULL)
    {

        while (fscanf(f, "%s %d\n", nomimage, &e->reponsevrai) != EOF && i != e->num_enigme)
        {
            i++;
        }
        e->img = IMG_Load(nomimage);
        fclose(f);
    }
    else
        printf("ERROR !");

    e->timer[0] = IMG_Load("img/timer/0.gif");
    e->timer[1] = IMG_Load("img/timer/1.gif");
    e->timer[2] = IMG_Load("img/timer/2.gif");
    e->timer[3] = IMG_Load("img/timer/3.gif");
    e->timer[4] = IMG_Load("img/timer/4.gif");
    e->timer[5] = IMG_Load("img/timer/5.gif");
    e->timer[6] = IMG_Load("img/timer/6.gif");
    e->timer[7] = IMG_Load("img/timer/7.gif");
    e->timer[8] = IMG_Load("img/timer/8.gif");
    e->timer[9] = IMG_Load("img/timer/9.gif");

    e->pos_timer.x = 560;
    e->pos_timer.y = 14;
}

int enigme_play(SDL_Surface* screen)
{
    enigme e;
    //Mix_Music* music;
    e.num_enigme = -1;
    int r = 0;
    int running = 0;
    int boucle = 1;
    char cc[30] = "0";
    text tt;

    init_enigme(&e);
    initexte(&tt);
    time_t start, end;
    start = clock();
    int t = 0;//, t0;

    while (boucle)
    {
        SDL_BlitSurface(e.img, NULL, screen, &e.p);
        snprintf(cc, 5, ":0%d", t);
        SDL_BlitSurface(e.timer[t], NULL, screen, &e.pos_timer);
        displayText(tt, screen, cc);
        SDL_Flip(screen);

        end = clock();
        //t0 = t;
        t = (end - start) / CLOCKS_PER_SEC;
        if (t == 10)
        {
            running = 1;
        }

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                boucle = 0;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    // Mix_PlayChannel( -1, son, 0 );
                    r = 1;
                    running = 1;
                    break;
                case SDLK_z:
                    // Mix_PlayChannel( -1, son, 0 );
                    r = 2;
                    running = 1;
                    break;
                case SDLK_e:
                    // Mix_PlayChannel( -1, son, 0 );
                    r = 3;
                    running = 1;
                    break;
                case SDLK_r:
                    // Mix_PlayChannel( -1, son, 0 );
                    r = 4;
                    running = 1;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        while (running)
        {
            afficher_resultat(screen, e.reponsevrai, r, &e);

            SDL_Event event;
            SDL_WaitEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                boucle = 0;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running = 0;
                    boucle = 0;
                    break;
                default:
                    // ignore all other SDLK values
                    break;
                }
            }
        }
    }

    if (r == e.reponsevrai)
        return 1;
    else
        return 0;
}
