#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "player.h"
#include "game.h"

using namespace std;

int main()
{
    game Game;
    player Player;
    SDL_Renderer *renderForPlayer = Game.render;
    Player.set_rend(renderForPlayer);
    Game.play(player);

    // destroy texture
    SDL_DestroyTexture(tex);

    // destroy renderer
    SDL_DestroyRenderer(render);

    // destroy window
    SDL_DestroyWindow(win);

    return 0;
}
