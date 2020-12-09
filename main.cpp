#include <iostream>
#include <vector>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include "wall.h"

using namespace std;

ifstream f("walls.in");

vector<wall> collision;
int nWalls;

const int playerWidth = 10;
const int playerHeight = 10;
int playerStartX = 50;
int playerStartY = 30;

const int speed = 300;

void read_walls()
{
    for(int i = 0; i < nWalls; ++i){
        int x,y,w,h;
        f >> x >> y >> w >> h;
        wall aux(x,y,w,h);
        collision.push_back(aux);
    }
}


int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("%s", TTF_GetError());
    }
    /*if(TTF_Init() != 0){
        printf("error");
    }*/

    SDL_Window* win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    SDL_Renderer* render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 82, 26, 52, 255);
    //CREATING THE PLAYER
    SDL_Surface* playerSurface;
    playerSurface = IMG_Load("untitled.png");
    //SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
    SDL_Texture* playerTex = SDL_CreateTextureFromSurface(render, playerSurface);
    SDL_FreeSurface(playerSurface);
    SDL_Rect dest;
    SDL_QueryTexture(playerTex, NULL, NULL, &dest.w, &dest.h);

    SDL_Surface* endSquare;
    endSquare = SDL_CreateRGBSurface(0, 10, 10, 32, 0, 0, 0, 0);
    SDL_FillRect(endSquare, NULL, SDL_MapRGB(endSquare->format, 0, 255, 0));
    SDL_Texture* endSqTex = SDL_CreateTextureFromSurface(render, endSquare);
    SDL_FreeSurface(endSquare);
    SDL_Rect endpoz;
    SDL_QueryTexture(endSqTex, NULL, NULL, &endpoz.w, &endpoz.h);
    endpoz.w = 10;
    endpoz.h = 10;

    // sets initial x-position of object
    endpoz.x = 790;

    // sets initial y-position of object
    endpoz.y = 790;

    SDL_Surface* endSurface;
    endSurface = IMG_Load("end.png");
    SDL_Texture* endTex = SDL_CreateTextureFromSurface(render, endSurface);
    SDL_FreeSurface(endSurface);
    SDL_Rect endScreen;
    SDL_QueryTexture(endTex, NULL, NULL, &endScreen.w, &endScreen.h);

    vector <SDL_Texture*> tex;

    SDL_Surface* surface;
    f >> nWalls;
    SDL_Rect* d = new SDL_Rect[nWalls];
    for(int i = 0; i < nWalls; ++i){
        surface = SDL_CreateRGBSurface(0, 10, 10, 32, 0, 0, 0, 0);
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
        //surface = SDL_CreateRGBSurface(0, 30, 100, 32, 0, 30, 0, 0);
        SDL_Texture* t = SDL_CreateTextureFromSurface(render, surface);
        SDL_FreeSurface(surface);
        tex.push_back(t);
        SDL_QueryTexture(tex[i], NULL, NULL, &d[i].w, &d[i].h);
    }

    read_walls();
    for(int i = 0; i < nWalls; ++i){
        d[i].x = collision[i].get_x();
        d[i].y = collision[i].get_y();
        d[i].w = collision[i].get_w();
        d[i].h = collision[i].get_h();
    }

    /*TTF_Font* Sans = TTF_OpenFont("sans.ttf", 24);
    if(!Sans) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
   // handle error
}
    TTF_CloseFont(Sans);
    SDL_Color White = {255,255,255};

    SDL_Surface* message = TTF_RenderText_Solid(Sans, "SCORE", White);
    SDL_Texture* mess = SDL_CreateTextureFromSurface(render, message);
    SDL_DestroyTexture(mess);
    SDL_FreeSurface(message);
    SDL_Rect mess_rect;
    mess_rect.x = 400;
    mess_rect.y = 200;
    mess_rect.w = 100;
    mess_rect.h = 100;
*/

    dest.w = playerWidth;
    dest.h = playerHeight;

    // sets initial x-position of object
    dest.x = playerStartX;

    // sets initial y-position of object
    dest.y = playerStartY;

    // controls annimation loop
    int close = 0;

    // speed of box
    //return 0;
    // annimation loop
    int img_end = 0;
    while (!close) {
        SDL_Event event;
        // Events mangement
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;

            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    dest.y -= speed / 30;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    dest.x -= speed / 30;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    dest.y += speed / 30;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    dest.x += speed / 30;
                    break;
                }
            }
        }
        if(img_end == 1){
            SDL_RenderClear(render);
            SDL_RenderCopy(render, endTex, NULL, NULL);
            SDL_RenderPresent(render);
            SDL_Event event1;
        // Events mangement
        while (SDL_PollEvent(&event1)) {
            switch (event1.type) {
                case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event1.key.keysym.scancode) {
                case SDL_SCANCODE_Q:
                    close = 1;
                    break;
                }
            }
        }
        }
        else{
        if(dest.x == 790 && dest.y == 790)
            img_end = 1;

        cout<<dest.x<<" "<<dest.y<<"\n";
        //cout<<dest2.x<<" "<<dest2.y<<"\n";
        // right boundary
        if (dest.x + dest.w > 800)
            dest.x = 800 - dest.w;

        // left boundary
        if (dest.x < 0)
            dest.x = 0;

        // bottom boundary
        if (dest.y + dest.h > 800)
            dest.y = 800 - dest.h;

        // upper boundary
        if (dest.y < 0)
            dest.y = 0;

        for(int i = 0; i < nWalls; ++i){
        int x,y,w,h;
        x = collision[i].get_x();
        y = collision[i].get_y();
        w = collision[i].get_w();
        h = collision[i].get_h();
        if(dest.y == y && dest.x >= x && dest.x < x + w)
            dest.y = y - dest.h;

        if(dest.y == y + h - dest.h && dest.x > x && dest.x < x + w)
            dest.y = y + h;

        if(dest.x == x && dest.y >= y && dest.y < y+ h)
            dest.x = x - dest.w;

        if(dest.x == x + w - dest.w && dest.y > y && dest.y < y + h)
            dest.x = x + w;
        }


        // clears the screen

        SDL_RenderClear(render);
        SDL_RenderCopy(render, playerTex, NULL, &dest);
        SDL_RenderCopy(render, endSqTex, NULL, &endpoz);
        for(int i = 0; i < nWalls; ++i){
            SDL_RenderCopy(render, tex[i], NULL, &d[i]);
        }

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(render);

        // calculates to 60 fps
        SDL_Delay(800 / 60);
        }
    }

    // destroy texture
    SDL_DestroyTexture(playerTex);
    for(int i = 0; i < nWalls; ++i){
        SDL_DestroyTexture(tex[i]);
    }

    delete []d;
    // destroy renderer
    SDL_DestroyRenderer(render);

    // destroy window
    SDL_DestroyWindow(win);

    return 0;
}
