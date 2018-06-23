#include "button.h"

ButtonRD::ButtonRD(int x, int y, int r, bool hid, int id, const char *path):Object(x, y, r)
{
    hidden = hid;
    alert = false;
    button_id = id;
    font = font_lib.button_txt();
    pic = load_bitmap_at_size(path, 2*r, 2*r);
    str = "";
}

ButtonRD::ButtonRD(int x, int y, int r):Object(x, y, r)
{
    hidden = false;
    alert = false;
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
    if(alert == false) alert = true, alert_t = 155;
}

int ButtonRD::click()
{
    if(alert) alert = false;
    return (hidden? -1:button_id);
}

void ButtonRD::set_str(string s)
{
    str = s;
}

void ButtonRD::alert_chgCol()
{
    // aler_t = [100, 410], back and froth
    if(alert) alert_t = (alert_t+5)%310;
}

void ButtonRD::draw()
{
    int x = pos.get_x(), y = pos.get_y(), r = pos.get_r();
    if(hidden)
    {
        al_draw_filled_circle(x, y, r, C::gray);
    }
    else if(alert)
    {
        // aler_t = [100, 410], back and froth
        char c = 100+(alert_t <= 155? alert_t:310-alert_t);
        al_draw_filled_circle(x, y, r, al_map_rgb(c, 255, c));
    }
    else
    {
        al_draw_filled_circle(x, y, r, C::white);
    }
    if(pic != NULL) al_draw_bitmap(pic, x-r, y-r, 0);
    al_draw_text(font, C::black, x, y, ALLEGRO_ALIGN_CENTER, str.c_str());
}
