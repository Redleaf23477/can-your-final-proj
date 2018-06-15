#include "Interface.h"

Interface::Interface()
{
}

Interface::~Interface()
{
//    for(auto &obj:objs) delete obj;
}

void Interface::draw()
{
//    al_draw_bitmap(bg, 0, 0, 0);
    al_clear_to_color(al_map_rgb(100, 100, 100));
//    for(auto obj:objs) obj->draw();

    al_flip_display();
}
