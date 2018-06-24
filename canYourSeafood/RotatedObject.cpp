#include "RotateObject.h"

RotateObject::RotateObject(const char *path,int x,int y,int r,int w,int h) : Object(x,y,r)
{
    pic = load_bitmap_at_size( path, w, h);
    degree = 0;
}

RotateObject::~RotateObject(){
    if(pic)
        al_destroy_bitmap(pic);
}

void RotateObject::set_degree(double degree){
    this->degree = degree;
}

void RotateObject::draw(){
    double pos[2] = {this->pos.get_x(),
                     this->pos.get_y()};

    al_draw_rotated_bitmap
    ( pic, al_get_bitmap_width(pic)/2, al_get_bitmap_height(pic)/2,
      pos[0],pos[1], angle_radius( degree ), 0);
    //al_draw_filled_circle( pos[0], pos[1], 50, al_map_rgb(0,0,0));
}

double RotateObject::get_degree(){
    return degree;
}
