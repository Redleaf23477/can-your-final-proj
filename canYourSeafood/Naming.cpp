#include "Naming.h"

Naming::Naming(ALLEGRO_DISPLAY *dis):Interface(dis)
{
    stat = INTER_CONTINUE;
    start_but = new ButtonRD(WIN_W/2, WIN_H/2, 100);
    mouse = new Object(0, 0, 1);
    objs.push_back(start_but);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

Naming::~Naming()
{
    delete start_but;
    delete mouse;
}

int Naming::run()
{
    if(!al_is_event_queue_empty(event_queue))
    {
        stat = process();
        draw();
    }
    return stat;
}

int Naming::process()
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return INTER_DONE;
    }
    else if(event.type == ALLEGRO_EVENT_TIMER)
    {
        al_flip_display();
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse->set_pos(event.mouse.x, event.mouse.y);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if(event.mouse.button == 1)
        {
            if(start_but->mouse_in(mouse)) return INTER_DONE;
        }
    }
    return INTER_CONTINUE;
}

