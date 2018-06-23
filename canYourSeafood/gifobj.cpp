#include "gifobj.h"
#define L 0
#define R 1
Gifobj::Gifobj(int x, int y, int r, int wid, int hei, int num_of_picture, int cd, const char *path):Object(x, y, r), center(x+wid/2, y+hei/2, r)
{
    dir = 0;
    now = 0;
    num = num_of_picture;
    CD = cd;

    width = wid, height = hei;

    stringstream SS;
    string P;
    for(int i=0;i<num;i++){
        P.clear();
        SS.clear();
        SS << path << "/" << i << ".png";
        SS >> P;
        cout<<"load: "<<P<<endl;
        ALLEGRO_BITMAP* T = load_bitmap_at_size(P.c_str(), wid, hei);
        GIF.push_back(T);
    }
    cout<<"GIF load finish"<<endl;
}

Gifobj::~Gifobj()
{
    for(int i=0;i<num;i++)
        al_destroy_bitmap(GIF[i]);
}

void Gifobj::draw()
{
    al_draw_bitmap(GIF[now],(float)pos.get_x(), (float)pos.get_y(), 0);
}

bool Gifobj::collide(Object *obj)
{
    Circle objpos = obj->get_pos();
    return center.collide(objpos);
}

void Gifobj::set_pos(int x, int y)
{
    pos.set_pos(x, y);
    center.set_pos(x+width/2, y+height/2);
}

void Gifobj::move_toward(Circle des)
{
    int fx = pos.get_x(), fy = pos.get_y();
    int cx = center.get_x(), cy = center.get_y();
    int px = des.get_x(), py = des.get_y();
    if((dir == L && px > cx) || (dir == R && px < cx)) change_dir();
    int dx = px-cx, dy = py-cy;
    if(dx) dx /= abs(dx);
    if(dy) dy /= abs(dy);
    set_pos(fx+dx, fy+dy);
}

void Gifobj::change_dir(){
    dir ^= 1;
}

void Gifobj::Move(){
    static int count_down = CD;
    count_down--;
    if(count_down)return;
    count_down = CD;
    if(dir)
        now = num/2 + (now + 1)% (num/2);
    else
        now = (now + 1)% (num/2);
}

