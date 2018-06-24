#include "Opening.h"
#define PI 3.1415926

namespace FA{
    double thick = 2000;
    double R = 5;
    double pos[4] = {WIN_W/3 - 150, WIN_H - 160,
                     WIN_W*2/3 + 150, WIN_H - 160};
    double angle = -30;
    double Gravity = 0.1;
    double x_speed = 3;
    double y_speed = 8;


    int Fish_Data[4] = {200,220,18,5};
    string path = "../assets/fish/bubble_fish";
    bool play = false;
}

void Opening::animation_init(){
    using namespace FA;
    pos[0] = WIN_W/3 - 150;
    pos[1] = WIN_H - 180;
    angle = -30;
    y_speed = 8;
}

void Opening::animation(){
    using namespace FA;
    if(y_speed > 0)
        y_speed -= Gravity;
    else
        y_speed  = 0;
    pos[ 0 ] += x_speed;
    pos[ 1 ] -= y_speed;


    if(angle < 0 && y_speed < 2)
        angle += 1;
    if(angle > 0)
        angle = 0;
}


Opening::Opening(ALLEGRO_DISPLAY *dis):Interface(dis)
{
    inter_stat = INTER_CONTINUE;

    SE = al_load_sample( "../assets/music/Dolphin.wav" );

    bg = load_bitmap_at_size("../assets/background/Opening.png",WIN_W,WIN_H);

    start_but = new ButtonRD(WIN_W/2, WIN_H/2, 50);
    start_but->set_str("START");


    fish1 = new Gifobj ( FA::pos[0], FA::pos[1], 100,
                       200,220,18,5,
                       FA::path.c_str());
    fish1->change_dir();

    fish2 = new Gifobj ( FA::pos[2], FA::pos[3], 100,
                       200,220,18,5,
                       FA::path.c_str());

    vis_objs.push_back(start_but);

    mouse = new Object(0, 0, 1);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

Opening::~Opening()
{
    //al_stop_sample_instance( bgm );
    delete mouse;
    if(fish1) delete fish1;
    if(fish2) delete fish2;
    if(SE) al_destroy_sample(SE);
    //if(bgm) al_destroy_sample_instance(bgm);
}

int Opening::run()
{
    if(!al_is_event_queue_empty(event_queue))
    {
        inter_stat = process();
        draw();
    }
    return inter_stat;
}

void Opening::draw(){
    al_clear_to_color( al_map_rgb(255,255,255) );

    if(bg)
        al_draw_bitmap(bg,0,0,0);

    ALLEGRO_BITMAP* FN  = fish1->now_pic();
    ALLEGRO_BITMAP* FN2 = fish2->now_pic();

    al_draw_rotated_bitmap
    ( FN, al_get_bitmap_width(FN)/2, al_get_bitmap_height(FN)/2,
      FA::pos[0], FA::pos[1],
      angle_radius( FA::angle ), 0 );

    al_draw_rotated_bitmap
    ( FN2, al_get_bitmap_width(FN2)/2, al_get_bitmap_height(FN2)/2,
      FA::pos[2], FA::pos[3],
      angle_radius( 30 ), 0 );

    for(auto obj:vis_objs) obj->draw();


    if(FA::thick>0)
        al_draw_circle(WIN_W/2,WIN_H/2,500,
                       al_map_rgb(123,200,156) , FA::thick);

    if(FA::thick<500 && FA::R<3000)
        al_draw_arc(WIN_W/2,WIN_H/2,FA::R,
                    0,2*PI,
                    al_map_rgb(123,200,156),
                    (FA::R<=100) ? FA::R : 100 );
}

int Opening::process()
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return INTER_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_TIMER)
    {
        al_flip_display();
        update();
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse->set_pos(event.mouse.x, event.mouse.y);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {

        if(event.mouse.button == 1)
        {

            if(fish1->rotate_collide(mouse))
                FA::play = true;

            if(fish2->rotate_collide(mouse))
                al_play_sample(SE, 2.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
            else
                al_play_sample(click, 2.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);

            if(start_but->collide(mouse))
                return INTER_DONE;
        }
        if(event.mouse.button == 2)
        {
            FA::play = false;
        }

    }

    return INTER_CONTINUE;
}

void Opening::update(){

    fish1->Move();
    fish2->Move();

    if(FA::play && FA::pos[0] <= WIN_W + al_get_bitmap_width( fish1->now_pic() ))
    {
        animation();
    }
    else{
        animation_init();
        FA::play = false;
    }

    fish1->set_pos( FA::pos[0], FA::pos[1]);

    if(FA::thick>0)
        FA::thick-=7;
    if(FA::thick<500 && FA::R < 3000)
        FA::R += 5;

}

