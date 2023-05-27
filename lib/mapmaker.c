#include "mapmaker.h"

int create_matrix(img *tiles, int *exist, int size, char mat[50][50])
{
    int i, j;
    for (i = 0; i < 50; i++)
    {
        for (j = 0; j < 49; j++)
        {
            mat[j][i] = '0';
        }
        mat[j][i] = 'q';
    }
    for (i = 0; i < size; i++)
    {
        switch (exist[i])
        {
        case 0:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = '2';
            break;
        case 1:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = '1';
            break;
        case 2:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = '3';
            break;
        case 3:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = '4';
            break;
        case 4:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = '5';
            break;
        case 5:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'a';
            break;
        case 6:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'b';
            break;
        case 7:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'c';
            break;
        case 8:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'd';
            break;
        case 9:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'e';
            break;
        case 10:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'f';
            break;
        case 11:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'g';
            break;
        case 12:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'h';
            break;
        case 13:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'i';
            break;
        case 14:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'j';
            break;
        case 15:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'k';
            break;
        case 16:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'n';
            break;
        case 17:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'p';
            break;
        case 18:
            mat[tiles[i].pos.x / 52][tiles[i].pos.y / 50] = 'x';
            break;
        }
    }
    /*for (i = 0; i < 50; i++)
    {
        for (j = 0; j < 50; j++)
        {
            printf("%c", mat[j][i]);
        }
        printf("\n");
    }
    */
}

int create_file(char mat[50][50], char *filename)
{
    int i, j;
    FILE *f = fopen(filename, "w");
    for (i = 0; i < 50; i++)
    {
        for (j = 0; j < 50; j++)
        {
            fprintf(f, "%c", mat[j][i]);
        }
        fprintf(f, " \n");
    }
    fclose(f);
}

int mapmaker_parser(img *tiles, int *exist, int *size, char *path)
{
    FILE *f = fopen(path, "r");
    if (f != NULL)
    {
        printf("map opened succesfully");
        int i = -1, j = 0;
        char n;
        if (f != NULL)
        {
            for (; fscanf(f, "%c ", &n) == 1;)
            {
                i++;
                switch (n)
                {
                case '1':

                    load_img(&tiles[*size], "img/wall_middle.png", i * 52, j * 50);
                    exist[*size]=1;
                    *size += 1;
                    break;
                case '2':

                    load_img(&tiles[*size], "img/wall_left.png", i * 52, j * 50);
                    exist[*size]=0;
                    *size += 1;
                    break;
                case '3':

                    load_img(&tiles[*size], "img/wall_right.png", i * 52, j * 50);
                    exist[*size]=2;
                    *size += 1;
                    break;
                case '4':

                    load_img(&tiles[*size], "img/liquid_tube_bottom.png", i * 52, j * 50);
                    exist[*size]=3;
                    *size += 1;
                    break;
                case '5':

                    load_img(&tiles[*size], "img/liquid_tube_top.png", i * 52, j * 50);
                    exist[*size]=4;
                    *size += 1;
                    break;
                case 'a':

                    load_img(&tiles[*size], "img/pipe_bottom_left.png", i * 52, j * 50);
                    exist[*size]=5;
                    *size += 1;
                    break;
                case 'b':

                    load_img(&tiles[*size], "img/pipe_bottom_right.png", i * 52, j * 50);
                    exist[*size]=6;
                    *size += 1;
                    break;
                case 'c':
                    load_img(&tiles[*size], "img/pipe_top_left.png", i * 52, j * 50);
                    exist[*size]=7;
                    *size += 1;
                    break;
                case 'd':

                    load_img(&tiles[*size], "img/pipe_top_right.png", i * 52, j * 50);
                    exist[*size]=8;
                    *size += 1;
                    break;
                case 'e':

                    load_img(&tiles[*size], "img/pipe_head_top.png", i * 52, j * 50);
                    exist[*size]=9;
                    *size += 1;
                    break;
                case 'f':

                    load_img(&tiles[*size], "img/pipe_head_down.png", i * 52, j * 50);
                    exist[*size]=10;
                    *size += 1;
                    break;
                case 'g':

                    load_img(&tiles[*size], "img/pipe_head_left.png", i * 52, j * 50);
                    exist[*size]=11;
                    *size += 1;
                    break;
                case 'h':

                    load_img(&tiles[*size], "img/pipe_head_right.png", i * 52, j * 50);
                    exist[*size]=12;
                    *size += 1;
                    break;
                case 'i':

                    load_img(&tiles[*size], "img/pipe_horizontal.png", i * 52, j * 50);
                    exist[*size]=13;
                    *size += 1;
                    break;
                case 'j':

                    load_img(&tiles[*size], "img/pipe_vertical.png", i * 52, j * 50);
                    exist[*size]=14;
                    *size += 1;
                    break;
                case 'k':

                    load_img(&tiles[*size], "img/enigme_objet.png", i * 52, j * 50);
                    exist[*size]=15;
                    *size += 1;
                    break;
                case 'n':

                    load_img(&tiles[*size], "img/spike.png", i * 52, j * 50);
                    exist[*size]=16;
                    *size += 1;
                    break;
                case 'p':
                    load_img(&tiles[*size], "img/potato_maker.png", i * 52, j * 50);
                    exist[*size]=17;
                    *size += 1;
                    break;
                case 'x':
                    load_img(&tiles[*size], "img/skander_maker.png", i * 52, j * 50);
                    exist[*size]=18;
                    *size += 1;
                    break;
                case 'q':
                    i = -1;
                    j++;
                    break;
                }
            }
            fclose(f);
        }
    }
}

