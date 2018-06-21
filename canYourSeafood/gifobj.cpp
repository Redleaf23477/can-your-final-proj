#include "gifobj.h"
#define L 0
#define R 1
Gifobj::Gifobj(int x, int y, int r, int wid, int hei, int num_of_picture, int cd, const char *path):Object(x, y, r)
{
    dir = 0;
    now = 0;
    num = num_of_picture;
    CD = cd;

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

