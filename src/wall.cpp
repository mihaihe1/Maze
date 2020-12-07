#include "wall.h"

wall::wall(int x1, int y1, int w1, int h1)
{
    x = x1;
    y = y1;
    w = w1;
    h = h1;
}

int wall::get_x(){ return x; }
int wall::get_y(){ return y; }
int wall::get_w(){ return w; }
int wall::get_h(){ return h; }

int wall::set_x(int x1){ x = x1; }
int wall::set_y(int y1){ y = y1; }
int wall::set_w(int w1){ w = w1; }
int wall::set_h(int h1){ h = h1; }
