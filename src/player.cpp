#include "player.h"

player::player()
{
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
