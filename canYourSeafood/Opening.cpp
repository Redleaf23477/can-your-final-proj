#include "Opening.h"

Opening::Opening()
{
    stat = OP_CONTINUE;
    start_but = new ButtonRD(WIN_W/2, WIN_H/2, 50);
    mouse = new Object(0, 0, 1);
    objs.push_back(start_but);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

Opening::~Opening()
{
    delete start_but;
    delete mouse;
}

bool Opening::run()
{
    if(!al_is_event_queue_empty(event_queue))
    {
        stat = process();
        draw();
    }
    return stat != OP_DONE;
}

int Opening::process()
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return OP_DONE;
    }
    else if(event.type == ALLEGRO_EVENT_TIMER)
    {
        al_flip_display();
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        dbg << "mouse_axes" << endl;
        mouse->set_pos(event.mouse.x, event.mouse.y);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if(event.mouse.button == 1)
        {
            dbg << "mouse_click" << endl;
            if(start_but->mouse_in(mouse)) return OP_DONE;
        }
    }
    return OP_CONTINUE;
}
