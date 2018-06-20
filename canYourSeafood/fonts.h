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

public:
    Fonts()
    {
        impact_small = NULL;
    }
    ~Fonts()
    {
    }
    void load()
    {
        dbg << "loading ttf fonts" << endl;
        impact_small = al_load_ttf_font("../assets/font/impact.ttf", 24, 0);
        cout << "ttf fonts loaded" << endl;
    }
    void destroy()
    {
        al_destroy_font(impact_small);
    }

    ALLEGRO_FONT* button_txt() { return impact_small; }
    ALLEGRO_FONT* textbox_txt() { return impact_small; }
};
extern Fonts font_lib;


// color defines
namespace C
{
    extern ALLEGRO_COLOR white;
    extern ALLEGRO_COLOR black;
}

#endif // FONTS_H
