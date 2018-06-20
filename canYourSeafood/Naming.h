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

    int process();

public:
    Naming(ALLEGRO_DISPLAY *dis);
    ~Naming();
    int run();
};

#endif // NAMING_H
