#ifndef GAMING_H
#define GAMING_H

#include "Interface.h"
#include "Object.h"
#include "Button.h"
#include "gifobj.h"

enum ButtonID
{
    GAM_CLOTHES,
    GAM_FEED,
    GAM_BALL,
    GAM_TOUCH,
    GAM_BIKE
};

class Menu : public Object
{
private:
    bool hidden;
    int width, height;
    ALLEGRO_COLOR bg_color;
    ALLEGRO_FONT *hide_font;

    ButtonRD *clothes, *feed, *ball, *touch, *bicycle, *rod;

    vector<Object*> buttons;

public:
    Menu(int, int, int, int, int, ALLEGRO_COLOR);
    ~Menu();
    bool ishidden() { return hidden; }
    void toggleHidden();
    void draw() override;
};

class VerticalBar : public Object
{
private:
    int width;
    int full, current;
    ALLEGRO_COLOR bar_color, edge_color;

public:
    VerticalBar(int, int, int, int, ALLEGRO_COLOR, ALLEGRO_COLOR);
    void set_current(int);
    int get_current() { return current; }
    void draw() override;
};

class Gaming : public Interface
{
protected:
    ALLEGRO_SAMPLE_INSTANCE *bgm;
    Object *mouse;
    Menu *menu;
    VerticalBar *belly, *happy;
    ButtonRD *start_but;
    Gifobj *fish;

    int process();

public:
    Gaming(ALLEGRO_DISPLAY*);
    ~Gaming();
    int run();
};

#endif // GAMING_H
