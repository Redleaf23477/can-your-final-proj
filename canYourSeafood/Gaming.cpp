#include "Gaming.h"

Gaming::Gaming(ALLEGRO_DISPLAY *dis):Interface(dis)
{
    stat = INTER_CONTINUE;

    bgm = load_bgm("../assets/music/pika_volley.ogg");
    bg = load_bitmap_at_size("../assets/background/aquarium.jpg", WIN_W, WIN_H);

    start_but = new ButtonRD(WIN_W/2, WIN_H/2, 50);
    start_but->set_str("game");
    vis_objs.push_back(start_but);
    mouse = new Object(0, 0, 1);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_play_sample_instance(bgm);
}

Gaming::~Gaming()
{
    al_stop_sample_instance(bgm);
    delete mouse;
    al_destroy_sample_instance(bgm);
}

int Gaming::run()
{
    if(!al_is_event_queue_empty(event_queue))
    {
        stat = process();
        draw();
    }
    return stat;
}

int Gaming::process()
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

