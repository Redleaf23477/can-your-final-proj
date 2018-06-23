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
    GAM_BIKE,

    ACC_BELT,
    ACC_HAT,
    ACC_GLASS
};

class Accessory : public Object
{
private:
    bool hidden;
    float ratio_x, ratio_y;
    int width, height;
    ALLEGRO_BITMAP *pic_left, *pic_right, *toDraw;

public:
    Accessory(int, int, int, float, float, const char *);
    ~Accessory();
    void toggleHidden();
    void update(Circle, int, int, int);
    void draw() override;
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
    vector<ButtonRD*> control_buttons;
    Menu *accessory;
    ButtonRD *but_belt, *but_hat, *but_glass;
    vector<ButtonRD*> accessory_buttons;
    Circle fish_goto;
    Object *fishfeed;
    Accessory *belt, *hat, *glass;
    Gifobj *fish;
    int bellycd;

    int process();
    int process_game();

public:
    Gaming(ALLEGRO_DISPLAY*);
    ~Gaming();
    int run();
};

#endif // GAMING_H
