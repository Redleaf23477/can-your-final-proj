#ifndef GAMING_H
#define GAMING_H

#include "Interface.h"
#include "Object.h"
#include "Button.h"
#include "gifobj.h"

enum GamStat
{
    GAM_NOTHING,
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

    vector<ButtonRD*> buttons;

public:
    Menu(int, int, int, int, int, ALLEGRO_COLOR, vector<ButtonRD*>);
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
    int get_full() { return full; }
    int get_current() { return current; }
    void draw() override;
};

class Gaming : public Interface
{
protected:
    int game_stat;
    ALLEGRO_SAMPLE_INSTANCE *bgm;
    Object *mouse;
    VerticalBar *belly, *happy;
    ButtonRD *start_but;
    Menu *menu;
    ButtonRD *clothes, *feed, *ball, *touch, *bicycle, *rod;
    vector<ButtonRD*> buttons;
    Gifobj *fish;

    int process();
    int process_game();

public:
    Gaming(ALLEGRO_DISPLAY*);
    ~Gaming();
    int run();
};

#endif // GAMING_H
