#include "Gaming.h"

/////////////////////////////////
// Gaming                      //
/////////////////////////////////

Gaming::Gaming(ALLEGRO_DISPLAY *dis):Interface(dis)
{
    inter_stat = INTER_CONTINUE;
    game_stat = GAM_NOTHING;

    bgm = load_bgm("../assets/music/pika_volley.ogg", ALLEGRO_PLAYMODE_LOOP);
    bg = load_bitmap_at_size("../assets/background/aquarium.jpg", WIN_W, WIN_H);

    start_but = new ButtonRD(WIN_W/2, WIN_H/2, 50);
    start_but->set_str("game");
    vis_objs.push_back(start_but);
    fish = new Gifobj(300, 10, 50, 150, 165, 18, 5, "../assets/fish/bubble_fish");
    vis_objs.push_back(fish);
    belly = new VerticalBar(30, 30, 30, 150, C::red, C::black);
    belly->set_current(50);
    vis_objs.push_back(belly);
    happy = new VerticalBar(60, 30, 30, 150, C::pink, C::black);
    happy->set_current(10);
    vis_objs.push_back(happy);
    mouse = new Object(0, 0, 1);

    // lower menu
    int mx = 0, my = WIN_H-80, mwid = WIN_W;
    int br = 30, bx = mx+2*br, by = my+br+10, dx = (mwid-14*br)/5+2*br;
    clothes = new ButtonRD(bx, by, 30, GAM_CLOTHES, "../assets/button/clothes.png");
    feed = new ButtonRD(bx+1*dx, by, 30, GAM_FEED, "../assets/button/fish_feed.png");
    ball = new ButtonRD(bx+2*dx, by, 30, GAM_BALL, "../assets/button/ball.png");
    touch = new ButtonRD(bx+3*dx, by, 30, GAM_TOUCH, "../assets/button/touch.png");
    bicycle = new ButtonRD(bx+4*dx, by, 30, GAM_BIKE, "../assets/button/bicycle.png");
    rod = new ButtonRD(bx+5*dx, by, 30, -1, "../assets/button/fishing_rod.png");
    buttons.push_back(clothes);
    buttons.push_back(feed);
    buttons.push_back(ball);
    buttons.push_back(touch);
    buttons.push_back(bicycle);
    buttons.push_back(rod);
    menu = new Menu(mx, my, 30, mwid, 80, C::brown, buttons);
    vis_objs.push_back(menu);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

//    al_play_sample_instance(bgm);
}

Gaming::~Gaming()
{
    al_stop_sample_instance(bgm);
    delete mouse;
    al_destroy_sample_instance(bgm);
}

int Gaming::run()
{
    if(!al_is_event_queue_empty(event_queue))
    {
        al_wait_for_event(event_queue, &event);
        inter_stat = process();
        game_stat = process_game();
        dbg << game_stat << endl;
        draw();
    }
    return inter_stat;
}

int Gaming::process()
{
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return INTER_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_TIMER)
    {
        if(fish) fish->Move();
        al_flip_display();
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
            if(menu->mouse_in(mouse)) menu->toggleHidden();
        }
    }
    return INTER_CONTINUE;
}

int Gaming::process_game()
{
    int nxt_stat = game_stat;
    // reveal button
    if(game_stat == GAM_NOTHING && clothes->isHidden()) clothes->toggleHidden();
    if(game_stat == GAM_NOTHING && happy->get_current() >= happy->get_full()/6 && feed->isHidden()) feed->toggleHidden();
    if(game_stat == GAM_NOTHING && happy->get_current() >= happy->get_full()/6*2 && ball->isHidden()) ball->toggleHidden();
    if(game_stat == GAM_NOTHING && happy->get_current() >= happy->get_full()/6*3 && touch->isHidden()) touch->toggleHidden();
    if(game_stat == GAM_NOTHING && happy->get_current() >= happy->get_full()/6*4 && bicycle->isHidden()) bicycle->toggleHidden();
    // allegro event handler
    if(event.type == ALLEGRO_EVENT_TIMER)
    {
        for(auto ptr:buttons) ptr->alert_chgCol();
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if(event.mouse.button == 1)
        {
            for(auto ptr:buttons)
            {
                Object *optr = ptr;
                if(optr->mouse_in(mouse)) nxt_stat = ptr->click();
                if(nxt_stat == -1) nxt_stat = game_stat;
            }
        }
    }
    // state function
    if(game_stat == GAM_CLOTHES)
    {
        happy->set_current(happy->get_current()+10);
        nxt_stat = GAM_NOTHING;
    }

    return nxt_stat;
}

/////////////////////////////////
// Menu                        //
/////////////////////////////////

Menu::Menu(int x, int y, int r, int wid, int hei, ALLEGRO_COLOR c, vector<ButtonRD*> but):Object(x, y, r)
{
    hidden = false;
    width = wid, height = hei;
    bg_color = c;
    hide_font = font_lib.icon_txt();
    buttons = but;
}

Menu::~Menu()
{
    for(auto ptr:buttons) delete ptr;
}

void Menu::toggleHidden()
{
    hidden ^= 1;
}

void Menu::draw()
{
    int x1 = pos.get_x(), y1 = pos.get_y();
    int x2 = x1+width, y2 = y1+height;
    if(hidden)
    {
        al_draw_text(hide_font, C::white, x1, y1, ALLEGRO_ALIGN_LEFT, ">>");
    }
    else
    {
        al_draw_filled_rectangle(x1, y1, x2, y2, bg_color);
        al_draw_text(hide_font, C::white, x1, y1, ALLEGRO_ALIGN_LEFT, "X");

        for(auto ptr:buttons) ptr->draw();
    }
}

/////////////////////////////////
// Vertical Bar                //
/////////////////////////////////

VerticalBar::VerticalBar(int x, int y, int wid, int hei, ALLEGRO_COLOR bar, ALLEGRO_COLOR edge):Object(x, y, 0)
{
    width = wid;
    full = hei, current = 0;
    bar_color = bar, edge_color = edge;
}

void VerticalBar::set_current(int val)
{
    current = val;
    if(current > full) current = full;
}

void VerticalBar::draw()
{
    int x1 = pos.get_x(), y1 = pos.get_y();
    int x2 = x1+width, y2 = y1+full+10;
    al_draw_rectangle(x1, y1, x2, y2, edge_color, 5);
    al_draw_filled_rectangle(x1+5, y2-5-current, x2-5, y2-5, bar_color);
}
