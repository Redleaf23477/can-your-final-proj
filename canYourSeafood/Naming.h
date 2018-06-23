#ifndef NAMING_H
#define NAMING_H

#include "Interface.h"
#include "Object.h"
#include "Button.h"
#include "textbox.h"

class Naming : public Interface
{
protected:
    Object *mouse;
    int stat;
    ButtonRD *start_but;
    Textbox *txt;
    ALLEGRO_BITMAP* egg;
    ALLEGRO_SAMPLE* SE;

    int process();

public:
    Naming(ALLEGRO_DISPLAY *dis);
    ~Naming();
    int run();
    void draw();

    void animation();
    void animation_init();
};

#endif // NAMING_H
