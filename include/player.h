#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef PLAYER_H
#define PLAYER_H


class player
{
    SDL_Rect poz;
    SDL_Surface* surface;
    SDL_Render* render;
    const int speed = 300;

    public:
        player();
        void move_player();
        void set_rend(SDL_Renderer*);
        void init();
};

#endif // PLAYER_H
