#include "EndingObj.h"

EndingObj::EndingObj(int x, int y, int r, ALLEGRO_BITMAP *img, int _kind):Object(x, y, r)
{
    bigfont = font_lib.ending_txt_b();
    smallfont = font_lib.ending_txt_s();
    pic = img;
    str = "ENDING";
    kind = _kind;
    gravity_cd = GRAVITY_END_CD;
    gravity = GRAVITY_END;
    hidden = false;

    switch(kind){
    case FISH:
        vx = 0;
        vy = 2;
        frame_cd = FISH_CD;
        hidden = true;
        break;
    case BIKE:
        vx = 0;
        vy = 0;
        angular_acceleration = 1;
        angle = 0;
        vangle = 0;
        frame_cd = 5;
        break;
    case MACHINE:
        vx = 0;
        vy = 0;
        hidden = true;
        break;
    case FISH_MEAT:
        vx = 0;
        vy = 0;
        angle = 0;
        hidden = true;
        break;
    case LIGHT:
        vx = 0;
        vy = 0;
        hidden = true;
        break;
    case CAN:
        vx = 0;
        vy = 0;
        hidden = true;
        break;
    default:
        dbg << "create EndingObj" << endl;
        break;
    }
}

EndingObj::~EndingObj()
{
    al_destroy_bitmap(pic);
}

void EndingObj::set_str(string s)
{
    str = s;
}

void EndingObj::update(){
    if(!hidden){
        switch(kind){
        case FISH:
            if(frame_cd == 5){
                rotate_r = 1;
                rotate_l = 0;
            }
            else if(frame_cd == 0){
                rotate_l = 1;
                rotate_r = 0;
                frame_cd = FISH_CD;
            }

            /*gravity_cd--;
            if(gravity_cd == 0){
                gravity_cd = GRAVITY_END_CD;
                vy += gravity;
            }*/
            break;
        case FISH_MEAT:
            gravity_cd--;
            if(gravity_cd == 0){
                gravity_cd = GRAVITY_END_CD;
                vy += gravity;
            }
            //cout<<vy<<endl;
            //cout<<gravity_cd<<endl;
        case BIKE:
            if(angle >= 180){
                angular_acceleration = 0;
            }
            if(rotate_r){
                if(frame_cd == 0){
                    frame_cd = 5;
                    vangle += angular_acceleration;
                }
                frame_cd--;
            }
            break;
        }
        angle += vangle;
        pos.set_pos(pos.get_x() + vx, pos.get_y() + vy);
    }
}

void EndingObj::draw()
{
    if(!hidden){
        if(kind == FISH){
            if(rotate_r){
                al_draw_rotated_bitmap(pic,
                                       al_get_bitmap_width(pic)/2, al_get_bitmap_height(pic)/2,
                                       pos.get_x(), pos.get_y(),
                                       20.0/360.0*2.0*PI, 0);
            }
            else if(rotate_l){
                al_draw_rotated_bitmap(pic,
                                       al_get_bitmap_width(pic)/2, al_get_bitmap_height(pic)/2,
                                       pos.get_x(), pos.get_y(),
                                       -20.0/360.0*2.0*PI, 0);
            }
            else{
                al_draw_bitmap(pic, pos.get_x()-al_get_bitmap_width(pic)/2, pos.get_y()-al_get_bitmap_height(pic)/2, 0);
            }
        }
        else if(kind == FISH_MEAT){
            if(rotate_r){
                al_draw_rotated_bitmap(pic,
                                       al_get_bitmap_width(pic)/2, al_get_bitmap_height(pic)/2,
                                       pos.get_x(), pos.get_y(),
                                       angle_radius(angle), 0);
                                       //cout<<angle<<endl;
            }
            else if(rotate_l){
                al_draw_rotated_bitmap(pic,
                                       al_get_bitmap_width(pic)/2, al_get_bitmap_height(pic)/2,
                                       pos.get_x(), pos.get_y(),
                                       -angle_radius(angle), 0);
                                       //cout<<angle<<endl;
            }
        }
        else if(kind == BIKE && rotate_r){
            al_draw_rotated_bitmap(pic,
                                   al_get_bitmap_width(pic)/2, al_get_bitmap_height(pic)/2,
                                   pos.get_x(), pos.get_y(),
                                   angle_radius(angle), 0);
        }
        else
            al_draw_bitmap(pic, pos.get_x()-al_get_bitmap_width(pic)/2, pos.get_y()-al_get_bitmap_height(pic)/2, 0);

        //cout<<pos.get_x() << " " << pos.get_y() << endl;
        //cout<<pos.get_x()-al_get_bitmap_width(pic)/2 << "  " << pos.get_y()-al_get_bitmap_height(pic)/2 << endl;
        //al_draw_filled_circle((float)pos.get_x(), (float)pos.get_y(), pos.get_r(), al_map_rgb(255, 255, 255));
        //al_draw_text(font, al_map_rgb(0, 0, 0), (float)pos.get_x(), (float)pos.get_y(), ALLEGRO_ALIGN_CENTER, str.c_str());
    }
}

