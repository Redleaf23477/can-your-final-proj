#ifndef ROTATEOBJECT_H_INCLUDED
#define ROTATEOBJECT_H_INCLUDED
#include "global.h"
#include "Object.h"

class RotateObject : public Object{
protected:
    ALLEGRO_BITMAP *pic;
    double degree;
public:
    RotateObject(const char *path,int x,int y,int r,int w,int h);
    ~RotateObject();
    void set_degree(double degree);
    void draw();
    double get_degree();
};

#endif // ROTATEOBJECT_H_INCLUDED
