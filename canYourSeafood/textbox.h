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
};

#endif // TEXTBOX_H
