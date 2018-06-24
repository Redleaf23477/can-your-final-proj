#include "Interface.h"
#include "global.h"
#include "fonts.h"

Interface::Interface(ALLEGRO_DISPLAY *dis):display(dis)
{
    bg = NULL;
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);

    srand(time(NULL)+7122);
    al_start_timer(timer);
}

Interface::~Interface()
{
    al_stop_timer(timer);
    if(bg) al_destroy_bitmap(bg);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    for(auto &obj:vis_objs) delete obj;
}

void Interface::draw()
{
    if(bg) al_draw_bitmap(bg, 0, 0, 0);
    else al_clear_to_color(C::light_orange);

    for(auto obj:vis_objs) obj->draw();
}
