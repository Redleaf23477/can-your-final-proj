#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"
#include "Circle.h"

class Object
{
protected:
    Circle pos;

public:
    Object(int, int, int);
    virtual ~Object();
    Circle get_pos() { return pos; }
    virtual void set_pos(int, int);
    virtual bool collide(const Object*) const;  // detect if mouse touch the object
    virtual void draw();
};

#endif // OBJECT_H
