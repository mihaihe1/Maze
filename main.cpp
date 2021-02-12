#include <iostream>
#include <bits/stdc++.h>
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
vector <SDL_Texture*> tex;
const int playerWidth = 10;
const int playerHeight = 10;
int playerStartX = 50;
int playerStartY = 30;
const int nLevels = 2;

const int speed = 300;

SDL_Rect* d;

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
    playerSurface = IMG_Load("resources/untitled.png");
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

   /* SDL_Surface* mainMenu;
    mainMenu = IMG_Load("start_menu.png");
    SDL_Texture* menuTex = SDL_CreateTextureFromSurface(render, mainMenu);
    SDL_FreeSurface(mainMenu);
    SDL_Rect menuScreen;
    SDL_QueryTexture(menuTex, NULL, NULL, &menuScreen.w, &menuScreen.h);
    */

    SDL_Surface* newGame;
    newGame = IMG_Load("resources/new_game.png");
    SDL_Texture* newGameTex = SDL_CreateTextureFromSurface(render, newGame);
    SDL_FreeSurface(newGame);
    SDL_Rect newGamePoz;
    SDL_QueryTexture(newGameTex, NULL, NULL, &newGamePoz.w, &newGamePoz.h);
    newGamePoz.w = 400;
    newGamePoz.h = 50;
    newGamePoz.x = 200;
    newGamePoz.y = 200;

    SDL_Surface* quitGame;
    quitGame = IMG_Load("resources/quit_game.png");
    SDL_Texture* quitGameTex = SDL_CreateTextureFromSurface(render, quitGame);
    SDL_FreeSurface(quitGame);
    SDL_Rect quitGamePoz;
    SDL_QueryTexture(quitGameTex, NULL, NULL, &quitGamePoz.w, &quitGamePoz.h);
    quitGamePoz.w = 400;
    quitGamePoz.h = 50;
    quitGamePoz.x = 200;
    quitGamePoz.y = 500;

    SDL_Surface* resumeGame;
    resumeGame = IMG_Load("resources/resume_game.png");
    SDL_Texture* resumeGameTex = SDL_CreateTextureFromSurface(render, resumeGame);
    SDL_FreeSurface(resumeGame);
    SDL_Rect resumeGamePoz;
    SDL_QueryTexture(resumeGameTex, NULL, NULL, &resumeGamePoz.w, &resumeGamePoz.h);
    resumeGamePoz.w = 400;
    resumeGamePoz.h = 50;
    resumeGamePoz.x = 200;
    resumeGamePoz.y = 200;

    SDL_Surface* retryGame;
    retryGame = IMG_Load("resources/retry.png");
    SDL_Texture* retryGameTex = SDL_CreateTextureFromSurface(render, retryGame);
    SDL_FreeSurface(retryGame);
    SDL_Rect retryGamePoz;
    SDL_QueryTexture(retryGameTex, NULL, NULL, &retryGamePoz.w, &retryGamePoz.h);
    retryGamePoz.w = 400;
    retryGamePoz.h = 50;
    retryGamePoz.x = 200;
    retryGamePoz.y = 400;

    SDL_Surface* wonGame;
    wonGame = IMG_Load("resources/won.png");
    SDL_Texture* wonGameTex = SDL_CreateTextureFromSurface(render, wonGame);
    SDL_FreeSurface(wonGame);
    SDL_Rect wonGamePoz;
    SDL_QueryTexture(wonGameTex, NULL, NULL, &wonGamePoz.w, &wonGamePoz.h);
    wonGamePoz.w = 400;
    wonGamePoz.h = 50;
    wonGamePoz.x = 200;
    wonGamePoz.y = 100;

    SDL_Surface* lostGame;
    lostGame = IMG_Load("resources/lost.png");
    SDL_Texture* lostGameTex = SDL_CreateTextureFromSurface(render, lostGame);
    SDL_FreeSurface(lostGame);
    SDL_Rect lostGamePoz;
    SDL_QueryTexture(lostGameTex, NULL, NULL, &lostGamePoz.w, &lostGamePoz.h);
    lostGamePoz.w = 400;
    lostGamePoz.h = 50;
    lostGamePoz.x = 200;
    lostGamePoz.y = 100;
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
    int cnt = 0;
    stack <string> game_state;
    game_state.push("QUIT");
    game_state.push("MENU");
    unsigned int start = 0;

    unsigned int copie = start;
    bool started = false;
    bool create_level = false;
    bool paused = false;
    unsigned int total = 0;
    bool winning = false;
    unsigned int in;
    while (game_state.top() != "QUIT") {
        SDL_Event event;
        string state = game_state.top();
        if(state == "MENU"){
            while(SDL_PollEvent(&event)){
                switch (event.type) {
                    case SDL_QUIT:
                        game_state.pop();
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        if(event.motion.x >= newGamePoz.x && event.motion.x <= newGamePoz.x + newGamePoz.w
                            && event.motion.y >= newGamePoz.y && event.motion.y <= newGamePoz.y + newGamePoz.h)
                            {
                                game_state.pop();
                                game_state.push("GAME");
                                break;
                            }
                        if(event.motion.x >= quitGamePoz.x && event.motion.x <= quitGamePoz.x + quitGamePoz.w
                            && event.motion.y >= quitGamePoz.y && event.motion.y <= quitGamePoz.y + quitGamePoz.h)
                            {
                                game_state.pop();
                                break;
                            }
                }
            }
        SDL_RenderClear(render);
        //SDL_RenderCopy(render, menuTex, NULL, &menuScreen);
        SDL_RenderCopy(render, newGameTex, NULL, &newGamePoz);
        SDL_RenderCopy(render, quitGameTex, NULL, &quitGamePoz);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(render);

        // calculates to 60 fps
        SDL_Delay(800 / 60);

        }
        else if(state == "GAME"){
        if(!started){
            start = SDL_GetTicks();
            //total = 0;
            started = true;
        }
        unsigned int t = 999999;
        if(SDL_GetTicks() < t){
        cout<<SDL_GetTicks()<<" "<<total<<" "<<start<<"\n";
        if(SDL_GetTicks() - total - start >= 35000){
            game_state.pop();
            game_state.push("ENDING");
        }
        }
        if(!create_level){

                SDL_Surface* surface;
                f >> nWalls;

                d = new SDL_Rect[nWalls];

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
            //cnt++;
            create_level = true;

        }

        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
                // handling of close button
                game_state.pop();
                break;

            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    game_state.push("PAUSE");
                    break;
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

        if(dest.x == 790 && dest.y == 790)
            {
                dest.x = 100;
                dest.y = 100;
                //total += SDL_GetTicks() - start;
                //game_state.pop();
                //game_state.push("ENDING");
                for(int i = 0; i < nWalls; ++i){
                    SDL_DestroyTexture(tex[i]);
                }
                tex.clear();
                collision.clear();
                //delete []d;
                cnt++;
                if(cnt == nLevels){
                    game_state.pop();
                    game_state.push("ENDING");
                    cout<<"final\n";
                    cout<< SDL_GetTicks() - total - start;
                    winning = true;
                }
                create_level = false;
            }
        else{
       //cout <<cnt;
        //cout<<SDL_GetTicks() - start<<"\n";

        //cout<<dest.x<<" "<<dest.y<<"\n";
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
        }

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(render);

        // calculates to 60 fps
        SDL_Delay(800 / 60);

        }
        else if(state == "ENDING"){
            SDL_RenderClear(render);
            if(!winning){
            SDL_RenderCopy(render, lostGameTex, NULL, &lostGamePoz);
            SDL_RenderCopy(render, retryGameTex, NULL, &retryGamePoz);
            }
            else{
            newGamePoz.y = 400;
            SDL_RenderCopy(render, wonGameTex, NULL, &wonGamePoz);
            SDL_RenderCopy(render, newGameTex, NULL, &newGamePoz);
            }
            SDL_RenderCopy(render, quitGameTex, NULL, &quitGamePoz);
            SDL_RenderPresent(render);
            SDL_Delay(800 / 60);
            SDL_Event event1;
        // Events mangement
            while (SDL_PollEvent(&event1)) {
                switch (event1.type) {
                    case SDL_QUIT:
                        //game_state.pop();
                        game_state.pop();
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        if(event1.motion.x >= retryGamePoz.x && event1.motion.x <= retryGamePoz.x + retryGamePoz.w
                            && event1.motion.y >= retryGamePoz.y && event1.motion.y <= retryGamePoz.y + retryGamePoz.h)
                            {
                                game_state.pop();
                                game_state.push("GAME");
                                f.clear();
                                f.seekg(0, f.beg);
                                cnt = 0;
                                started = false;
                                winning = false;
                                break;
                            }
                        if(event1.motion.x >= quitGamePoz.x && event1.motion.x <= quitGamePoz.x + quitGamePoz.w
                            && event1.motion.y >= quitGamePoz.y && event1.motion.y <= quitGamePoz.y + quitGamePoz.h)
                            {
                                game_state.pop();

                           //     game_state.pop();
                                break;
                            }
                    case SDL_KEYDOWN:
                    // keyboard API for key pressed
                    switch (event1.key.keysym.scancode) {
                    case SDL_SCANCODE_Q:
                        game_state.pop();
                        break;
                    }
                }

            }
        }
        else if(state == "PAUSE"){
            if(!paused){
                in = SDL_GetTicks();
                paused = true;
            }
            cout << in <<"\n";
            //cout << start <<"\n";
            //cout << start + t <<"\n";
            while(SDL_PollEvent(&event)){
                switch (event.type) {
                    /*case SDL_KEYDOWN:
                    // keyboard API for key pressed
                    switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        game_state.pop();
                        break;
                    }*/
                    case SDL_QUIT:
                        game_state.pop();
                        game_state.pop();
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        if(event.motion.x >= resumeGamePoz.x && event.motion.x <= resumeGamePoz.x + resumeGamePoz.w
                            && event.motion.y >= resumeGamePoz.y && event.motion.y <= resumeGamePoz.y + resumeGamePoz.h)
                            {
                                paused = false;
                                total += SDL_GetTicks() - in;
                                game_state.pop();
                                break;
                            }
                        if(event.motion.x >= quitGamePoz.x && event.motion.x <= quitGamePoz.x + quitGamePoz.w
                            && event.motion.y >= quitGamePoz.y && event.motion.y <= quitGamePoz.y + quitGamePoz.h)
                            {
                                game_state.pop();
                                game_state.pop();
                                break;
                            }
                    case SDL_KEYDOWN:
                    // keyboard API for key pressed
                    switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        paused = false;
                        total += SDL_GetTicks() - in;
                        game_state.pop();
                        break;
                    }
                }
            }
        SDL_RenderClear(render);
        //SDL_RenderCopy(render, menuTex, NULL, &menuScreen);
        SDL_RenderCopy(render, resumeGameTex, NULL, &resumeGamePoz);
        SDL_RenderCopy(render, quitGameTex, NULL, &quitGamePoz);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(render);

        // calculates to 60 fps
        SDL_Delay(800 / 60);
        }
    }

    // destroy texture
    SDL_DestroyTexture(playerTex);
    SDL_DestroyTexture(newGameTex);
    SDL_DestroyTexture(quitGameTex);
    SDL_DestroyTexture(retryGameTex);
    SDL_DestroyTexture(resumeGameTex);
    SDL_DestroyTexture(wonGameTex);
    SDL_DestroyTexture(lostGameTex);
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
