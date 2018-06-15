#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"

class Object
{
private:
    Circle pos;
    ALLEGRO_BITMAP *pic;

public:
    bool is_mouse_touch(const Circle &) const;
    void run();
    void draw();
};

bool Object::is_mouse_touch(const Circle &mouse) const
{
    return pos.collide(mouse);
}

#endif // OBJECT_H
