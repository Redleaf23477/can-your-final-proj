#ifndef FONTS_H
#define FONTS_H

class Fonts
{
private:
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
};

#endif // FONTS_H
