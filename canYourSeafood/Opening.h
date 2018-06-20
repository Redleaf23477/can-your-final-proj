#ifndef OPENING_H
#define OPENING_H

#include "Interface.h"
#include "Object.h"
#include "Button.h"

class Opening : public Interface
{
protected:
    Object *mouse;
    int stat;
    ButtonRD *start_but;
    ALLEGRO_BITMAP * BG;

    int process();

public:
    Opening(ALLEGRO_DISPLAY*);
    ~Opening();
    int run();
};

#endif // OPENING_H
