#ifndef GIFOBJ_H
#define GIFOBJ_H

#include "global.h"
#include "Object.h"

class Gifobj : public Object
{
private:
    vector <ALLEGRO_BITMAP*> GIF;
    Circle center;
    int width, height;
    int dir, now, num;
    int CD;

public:
    Gifobj(int x, int y, int r, int wid, int hei, int num_of_picture,int cd, const char* path);
    void Move();
    void change_dir();
    ALLEGRO_BITMAP* now_pic();
    int get_width() { return width; }
    int get_height() { return height; }
    int get_dir() { return dir; }
    Circle get_center() { return center; }
    void set_pos(int, int);
    bool collide(Object*);
    bool rotate_collide(Object*);
    void move_toward(Circle);
    ~Gifobj();
    void draw();
};

#endif // GIFOBJ_H
