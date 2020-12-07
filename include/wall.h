#ifndef WALL_H
#define WALL_H


class wall
{
    int x, y, w, h;
    public:
        wall(int, int, int, int);
        int get_x();
        int get_y();
        int get_w();
        int get_h();
        int set_x(int x1);
        int set_y(int y1);
        int set_w(int w1);
        int set_h(int h1);

};

#endif // WALL_H
