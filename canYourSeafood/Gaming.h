#ifndef GAMING_H
#define GAMING_H

#include "Interface.h"
#include "Object.h"
#include "Button.h"

class Gaming : public Interface
{
protected:
    ALLEGRO_SAMPLE_INSTANCE *bgm;
    Object *mouse;
    int stat;
    ButtonRD *start_but;

    int process();

public:
    Gaming(ALLEGRO_DISPLAY*);
    ~Gaming();
    int run();
};

#endif // GAMING_H
