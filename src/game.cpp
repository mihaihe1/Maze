#include "game.h"

game::game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("error");
    }
    win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);
    render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    surface = SDL_CreateRGBSurface(0, 30, 30, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 0));
    tex = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    SDL_Rect poz;
    SDL_QueryTexture(tex, NULL, NULL, &poz.w, &poz.h);

    // sets dimension of player(image)
    poz.w /= 3;
    poz.h /= 3;

    // sets initial x-position of object
    poz.x = 400;
    // sets initial y-position of object
    poz.y = 400;
    exit = 0;
}

void game::play(player &p)
{
    while (!exit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
                exit = 1;
                break;

            //case SDL_KEYDOWN:
                // keyboard API for key pressed
                //if(event.key.keysym.scancode) p.move_player();

            }
        }

        // clears the screen
        SDL_RenderClear(render);
        SDL_RenderCopy(render, tex, NULL, &poz);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(render);

        // calculates to 60 fps
        SDL_Delay(800 / 60);
    }
}
