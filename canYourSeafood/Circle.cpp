#include "Circle.h"

Circle::Circle(int x, int y, int r):_x(x), _y(y), _r(r){}

void Circle::set_pos(int x, int y)
{
    _x = x, _y = y;
}

bool Circle::collide(const Circle &c) const
{
    int dx = abs(_x-c.get_x());
    int dy = abs(_y-c.get_y());
    int d2 = pw2(dx)+pw2(dy);
    return d2 <= pw2(_r+c.get_r());
}
