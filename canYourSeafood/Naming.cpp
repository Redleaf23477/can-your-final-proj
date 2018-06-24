#include "Naming.h"
namespace EA{
    double angle = 0;
    double range = 8;
    double rate = 0.4;
    double pos[2] = { WIN_W/2, WIN_H/2-80 };
    int state = 0;

    bool inRange ( double x, double L, double R){
        return ( x >= L ) && ( x <= R );
    }
}

void Naming::animation(){
    using namespace EA;
    switch (state){
    case 0:
        angle += rate;
        if (angle >= range)
            state = 1;
        break;
    case 1:
        angle -= rate;
        if( angle <= -range)
            state = 2;
        break;
    case 2:
        angle += rate;
        if( angle >= 0)
            state = 3;
        break;
    case 3:
        angle = 0;
        break;
    }
}

void Naming::animation_init(){
    using namespace EA;
    angle = 0;
    state = 0;
}

Naming::Naming(ALLEGRO_DISPLAY *dis):Interface(dis)
{
    inter_stat = INTER_CONTINUE;

    egg = load_bitmap_at_size("../assets/fish/egg.png",300,300);
    SE = al_load_sample( "../assets/music/Dolphin.wav" );
    bg = load_bitmap_at_size( "../assets/background/Naming.jpg", WIN_W, WIN_H );

    start_but = new ButtonRD(WIN_W/2, WIN_H - 150, 40);
    start_but->set_str("Enter");
    vis_objs.push_back(start_but);

    txt = new Textbox(WIN_W/2 - 75, WIN_H/2 + 50, 150, 30);
    vis_objs.push_back(txt);

    mouse = new Object(0, 0, 1);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

Naming::~Naming()
{
    delete mouse;
}

void Naming::draw(){
//    static double angle = 0;
    al_clear_to_color( C::dark_orange );

    /*
    al_draw_filled_rectangle
    ( EA::pos[0] - al_get_bitmap_width(egg)*3/8, EA::pos[1] - al_get_bitmap_height(egg)*2/5,
      EA::pos[0] + al_get_bitmap_width(egg)*3/8, EA::pos[1] + al_get_bitmap_height(egg)*2/5, C::black);
    */
    if(bg)al_draw_bitmap(bg, 0, 0, 0);

    al_draw_rotated_bitmap
    ( egg , al_get_bitmap_width(egg)/2, al_get_bitmap_height(egg)/2,
      WIN_W/2, WIN_H/2 - 80,
      angle_radius( EA::angle ), 0 );

    for( auto& o: vis_objs )
        o->draw();
}

int Naming::run()
{
    if(!al_is_event_queue_empty(event_queue))
    {
        inter_stat = process();
        draw();
    }
    return inter_stat;
}

int Naming::process()
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return INTER_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_TIMER)
    {
        al_flip_display();
        animation();
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse->set_pos(event.mouse.x, event.mouse.y);
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if(event.mouse.button == 1)
        {
            if(start_but->collide(mouse)) return INTER_DONE;

            if(EA::inRange(event.mouse.x, EA::pos[0] - al_get_bitmap_width(egg)*3/8, EA::pos[0] + al_get_bitmap_width(egg)*3/8) &&
               EA::inRange(event.mouse.y, EA::pos[1] - al_get_bitmap_height(egg)*2/5, EA::pos[1] + al_get_bitmap_height(egg)*2/5) )
               {
                   EA::state = 0;
                   al_play_sample(SE, 2.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
               }
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        txt->run(event);
    }
    return INTER_CONTINUE;
}

