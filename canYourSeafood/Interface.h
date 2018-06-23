#ifndef INTERFACE_H
#define INTERFACE_H

#include "global.h"
#include "gifobj.h"
#include "Object.h"

class Interface
{
protected:
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_EVENT event;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *bg;

    vector<Object*> vis_objs;            // an array that stores every pointer of visible objects in the interface
    int inter_stat;

    virtual int process() = 0;
    virtual void draw();

public:
    Interface(ALLEGRO_DISPLAY*);
    virtual ~Interface();
    virtual int run() = 0;
};



#endif // INTERFACE_H
