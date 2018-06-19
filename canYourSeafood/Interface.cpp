#include "Interface.h"

Interface::Interface(ALLEGRO_DISPLAY *dis):display(dis)
{
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);

    al_start_timer(timer);
}

Interface::~Interface()
{
    al_stop_timer(timer);

    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    for(auto &obj:vis_objs) delete obj;
}

void Interface::draw()
{
//    al_draw_bitmap(bg, 0, 0, 0);
    al_clear_to_color(al_map_rgb(100, 100, 100));
    for(auto obj:vis_objs) obj->draw();
}