int mapmaker(SDL_Surface *screen)
{
    char filename[30];
    printf("give me a filename\n");
    fflush(stdin);
    scanf("%s",filename);
    fflush(stdin);
    int rc=0;
    SDL_Rect fs;
    fs.x = 0;
    fs.y = 0;
    fs.w = SCREEN_W;
    fs.h = SCREEN_H;
    SDL_Rect clip;
    clip.x = 0;
    clip.y = 100;
    clip.w = SCREEN_W;
    clip.h = SCREEN_H - 100;
    int counter;
    int page=0;
    button keys[4];
    for (int i = 0; i < 4; i++)
    {
        keys[i].pressed = 0;
        keys[i].released = 0;
    }
    img selectable_tiles[30];
    img tiles[1000];
    int exist[1000];
    for (int i = 0; i < 1000; i++)
    {
        exist[i] = -1;
    }
    int size = 0;
    int selected = -1;
    camera cam;
    camera mouse;
    cam.x = SCREEN_W / 2;
    cam.y = SCREEN_H / 2 - 100;
    int boucle = 1;
    img blackbar, bg, arrow_left, arrow_right;
    load_img(&blackbar, "img/topbar.png", 0, 0);
    load_img(&bg, "img/bgexp.png", 0, 0);
    load_img(&arrow_left,"img/arrow_left.png",10,10);
    load_img(&arrow_right,"img/arrow_right.png",1150+60,10);
    load_img(&selectable_tiles[0], "img/wall_left.png", 60 +10, 10);
    load_img(&selectable_tiles[1], "img/wall_middle.png", 60 +70, 10);
    load_img(&selectable_tiles[2], "img/wall_right.png", 60 +130, 10);
    load_img(&selectable_tiles[3], "img/liquid_tube_bottom.png", 60 +190, 10);
    load_img(&selectable_tiles[4], "img/liquid_tube_top.png", 60 +250, 10);
    load_img(&selectable_tiles[5], "img/pipe_bottom_left.png", 60 +310, 10);
    load_img(&selectable_tiles[6], "img/pipe_bottom_right.png", 60 +370, 10);
    load_img(&selectable_tiles[7], "img/pipe_top_left.png", 60 +430, 10);
    load_img(&selectable_tiles[8], "img/pipe_top_right.png", 60 +490, 10);
    load_img(&selectable_tiles[9], "img/pipe_head_top.png", 60 +550, 10);
    load_img(&selectable_tiles[10], "img/pipe_head_down.png", 60 +610, 10);
    load_img(&selectable_tiles[11], "img/pipe_head_left.png", 60 +670, 10);
    load_img(&selectable_tiles[12], "img/pipe_head_right.png", 60 +730, 10);
    load_img(&selectable_tiles[13], "img/pipe_horizontal.png", 60 +790, 10);
    load_img(&selectable_tiles[14], "img/pipe_vertical.png", 60 +850, 10);
    load_img(&selectable_tiles[15], "img/enigme_objet.png", 60 +910, 10);
    load_img(&selectable_tiles[16], "img/spike.png",60 + 970, 10);
    load_img(&selectable_tiles[17], "img/potato_maker.png", 60 +1030, 10);
    load_img(&selectable_tiles[18], "img/skander_maker.png", 60 +1090, 10);
    load_img(&selectable_tiles[19], "img/crate.png", 60 +10, 10);
    load_img(&selectable_tiles[20], "img/locker.png", 60+70, 10);
    mapmaker_parser(tiles, exist, &size, filename);
    SDL_Event event;
    while (boucle)
    {
        mouse.x = -1;
        mouse.y = -1;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT){
                    rc=1;
                    mouse.x = event.motion.x;
                    mouse.y = event.motion.y;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                rc=0;
                mouse.x=-1;
                mouse.y=-1;    
                break;
            case SDL_MOUSEMOTION:
                if(rc==1){
                    mouse.x = event.motion.x;
                    mouse.y = event.motion.y;
                }
                break;
            
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    keys[0].pressed = 1;
                    keys[0].released = 1;
                    break;
                case SDLK_LEFT:
                    keys[1].pressed = 1;
                    keys[1].released = 1;
                    break;
                case SDLK_UP:
                    keys[2].pressed = 1;
                    keys[1].released = 1;
                    break;
                case SDLK_DOWN:
                    keys[3].pressed = 1;
                    keys[1].released = 1;
                    break;
                case SDLK_RETURN:
                    boucle = 0;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    keys[0].released = 1;
                    keys[0].pressed = 0;
                    break;
                case SDLK_LEFT:
                    keys[1].released = 1;
                    keys[1].pressed = 0;
                    break;
                case SDLK_UP:
                    keys[2].released = 1;
                    keys[2].pressed = 0;
                    break;
                case SDLK_DOWN:
                    keys[3].released = 1;
                    keys[3].pressed = 0;
                    break;
                }
            }
        }

        // handling camera
        if (keys[0].pressed == 1)
            cam.x += 4;
        if (keys[1].pressed == 1)
            cam.x -= 4;
        if (keys[2].pressed == 1)
            cam.y -= 4;
        if (keys[3].pressed == 1)
            cam.y += 4;
        if (cam.x > bg.image->w - SCREEN_W / 2)
            cam.x = bg.image->w - SCREEN_W / 2;
        else if (cam.x < SCREEN_W / 2)
            cam.x = SCREEN_W / 2;
        if (cam.y > bg.image->h - SCREEN_H / 2)
            cam.y = bg.image->h - SCREEN_H / 2;
        else if (cam.y < (SCREEN_H / 2)-100)
            cam.y = SCREEN_H / 2-100;

        // handling mouse clicks

        if (mouse.x != -1 && mouse.y != -1)
        {
            if (mouse.y < 100)selected = -1;
            // checks page
            if(event.type==SDL_MOUSEBUTTONDOWN){
                if (check_point_collision(arrow_left, mouse.x, mouse.y)){
                    page--;
                }
                else if (check_point_collision(arrow_right, mouse.x, mouse.y)){
                    page++;
                }
                if (page>1)page=1;
                else if(page<0)page=0;
            }


            for (int i = 0; i < 19; i++)
            {
                if(page==1 && i==2)break;
                if (check_point_collision(selectable_tiles[i+page*19], mouse.x, mouse.y))
                {
                    selected = i+page*19;
                    break;
                }
            }

            camera mousecam;
            mousecam.x = mouse.x + cam.x - SCREEN_W / 2;
            mousecam.y = mouse.y + cam.y - SCREEN_H / 2;
            mousecam.x = (mousecam.x / 52) * 52;
            mousecam.y = (mousecam.y / 50) * 50;
            if (mouse.y > 100 && selected == -1)
            {
                for (counter = 0; counter < size; counter++)
                {
                    if (mousecam.x == tiles[counter].pos.x && mousecam.y == tiles[counter].pos.y)
                    {
                        for (int i = counter; i < size; i++)
                        {
                            tiles[i] = tiles[i + 1];
                            exist[i] = exist[i + 1];
                        }
                        size--;
                        break;
                    }
                }
            }
            else if (mouse.y > 100 && selected != -1)
            {
                if (selected == 17 || selected == 18)
                {
                    for (int i = 0; i < size; i++)
                    {
                        if (exist[i] == selected)
                        {
                            for (int j = i; j < size; j++)
                            {
                                tiles[j] = tiles[j + 1];
                                exist[j] = exist[j + 1];
                            }
                            size--;
                            break;
                        }
                    }
                }
                for (counter = 0; counter < size; counter++)
                {
                    if (mousecam.x == tiles[counter].pos.x && mousecam.y == tiles[counter].pos.y)
                    {
                        break;
                    }
                }
                // load_img(&tiles[counter],"img/wall_left.png",(mousecam.x/52)*52,(mousecam.y/50)*50);
                // free_img(tiles[counter]);
                if (selected == 0)
                    load_img(&tiles[counter], "img/wall_left.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 1)
                    load_img(&tiles[counter], "img/wall_middle.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 2)
                    load_img(&tiles[counter], "img/wall_right.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 3)
                    load_img(&tiles[counter], "img/liquid_tube_bottom.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 4)
                    load_img(&tiles[counter], "img/liquid_tube_top.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 5)
                    load_img(&tiles[counter], "img/pipe_bottom_left.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 6)
                    load_img(&tiles[counter], "img/pipe_bottom_right.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 7)
                    load_img(&tiles[counter], "img/pipe_top_left.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 8)
                    load_img(&tiles[counter], "img/pipe_top_right.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 9)
                    load_img(&tiles[counter], "img/pipe_head_top.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 10)
                    load_img(&tiles[counter], "img/pipe_head_down.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 11)
                    load_img(&tiles[counter], "img/pipe_head_left.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 12)
                    load_img(&tiles[counter], "img/pipe_head_right.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 13)
                    load_img(&tiles[counter], "img/pipe_horizontal.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 14)
                    load_img(&tiles[counter], "img/pipe_vertical.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 15)
                    load_img(&tiles[counter], "img/enigme_objet.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 16)
                    load_img(&tiles[counter], "img/spike.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 17)
                    load_img(&tiles[counter], "img/potato_maker.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 18)
                    load_img(&tiles[counter], "img/skander_maker.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 19)
                    load_img(&tiles[counter], "img/crate.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);
                else if (selected == 20)
                    load_img(&tiles[counter], "img/locker.png", (mousecam.x / 52) * 52, (mousecam.y / 50) * 50);    
                if (counter == size)
                    size++;
                exist[counter] = selected;
            }
        }

        // displaying stuff
        SDL_SetClipRect(screen, &fs);
        display_sprite(screen, bg, cam, 1, 0);
        display_tiles(screen, tiles, cam, size, 1, 0);
        SDL_SetClipRect(screen, NULL);
        display_img(screen, blackbar);
        display_img(screen,arrow_left);
        display_img(screen,arrow_right);
        for (int i = 0; i < 19; i++)
        {
            if(page==1 && i==2)break;
            display_img(screen, selectable_tiles[i+page*19]);
        }
        SDL_Flip(screen);
    }
    char mat[50][50];
    create_matrix(tiles, exist, size, mat);
    create_file(mat, filename);
    return (1);
}