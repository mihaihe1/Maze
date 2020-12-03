#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

using namespace std;

int main()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("error");
    }
    SDL_Window* win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    SDL_Renderer* render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 0x0, 0xFF, 0xFF, 0xFF);
    SDL_Surface* surface;
    surface = IMG_Load("untitled.png");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

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

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(render);

        // calculates to 60 fps
        SDL_Delay(800 / 60);
    }

    // destroy texture
    SDL_DestroyTexture(tex);

    // destroy renderer
    SDL_DestroyRenderer(render);

    // destroy window
    SDL_DestroyWindow(win);

    return 0;
}
