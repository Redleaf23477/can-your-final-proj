#include "textbox.h"
#include "global.h"

Textbox::Textbox(int x, int y, int wid, int hei):Object(x, y, 0), width(wid), height(hei)
{
    font = font_lib.textbox_txt();
    box_col = C::white;
    txt_col = C::black;
    maxlen = 10;
}

Textbox::~Textbox()
{
}

void Textbox::run(ALLEGRO_EVENT event)  // process key code and convert to string
{
    if(event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        int &key = event.keyboard.keycode;
        if(ALLEGRO_KEY_A <= key && key <= ALLEGRO_KEY_Z)
        {
            if(str.size() <= maxlen) str.push_back('A'+key-ALLEGRO_KEY_A);
        }
        else if(ALLEGRO_KEY_0 <= key && key <= ALLEGRO_KEY_9)
        {
            if(str.size() <= maxlen) str.push_back('0'+key-ALLEGRO_KEY_0);
        }
        else if(key == ALLEGRO_KEY_BACKSPACE)
        {
            if(str.size() > 0) str.pop_back();
        }
        else
        {
            dbg << "unsupported key code" << endl;
        }
    }
}

void Textbox::draw()
{
    float x1 = pos.get_x(), x2 = x1+width;
    float y1 = pos.get_y(), y2 = y1+height;
    al_draw_filled_rectangle(x1, x2, y1, y2, box_col);
    al_draw_text(font, txt_col, x1, y1, ALLEGRO_ALIGN_LEFT, str.c_str());
}
