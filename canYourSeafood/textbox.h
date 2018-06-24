#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Object.h"
#include "global.h"
#include "fonts.h"

class Textbox:public Object
{
private:
    string str;
    int width, height;
    size_t maxlen;
    ALLEGRO_FONT *font;
    ALLEGRO_COLOR box_col, txt_col;

public:
    Textbox(int, int, int, int);
    ~Textbox();
    string get_txt() { return str; }
    void run(ALLEGRO_EVENT);
    void draw();
    void draw_for_ending();
    void set_txt(string s){ str = s; };
    void set_txt_color(ALLEGRO_COLOR color) { txt_col = color; };
    void set_font(ALLEGRO_FONT* f){ font = f; }
    int get_posy(){ return pos.get_y(); };
    int get_posx(){ return pos.get_x(); };
};

#endif // TEXTBOX_H
