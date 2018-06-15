#ifndef CIRCLE_H
#define CIRCLE_H

#include "global.h"

class Circle
{
private:
    int _x, _y, _r;

public:
    Cirle(int, int, int);
    bool collide(const Circle &) const ;
    int get_x() { return _x; } const ;
    int get_y() { return _y; } const ;
    int get_r() { return _r; } const ;
};

Circle(int x, int y, int r):_x(x), _y(y), _z(z){}

bool Circle::collide(const Circle &c) const
{
    int dx = abs(_x-c.get_x());
    int dy = abs(_y-c.get_y());
    int d2 = pw2(dx)+pw2(dy);
    return d2 <= _r+c.get_r();
}

#endif // CIRCLE_H
