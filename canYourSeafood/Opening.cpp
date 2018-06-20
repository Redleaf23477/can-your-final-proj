#include "Opening.h"

Opening::Opening(ALLEGRO_DISPLAY *dis):Interface(dis)
{
    inter_stat = INTER_CONTINUE;
    start_but = new ButtonRD(WIN_W/2, WIN_H/2, 50);
    start_but->set_str("open");
    vis_objs.push_back(start_but);
    mouse = new Object(0, 0, 1);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

Opening::~Opening()
{
    delete mouse;
}

int Opening::run()
{
    if(!al_is_event_queue_empty(event_queue))
    {
        inter_stat = process();
        draw();
    }
    return inter_stat;
}

int Opening::process()
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return INTER_EXIT;
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
