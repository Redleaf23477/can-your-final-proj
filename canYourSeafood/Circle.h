#ifndef CIRCLE_H
#define CIRCLE_H

#include "global.h"

class Circle
{
private:
    int _x, _y, _r;

public:
    Circle(int, int, int);
    bool collide(const Circle &) const ;
    void set_pos(int, int);
    int get_x() const { return _x; }
    int get_y() const { return _y; }
    int get_r() const { return _r; }
};

#endif // CIRCLE_H
