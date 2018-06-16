#ifndef INTERFACE_H
#define INTERFACE_H

#include "global.h"
#include "Object.h"

class Interface
{
protected:
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_EVENT event;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;

    vector<Object*> objs;            // an array that stores every pointer of obj in the interface
    int stat;

    virtual int process() = 0;
    virtual void draw();

public:
    Interface();
    virtual ~Interface();
    virtual int run() = 0;
};



#endif // INTERFACE_H
