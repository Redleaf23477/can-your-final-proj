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
    void set_pos(int, int);
    virtual bool mouse_in(const Object*) const;  // detect if mouse touch the object
    virtual void draw();
};

#endif // OBJECT_H
