#include "button.h"

ButtonRD::ButtonRD(int x, int y, int r):Object(x, y, r)
{
    font = font_lib.button_txt();
    str = "Start!";
}

ButtonRD::~ButtonRD()
{
}

int ButtonRD::click()
{
    return 1;
}

void ButtonRD::set_str(string s)
{
    str = s;
}

void ButtonRD::draw()
{
    al_draw_filled_circle((float)pos.get_x(), (float)pos.get_y(), pos.get_r(), al_map_rgb(255, 255, 255));
    al_draw_text(font, al_map_rgb(0, 0, 0), (float)pos.get_x(), (float)pos.get_y(), ALLEGRO_ALIGN_CENTER, str.c_str());
}
