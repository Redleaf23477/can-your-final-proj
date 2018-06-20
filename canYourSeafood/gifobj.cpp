#include "gifobj.h"

Gifobj::Gifobj(int x, int y, int r, const char *path):Object(x, y, r)
{
    gif = algif_load_animation(path);
}

Gifobj::~Gifobj()
{
    algif_destroy_animation(gif);
}

void Gifobj::draw()
{
    ALLEGRO_BITMAP *now = algif_get_bitmap(gif, al_get_time());
    al_draw_bitmap(now, (float)pos.get_x(), (float)pos.get_y(), 0);
}
