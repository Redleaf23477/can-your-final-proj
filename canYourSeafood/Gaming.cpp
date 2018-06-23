#include "Gaming.h"

/////////////////////////////////
// Gaming                      //
/////////////////////////////////

Gaming::Gaming(ALLEGRO_DISPLAY *dis):Interface(dis), fish_goto(0, 0, 0)
{
    inter_stat = INTER_CONTINUE;
    game_stat = GAM_NOTHING;

    bgm = load_bgm("../assets/music/pika_volley.ogg", ALLEGRO_PLAYMODE_LOOP);
    bg = load_bitmap_at_size("../assets/background/aquarium.jpg", WIN_W, WIN_H);

    start_but = new ButtonRD(WIN_W/2, WIN_H/2, 50);
    start_but->set_str("game");
    vis_objs.push_back(start_but);
    belly = new VerticalBar(30, 30, 30, 150, C::red, C::black);
    belly->set_current(50);
    vis_objs.push_back(belly);
    happy = new VerticalBar(60, 30, 30, 150, C::pink, C::black);
    happy->set_current(10);
    vis_objs.push_back(happy);
    fish = new Gifobj(300, 10, 70, 150, 165, 18, 5, "../assets/fish/bubble_fish");
    vis_objs.push_back(fish);

    mouse = new Object(0, 0, 1);
    bellycd = 100;

    // accessory
    belt = new Accessory(0, 0, 0, 25.26/100, 43.12/100, "../assets/accessory/belt/belt");
    vis_objs.push_back(belt);
    hat = new Accessory(0, 0, 0, 1.16/100, 25.32/100, "../assets/accessory/hat/hat");
    vis_objs.push_back(hat);
    glass = new Accessory(0, 0, 0, 8.2/100, 49.52/100, "../assets/accessory/glass/glass");
    vis_objs.push_back(glass);

    // objects related to each button
    fishfeed = NULL;
    fish_goto = fish->get_pos();

    // lower menu
    int mx = 0, my = WIN_H-80, mwid = WIN_W, mhei = 80;
    int br = 30, bx = mx+2*br, by = my+br+10, dx = (mwid-14*br)/5+2*br, dy = 0;
    clothes = new ButtonRD(bx, by, 30, true, GAM_CLOTHES, "../assets/button/clothes.png");
    feed = new ButtonRD(bx+1*dx, by, 30, true, GAM_FEED, "../assets/button/fish_feed.png");
    ball = new ButtonRD(bx+2*dx, by, 30, true, GAM_BALL, "../assets/button/ball.png");
    touch = new ButtonRD(bx+3*dx, by, 30, true, GAM_TOUCH, "../assets/button/touch.png");
    bicycle = new ButtonRD(bx+4*dx, by, 30, true, GAM_BIKE, "../assets/button/bicycle.png");
    rod = new ButtonRD(bx+5*dx, by, 30, true, -1, "../assets/button/fishing_rod.png");
    control_buttons.push_back(clothes);
    control_buttons.push_back(feed);
    control_buttons.push_back(ball);
    control_buttons.push_back(touch);
    control_buttons.push_back(bicycle);
    control_buttons.push_back(rod);
    menu = new Menu(mx, my, 30, mwid, mhei, C::brown, control_buttons);
    vis_objs.push_back(menu);

    // accessory menu
    mx = 0, my = 250, mwid = 80, mhei = 220;
    br = 30, bx = mx+br+10, by = my+br+10, dx = 0, dy = 2*br+10;
    but_belt = new ButtonRD(bx, by, br, false, ACC_BELT, "../assets/accessory/belt/belt_icon.png");
    but_hat = new ButtonRD(bx, by+1*dy, br, false, ACC_HAT, "../assets/accessory/hat/hat_icon.png");
    but_glass = new ButtonRD(bx, by+2*dy, br, false, ACC_GLASS, "../assets/accessory/glass/glass_icon.png");
    accessory_buttons.push_back(but_belt);
    accessory_buttons.push_back(but_hat);
    accessory_buttons.push_back(but_glass);
    accessory = new Menu(mx, my, 30, mwid, mhei, C::brown, accessory_buttons);
    accessory->toggleHidden();
    vis_objs.push_back(accessory);

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
        if(fish)
        {
            fish->Move();
        }
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
            if(start_but->collide(mouse)) return INTER_DONE;
        }
    }
    if(game_stat == GAM_BIKE) return INTER_DONE;
    return INTER_CONTINUE;
}

