#ifndef GIFOBJ_H
#define GIFOBJ_H

#include "global.h"
#include "Object.h"

class Gifobj : public Object
{
private:
    ALGIF_ANIMATION *gif;

public:
    Gifobj(int, int, int, const char*);
    ~Gifobj();
    void draw();
};

#endif // GIFOBJ_H
