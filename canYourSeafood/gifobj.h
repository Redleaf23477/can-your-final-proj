#ifndef GIFOBJ_H
#define GIFOBJ_H

#include "global.h"
#include "Object.h"

class Gifobj : public Object
{
private:
    vector <ALLEGRO_BITMAP*> GIF;
    int dir, now, num;
    int CD;
public:
    Gifobj(int x, int y, int r, int num_of_picture,int cd, const char* path);
    void Move();
    void change_dir();
    ~Gifobj();
    void draw();
};

#endif // GIFOBJ_H
