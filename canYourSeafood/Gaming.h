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
    GAM_CUT,

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

class Ball : public Object
{
private:
    bool hidden;
    int cd, CD;
    int idx, pic_num;
    int vx, vy, g;
    Circle center;
    vector<ALLEGRO_BITMAP*> PIC;
    ALLEGRO_BITMAP *toDraw;

public:
    Ball(int, int, int, int, const char*);
    ~Ball();
    int get_vx() { return vx; }
    int get_vy() { return vy; }
    bool isHidden() { return hidden; }
    Circle get_center() { return center; }
    void set_v(int x, int y);
    void set_pos(int x, int y);
    void toggleHidden();
    bool collide(Object*);
    bool Move();
    void click();
    void draw() override;
};

class Gaming : public Interface
{
protected:
    int game_stat;
    ALLEGRO_SAMPLE_INSTANCE *bgm;
    bool grab;
    ALLEGRO_BITMAP *mouse_touch, *mouse_grab;
    ALLEGRO_MOUSE_CURSOR *cursor_touch, *cursor_grab;
    Object *mouse;
    VerticalBar *belly, *happy;
    Menu *menu;
    ButtonRD *but_clothes, *but_feed, *but_ball, *but_touch, *but_bicycle, *but_rod;
    vector<ButtonRD*> control_buttons;
    Menu *accessory;
    ButtonRD *but_belt, *but_hat, *but_glass;
    vector<ButtonRD*> accessory_buttons;
    Circle fish_goto;
    Object *fishfeed;
    Accessory *belt, *hat, *glass;
    Gifobj *fish;
    Ball *ball;

    ALLEGRO_SAMPLE *hit;
    ALLEGRO_SAMPLE *bite;

    int dropv;
    int bellycd;

    int process();
    int process_game();

public:
    Gaming(ALLEGRO_DISPLAY*);
    ~Gaming();
    int run();
};

#endif // GAMING_H
