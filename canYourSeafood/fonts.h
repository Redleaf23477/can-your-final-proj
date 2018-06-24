#ifndef FONTS_H
#define FONTS_H

#include "global.h"
/*
    A class that contains all fonts used in the project.
    set the pointer to NULL in the constructor
    call al_load_ttf_font("../assets/font/xxx.ttf", size, 0) in the "load" function
    call al_destroy_font() int the "destroy" function
    for each kind of text, build a member function to map them to a font
*/

class Fonts
{
private:
    // ALLEGRO_FONT *fontName_size
    ALLEGRO_FONT *impact_small;
    ALLEGRO_FONT *ending_small;
    ALLEGRO_FONT *ending_big;

public:
    Fonts()
    {
        impact_small = NULL;
        ending_small = NULL;
        ending_big = NULL;
    }
    ~Fonts()
    {
    }
    void load()
    {
        dbg << "loading ttf fonts" << endl;
        impact_small = al_load_ttf_font("../assets/font/impact.ttf", 24, 0);
        ending_small = al_load_ttf_font("../assets/font/impact.ttf", 24, 0);
        ending_big = al_load_ttf_font("../assets/font/impact.ttf", 48, 0);
        cout << "ttf fonts loaded" << endl;
    }
    void destroy()
    {
        al_destroy_font(impact_small);
        al_destroy_font(ending_small);
        al_destroy_font(ending_big);
    }

    ALLEGRO_FONT* button_txt() { return impact_small; }
    ALLEGRO_FONT* ending_txt_s() { return ending_small; }
    ALLEGRO_FONT* ending_txt_b() { return ending_big; }
};

#endif // FONTS_H
