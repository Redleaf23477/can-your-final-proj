#include "Opening.h"
#define PI 3.1415926
double thick = 1200;
double R = 5;
Opening::Opening(ALLEGRO_DISPLAY *dis):Interface(dis)
{
    bg = load_bitmap_at_size("../assets/background/Opening.png",WIN_W,WIN_H);
    stat = INTER_CONTINUE;
    start_but = new ButtonRD(WIN_W/2, WIN_H/2, 50);
    start_but->set_str("START");
    vis_objs.push_back(start_but);
    mouse = new Object(0, 0, 1);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

Opening::~Opening()
{
    delete mouse;
}

int Opening::run()
{
    if(!al_is_event_queue_empty(event_queue))
    {
        stat = process();
        draw();
    }
    return stat;
}

void Rotate(double center_x=0,double center_y=0,double T=10){
    for(int i=0;i<4;i++){
        double dx = x[i] - center_x;
        double dy = y[i] - center_y;
        dx = dx*cos(PI/T) - dy*sin(PI/T);
        dy = dx*sin(PI/T) + dy*cos(PI/T);
        x[i] = dx + center_x;
        y[i] = dy + center_y;
    }
}

void Opening::draw(){
    al_clear_to_color( al_map_rgb(255,255,255) );
    if(bg)
        al_draw_bitmap(bg,0,0,0);
    for(auto obj:vis_objs) obj->draw();
    if(thick>0)
        al_draw_circle(WIN_W/2,WIN_H/2,500, al_map_rgb(123,200,156) , thick);
    if(thick<500 && R<3000)
        al_draw_arc(WIN_W/2,WIN_H/2,R,0,2*PI, al_map_rgb(123,200,156), (R<=100) ? R : 100 );
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
        if(thick>0)
            thick-=7;
        if(thick<500 && R < 3000)
            R += 5;
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse->set_pos(event.mouse.x, event.mouse.y);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if(event.mouse.button == 1)
        {
            if(start_but->mouse_in(mouse)) return INTER_DONE;
        }
    }
    return INTER_CONTINUE;
}

