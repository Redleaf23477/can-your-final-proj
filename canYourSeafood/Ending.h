#ifndef ENDING_H
#define ENDING_H

#include "Interface.h"
#include "Object.h"
#include "Button.h"

class Ending : public Interface
{
protected:
    Object *mouse;
    int stat;
    ButtonRD *start_but;

    int process();

public:
    Ending(ALLEGRO_DISPLAY*);
    ~Ending();
    int run();
};

#endif // ENDING_H

