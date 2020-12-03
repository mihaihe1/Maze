#include "game.h"

game::game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("error");
    }
    win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 82, 26, 52, 255);
    exit = 0;
}

void game::play(const player &p)
{
    while (!exit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
                close = 1;
                break;

            case SDL_KEYDOWN:
                // keyboard API for key pressed
                if(event.key.keysym.scancode) p.move_player();

            }
        }

        // clears the screen
        SDL_RenderClear(render);
        SDL_RenderCopy(render, tex, NULL, &dest);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(render);

        // calculates to 60 fps
        SDL_Delay(800 / 60);
    }
}
