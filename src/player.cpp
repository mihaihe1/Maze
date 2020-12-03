#include "player.h"

player::player()
{
}

void player::init()
{
    surface = IMG_Load("untitled.png");
    SDL_Texture* tex = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(tex, NULL, NULL, &poz.w, &poz.h);

    // sets dimension of player(image)
    poz.w /= 6;
    poz.h /= 6;

    // sets initial x-position of object
    poz.x = 400;
    // sets initial y-position of object
    poz.y = 400;

}

void player::set_rend(SDL_Renderer *r)
{
    render = r;
}

void player::move_player()
{
        if(SDL_SCANCODE_W)
            if(SDL_SCANCODE_UP){
                poz.y -= speed / 30;
                //break;
            }
        if(SDL_SCANCODE_A)
            if(SDL_SCANCODE_LEFT){
                poz.x -= speed / 30;
                //break;
            }
        if(SDL_SCANCODE_S)
            if(SDL_SCANCODE_DOWN){
                poz.y += speed / 30;
                //break;
            }
        if(SDL_SCANCODE_D)
            if(SDL_SCANCODE_RIGHT){
                poz.x += speed / 30;
                //break;
            }
}
