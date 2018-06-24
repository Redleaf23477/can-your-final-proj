#ifndef ENDINGOBJ_H
#define ENDINGOBJ_H

#include "global.h"
#include "Object.h"

#define FISH 0
#define BIKE 1
#define MACHINE 2
#define FISH_MEAT 3
#define LIGHT 4
#define CAN 5

#define GRAVITY_END_CD 10
#define GRAVITY_END 1
#define FISH_CD 10
#define PI 3.1415926

// round button
class EndingObj:public Object
{
private:
    ALLEGRO_FONT *bigfont;
    ALLEGRO_FONT *smallfont;
    string str;
    ALLEGRO_BITMAP* pic;
    int vx, vy;
    int vangle;
    int angular_acceleration;
    int angle = 0;
    int gravity;
    int gravity_cd;
    int kind;
    int frame_cd;

public:
    EndingObj(int, int, int, ALLEGRO_BITMAP*, int);
    ~EndingObj();
    void set_str(string);
    void update();
    void draw() override;
    void set_pic(ALLEGRO_BITMAP* img){ pic = img; };
    ALLEGRO_BITMAP* get_pic(){ return pic; }
    bool beneath(EndingObj* obj){ return pos.get_y()+al_get_bitmap_height(pic)/2 > obj->pos.get_y()-60; }
    void count_frame_cd(){ frame_cd--; }
    void set_speed(int _vx, int _vy){ vx = _vx; vy = _vy; }
    void set_vangle(int v){ vangle = v; }
    void set_gravity(int g){ gravity = g; }
    int get_posx(){ return pos.get_x(); }
    int get_posy(){ return pos.get_y(); }
    int get_angle(){ return angle; }
    bool hidden;
    int rotate_l = 0, rotate_r = 0;
};

#endif // OBJECT_H
