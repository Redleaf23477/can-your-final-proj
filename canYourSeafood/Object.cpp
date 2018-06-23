#include "Object.h"

Object::Object(int x, int y, int r):pos(x, y, r)
{
}

Object::~Object()
{
}

void Object::set_pos(int x, int y)
{
    pos.set_pos(x, y);
}

bool Object::collide(const Object *obj) const
{
    return pos.collide(obj->pos);
}

void Object::draw()
{
    al_draw_filled_circle((float)pos.get_x(), (float)pos.get_y(), pos.get_r(), al_map_rgba(71, 22, 22, 200));
}
