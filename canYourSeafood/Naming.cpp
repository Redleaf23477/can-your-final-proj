#include "Naming.h"

Naming::Naming(ALLEGRO_DISPLAY *dis):Interface(dis)
{
    inter_stat = INTER_CONTINUE;

    start_but = new ButtonRD(WIN_W/2, WIN_H/2, 100);
    start_but->set_str("name");
    vis_objs.push_back(start_but);
    txt = new Textbox(10, 10, 150, 30);
    vis_objs.push_back(txt);

    fish = new Gifobj(300, 10, 50, 18, "../assets/fish/bubble_fish");
    vis_objs.push_back(fish);
    mouse = new Object(0, 0, 1);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

Naming::~Naming()
{
    delete mouse;
}

int Naming::run()
{
    if(!al_is_event_queue_empty(event_queue))
    {
        inter_stat = process();
        draw();
    }
    return inter_stat;
}

int Naming::process()
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return INTER_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_TIMER)
    {
        al_flip_display();
        if(fish)
            fish->Move();
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
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        txt->run(event);
    }
    return INTER_CONTINUE;
}