int Gaming::process_game()
{
    int nxt_stat = game_stat;
    // reveal button
    if(game_stat == GAM_NOTHING && clothes->isHidden()) clothes->toggleHidden();
    if(game_stat == GAM_NOTHING && (!clothes->isAlert()) && feed->isHidden()) feed->toggleHidden();
    if(game_stat == GAM_NOTHING && happy->get_current() >= happy->get_full()/6*2 && ball->isHidden()) ball->toggleHidden();
    if(game_stat == GAM_NOTHING && happy->get_current() >= happy->get_full()/6*3 && touch->isHidden()) touch->toggleHidden();
    if(game_stat == GAM_NOTHING && happy->get_current() >= happy->get_full()/6*4 && bicycle->isHidden()) bicycle->toggleHidden();
    // allegro event handler
    if(event.type == ALLEGRO_EVENT_TIMER)
    {
        // belly and happy count down
        if(bellycd-- == 0)
        {
            belly->set_current(belly->get_current()-1);
            happy->set_current(happy->get_current()-1);
            bellycd = 100;
        }
        // alert_button
        for(auto ptr:control_buttons) ptr->alert_chgCol();
        // fish and accessory move
        if(game_stat == GAM_NOTHING)
        {
            if(rand()%71 == 0) fish_goto.set_pos(rand()%(WIN_W-50), rand()%(WIN_H-100));
            fish->move_toward(fish_goto);
        }
        belt->update(fish->get_pos(), fish->get_width(), fish->get_height(), fish->get_dir());
        hat->update(fish->get_pos(), fish->get_width(), fish->get_height(), fish->get_dir());
        glass->update(fish->get_pos(), fish->get_width(), fish->get_height(), fish->get_dir());
        if(game_stat == GAM_FEED && fishfeed) fish->move_toward(fishfeed->get_pos());
    }

    // state function
    if(game_stat == GAM_NOTHING)
    {
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1)
        {
            for(auto ptr:control_buttons)
            {
                Object *optr = ptr;
                if(optr->collide(mouse)) nxt_stat = ptr->click();
                if(nxt_stat == -1) nxt_stat = game_stat;
            }
            // toggle accessory menu
            if(nxt_stat == GAM_CLOTHES)
            {
                if(accessory->ishidden()) accessory->toggleHidden();
            }
            else if(!accessory->ishidden()) accessory->toggleHidden();
        }
    }
    else if(game_stat == GAM_CLOTHES)
    {
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1)
        {
            if(but_belt->collide(mouse)) belt->toggleHidden(), accessory->toggleHidden(), nxt_stat = GAM_NOTHING, happy->set_current(happy->get_current()+10);
            if(but_hat->collide(mouse)) hat->toggleHidden(), accessory->toggleHidden(), nxt_stat = GAM_NOTHING, happy->set_current(happy->get_current()+10);
            if(but_glass->collide(mouse)) glass->toggleHidden(), accessory->toggleHidden(), nxt_stat = GAM_NOTHING, happy->set_current(happy->get_current()+10);
        }
    }
    else if(game_stat == GAM_FEED)
    {
        int mx = mouse->get_pos().get_x(), my = mouse->get_pos().get_y();
        if(fishfeed == NULL)
        {
            fishfeed = new Object(mx, my, 10);
            vis_objs.push_back(fishfeed);
        }
        fishfeed->set_pos(mx, my);
        if(fish->collide(fishfeed))
        {
            Object *bye = fishfeed; delete bye; fishfeed = NULL;
            vis_objs.pop_back();
            belly->set_current(belly->get_current()+10);
            happy->set_current(happy->get_current()+10);
            nxt_stat = GAM_NOTHING;
        }
    }
    else if(game_stat == GAM_BALL)
    {
        //
    }
    else if(game_stat == GAM_TOUCH)
    {
        //
    }
    else if(game_stat == GAM_BIKE)
    {
        //
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
//        al_draw_text(hide_font, C::white, x1, y1, ALLEGRO_ALIGN_LEFT, ">>");
    }
    else
    {
        al_draw_filled_rectangle(x1, y1, x2, y2, bg_color);
//        al_draw_text(hide_font, C::white, x1, y1, ALLEGRO_ALIGN_LEFT, "X");

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
    if(current < 0) current = 0;
}

void VerticalBar::draw()
{
    int x1 = pos.get_x(), y1 = pos.get_y();
    int x2 = x1+width, y2 = y1+full+10;
    al_draw_rectangle(x1, y1, x2, y2, edge_color, 5);
    al_draw_filled_rectangle(x1+5, y2-5-current, x2-5, y2-5, bar_color);
}

/////////////////////////////////
// Accessory                   //
/////////////////////////////////

Accessory::Accessory(int x, int y, int r, float rx, float ry, const char *path):Object(x, y, r)
{
    hidden = true;
    ratio_x = rx, ratio_y = ry;
    string str(path);
    string lft = str+"_left.png";
    string rgh = str+"_right.png";
    ALLEGRO_BITMAP *ori = al_load_bitmap(lft.c_str());
    int ow = al_get_bitmap_width(ori), oh = al_get_bitmap_height(ori);
    pic_left = load_bitmap_at_size(lft.c_str(), ow/2, oh/2);
    pic_right = load_bitmap_at_size(rgh.c_str(), ow/2, oh/2);
    width = ow/2, height = oh/2;
    toDraw = pic_right;
}

Accessory::~Accessory()
{
    al_destroy_bitmap(pic_left);
    al_destroy_bitmap(pic_right);
}

void Accessory::update(Circle pos, int wid, int hei, int dir)
{
    int x, y;
    if(dir == 0)  // L == 0, R == 1
    {
        x = pos.get_x()+ratio_x*wid;
        y = pos.get_y()+ratio_y*hei;
        toDraw = pic_left;
    }
    else
    {
        x = pos.get_x()+wid-ratio_x*wid-width;
        y = pos.get_y()+ratio_y*hei;
        toDraw = pic_right;
    }
    set_pos(x, y);
}

void Accessory::toggleHidden()
{
    hidden ^= 1;
}

void Accessory::draw()
{
    if(!hidden) al_draw_bitmap(toDraw, (float)pos.get_x(), (float)pos.get_y(), 0);
}
