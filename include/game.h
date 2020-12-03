#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "player.h"

#ifndef GAME_H
#define GAME_H


class game
{
    SDL_Window* win;
    SDL_Surface* surface;
    SDL_Texture* tex;
    int exit;

    public:
        SDL_Renderer* render;
        game();
        void play(const player&);

};

#endif // GAME_H
