#include "button.h"

ButtonRD::ButtonRD(int x, int y, int r, int id, const char *path):Object(x, y, r)
{
    hidden = true;
    button_id = id;
    font = font_lib.button_txt();
    pic = load_bitmap_at_size(path, 2*r, 2*r);
    str = "";
}

ButtonRD::ButtonRD(int x, int y, int r):Object(x, y, r)
{
    hidden = false;
    button_id = -1;
    font = font_lib.button_txt();
    pic = NULL;
    str = "Start!";
}

ButtonRD::~ButtonRD()
{
    if(pic) al_destroy_bitmap(pic);
}

void ButtonRD::toggleHidden()
{
    hidden ^= 1;
}

int ButtonRD::click()
{
    return (hidden? -1:button_id);
}

void ButtonRD::set_str(string s)
{
    str = s;
}

void ButtonRD::draw()
{
    int x = pos.get_x(), y = pos.get_y(), r = pos.get_r();
    if(hidden)
    {
        al_draw_filled_circle(x, y, r, C::gray);
    }
    else
    {
        al_draw_filled_circle(x, y, r, C::white);
    }
    if(pic != NULL) al_draw_bitmap(pic, x-r, y-r, 0);
    al_draw_text(font, C::black, x, y, ALLEGRO_ALIGN_CENTER, str.c_str());
}
