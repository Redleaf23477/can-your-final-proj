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
    ALLEGRO_SAMPLE_INSTANCE *bgm;
    ALLEGRO_SAMPLE *SE;

    Gifobj* fish1;
    Gifobj* fish2;

    int process();

public:
    Opening(ALLEGRO_DISPLAY*);
    ~Opening();
    int run();
    void draw();
    void update();

    void animation();
    void animation_init();
};

#endif // OPENING_H
