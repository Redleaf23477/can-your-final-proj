#ifndef FONTS_H
#define FONTS_H
#include "global.h"

// color namespace
/*
    global variables that stores ALLEGRO_COLOR.
    packeted in a namespace to avoid name conflict
*/
namespace C
{
    extern ALLEGRO_COLOR white;
    extern ALLEGRO_COLOR black;
    extern ALLEGRO_COLOR light_orange;
    extern ALLEGRO_COLOR dark_orange;
    extern ALLEGRO_COLOR purple;
    extern ALLEGRO_COLOR blue;
    extern ALLEGRO_COLOR brown;
    extern ALLEGRO_COLOR gray;
    extern ALLEGRO_COLOR red;
    extern ALLEGRO_COLOR pink;
}

// Fonts class
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
    ALLEGRO_FONT *ending_slogan1;
    ALLEGRO_FONT *ending_slogan2;
    ALLEGRO_FONT *bebas_mini;

public:
    Fonts()
    {
        impact_small = NULL;
        ending_small = NULL;
        ending_big = NULL;
        bebas_mini = NULL;
    }
    ~Fonts()
    {
    }
    void load()
    {
        dbg << "loading ttf fonts" << endl;
        impact_small = al_load_ttf_font("../assets/font/impact.ttf", 24, 0);
        ending_small = al_load_ttf_font("../assets/font/Caviar_Dreams_Bold.ttf", 20, 0);
        ending_big = al_load_ttf_font("../assets/font/Berlin Sans FB Demi Bold.ttf", 27, 0);
        ending_slogan1 = al_load_ttf_font("../assets/font/Berlin Sans FB Demi Bold.ttf", 48, 0);
        ending_slogan2 = al_load_ttf_font("../assets/font/Berlin Sans FB Demi Bold.ttf", 40, 0);
        cout << "ttf fonts loaded" << endl;

        bebas_mini = al_load_ttf_font("../assets/font/bebas.ttf", 18, 0);

        dbg << "loading color" << endl;
        C::white = al_map_rgb(255, 255, 255);
        C::black = al_map_rgb(0, 0, 0);
        C::light_orange = al_map_rgb(255, 196,87);
        C::dark_orange = al_map_rgb(255, 142, 71);
        C::purple = al_map_rgb(149, 128, 255);
        C::blue = al_map_rgb(77, 129, 179);
        C::brown = al_map_rgb(108, 56, 21);
        C::gray = al_map_rgb(100, 100, 100);
        C::red = al_map_rgb(255, 0, 0);
        C::pink = al_map_rgb(255, 174, 201);
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
    ALLEGRO_FONT* get_ending_slogan1() { return ending_slogan1; }
    ALLEGRO_FONT* get_ending_slogan2() { return ending_slogan2; }
    ALLEGRO_FONT* textbox_txt() { return impact_small; }
    ALLEGRO_FONT* icon_txt() { return bebas_mini; }
};
extern Fonts font_lib;

#endif // FONTS_H
