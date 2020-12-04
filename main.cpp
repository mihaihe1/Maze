#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>


using namespace std;

int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("%s", TTF_GetError());
    }
    if(TTF_Init() != 0){
        printf("error");
    }
    SDL_Window* win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    SDL_Renderer* render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 82, 26, 52, 255);
    SDL_Surface* surface;
    surface = IMG_Load("untitled.png");
    //SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
    SDL_Texture* tex = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    SDL_Surface* surface2;
    surface2 = IMG_Load("untitled.png");
    //SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
    SDL_Texture* tex2 = SDL_CreateTextureFromSurface(render, surface2);
    SDL_FreeSurface(surface2);
    SDL_Rect dest2;
    SDL_QueryTexture(tex2, NULL, NULL, &dest2.w, &dest2.h);

    TTF_Font* Sans = TTF_OpenFont("sans.ttf", 24);
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

    dest2.w /= 6;
    dest2.h /= 6;

    // sets initial x-position of object
    dest2.x = 600;

    // sets initial y-position of object
    dest2.y = 600;

    dest.w /= 6;
    dest.h /= 6;

    // sets initial x-position of object
    dest.x = 400;

    // sets initial y-position of object
    dest.y = 400;

    // controls annimation loop
    int close = 0;

    // speed of box
    int speed = 300;

    // annimation loop
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

        // clears the screen
        SDL_RenderClear(render);
        SDL_RenderCopy(render, tex, NULL, &dest);
        SDL_RenderCopy(render, tex2, NULL, &dest2);
        //SDL_RenderCopy(render, mess, NULL, &mess_rect);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(render);

        // calculates to 60 fps
        SDL_Delay(800 / 60);
    }

    // destroy texture
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(tex2);

    // destroy renderer
    SDL_DestroyRenderer(render);

    // destroy window
    SDL_DestroyWindow(win);

    return 0;
}
