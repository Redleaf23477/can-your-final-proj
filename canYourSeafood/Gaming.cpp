#include "Gaming.h"

/////////////////////////////////
// Gaming                      //
/////////////////////////////////

Gaming::Gaming(ALLEGRO_DISPLAY *dis):Interface(dis), fish_goto(0, 0, 0)
{
    inter_stat = INTER_CONTINUE;
    game_stat = GAM_NOTHING;

    bg = load_bitmap_at_size("../assets/background/aquarium.jpg", WIN_W, WIN_H);

    mouse_touch = load_bitmap_at_size("../assets/hands/hand.png", 30, 30);
    mouse_grab = load_bitmap_at_size("../assets/hands/grab.png", 30, 30);
    cursor_touch = al_create_mouse_cursor(mouse_touch, 0, 0);
    cursor_grab = al_create_mouse_cursor(mouse_grab, 0, 0);
    grab = false;

    belly = new VerticalBar(30, 30, 30, 150, C::red, C::black);
    belly->set_current(50);
    happy = new VerticalBar(60, 30, 30, 150, C::pink, C::black);
    happy->set_current(10);
    fish = new Gifobj(300, 10, 70, 150, 165, 18, 5, "../assets/fish/bubble_fish");
    ball = new Ball(0, 0, 30, 8, "../assets/ball/");

    mouse = new Object(0, 0, 1);
    bellycd = 100;
    dropv = 0;

    // accessory
    belt = new Accessory(0, 0, 0, 25.26/100, 43.12/100, "../assets/accessory/belt/belt");
    hat = new Accessory(0, 0, 0, 1.16/100, 25.32/100, "../assets/accessory/hat/hat");
    glass = new Accessory(0, 0, 0, 8.2/100, 49.52/100, "../assets/accessory/glass/glass");

    // objects related to each button
    fishfeed = NULL;
    fish_goto = fish->get_pos();

    // lower menu
    int mx = 0, my = WIN_H-80, mwid = WIN_W, mhei = 80;
    int br = 30, bx = mx+2*br, by = my+br+10, dx = (mwid-14*br)/5+2*br, dy = 0;
    but_clothes = new ButtonRD(bx, by, 30, true, GAM_CLOTHES, "../assets/button/clothes.png");
    but_feed = new ButtonRD(bx+1*dx, by, 30, true, GAM_FEED, "../assets/button/fish_feed.png");
    but_ball = new ButtonRD(bx+2*dx, by, 30, true, GAM_BALL, "../assets/button/ball.png");
    but_touch = new ButtonRD(bx+3*dx, by, 30, true, GAM_TOUCH, "../assets/button/touch.png");
    but_bicycle = new ButtonRD(bx+4*dx, by, 30, true, GAM_BIKE, "../assets/button/bicycle.png");
    but_rod = new ButtonRD(bx+5*dx, by, 30, true, -1, "../assets/button/fishing_rod.png");
    control_buttons.push_back(but_clothes);
    control_buttons.push_back(but_feed);
    control_buttons.push_back(but_ball);
    control_buttons.push_back(but_touch);
    control_buttons.push_back(but_bicycle);
    control_buttons.push_back(but_rod);
    menu = new Menu(mx, my, 30, mwid, mhei, C::brown, control_buttons);

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

    // push_back all visible objects
    vis_objs.push_back(belly);
    vis_objs.push_back(happy);
    vis_objs.push_back(fish);
    vis_objs.push_back(belt);
    vis_objs.push_back(hat);
    vis_objs.push_back(glass);
    vis_objs.push_back(ball);
    vis_objs.push_back(menu);
    vis_objs.push_back(accessory);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

}

Gaming::~Gaming()
{
    delete mouse;
    al_destroy_bitmap(mouse_touch);
    al_destroy_bitmap(mouse_grab);
    al_destroy_mouse_cursor(cursor_touch);
    al_destroy_mouse_cursor(cursor_grab);
}

int Gaming::run()
{
    if(!al_is_event_queue_empty(event_queue))
    {
        al_wait_for_event(event_queue, &event);
        inter_stat = process();
        game_stat = process_game();
//        dbg << game_stat << endl;
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
        fish->Move();
        al_flip_display();
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse->set_pos(event.mouse.x, event.mouse.y);
    }

    if(game_stat == GAM_CUT) return INTER_DONE;
    return INTER_CONTINUE;
}

int Gaming::process_game()
{
    int nxt_stat = game_stat;
    // reveal button
    if(game_stat == GAM_NOTHING && but_clothes->isHidden()) but_clothes->toggleHidden();
    if(game_stat == GAM_NOTHING && (!but_clothes->isAlert()) && but_feed->isHidden()) but_feed->toggleHidden();
    if(game_stat == GAM_NOTHING && happy->get_current() >= happy->get_full()/6*2 && but_ball->isHidden()) but_ball->toggleHidden();
    if(game_stat == GAM_NOTHING && happy->get_current() >= happy->get_full()/6*3 && but_touch->isHidden()) but_touch->toggleHidden();
    if(game_stat == GAM_NOTHING && happy->get_current() >= happy->get_full()/6*4 && but_bicycle->isHidden()) but_bicycle->toggleHidden();
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

        // not bicycle: normal moving
        if(game_stat != GAM_BIKE)
        {
            belt->update(fish->get_pos(), fish->get_width(), fish->get_height(), fish->get_dir());
            hat->update(fish->get_pos(), fish->get_width(), fish->get_height(), fish->get_dir());
            glass->update(fish->get_pos(), fish->get_width(), fish->get_height(), fish->get_dir());
            if(game_stat == GAM_FEED && fishfeed) fish->move_toward(fishfeed->get_pos());
        }
    }

    // state function
    if(game_stat == GAM_NOTHING)
    {
        // fish and accessory move
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            if(rand()%71 == 0) fish_goto.set_pos(rand()%(WIN_W-50), rand()%(WIN_H-100));
            fish->move_toward(fish_goto);
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1)
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
            // initial ball and fish in GAM_BALL
            if(nxt_stat == GAM_BALL)
            {
                if(fish->get_dir() == 1) fish->change_dir();
                ball->toggleHidden();
                ball->set_pos(fish->get_pos().get_x(), fish->get_pos().get_y());
                ball->set_v(-rand()%5-1, -rand()%5-1);
            }
            // change mouse sprite in GAM_TOUCH
            if(nxt_stat == GAM_TOUCH)
            {
                // change image of MOUSE_CURSOR_ALLEGRO
                al_set_mouse_cursor(display, cursor_touch);
            }
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
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            if(fish->collide(ball))
            {
                ball->set_v(-rand()%5-1, -rand()%5-1);
                belly->set_current(belly->get_current()-5);
                happy->set_current(happy->get_current()+5);
            }
            if(ball->Move() == false) nxt_stat = GAM_NOTHING, ball->toggleHidden();
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1)
        {
            if(ball->collide(mouse)) ball->set_v(-ball->get_vx(), -ball->get_vy());
        }
    }
    else if(game_stat == GAM_TOUCH)
    {
        // fish and accessory move
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            if(grab && fish->collide(mouse))
            {
                fish_goto.set_pos(rand()%(WIN_W-50), rand()%(WIN_H-100));
                happy->set_current(happy->get_current()-1);
            }
            else if(rand()%71 == 0) fish_goto.set_pos(rand()%(WIN_W-50), rand()%(WIN_H-100));
            fish->move_toward(fish_goto);
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1)
        {
            if(but_touch->collide(mouse))
            {
                al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
                nxt_stat = GAM_NOTHING;
            }
            else
            {
                grab = true;
                al_set_mouse_cursor(display, cursor_grab);
            }
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && event.mouse.button == 1)
        {
            grab = false;
            al_set_mouse_cursor(display, cursor_touch);
        }
    }
    else if(game_stat == GAM_BIKE)
    {
        if(event.type == ALLEGRO_EVENT_TIMER)
        {
            int fx = fish->get_pos().get_x(), fy = fish->get_pos().get_y();
            dropv += 1;
            fish->set_pos(fx, fy+dropv);
        }
        if(fish->get_pos().get_y() > WIN_H) nxt_stat = GAM_CUT;
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

/////////////////////////////////
// Ball                        //
/////////////////////////////////

Ball::Ball(int x, int y, int r, int picN, const char *path):Object(x, y, r), center(x-r, y-r, r)
{
    pic_num = picN;
    string folder(path), fileName;
    for(int i = 0; i < picN; i++)
    {
        stringstream ss; ss << folder << i << ".png";
        ss >> fileName;
        cout << "load: " << fileName << endl;
        ALLEGRO_BITMAP *tmp = load_bitmap_at_size(fileName.c_str(), 2*r, 2*r);
        PIC.push_back(tmp);
    }
    cd = CD = 10;
    idx = 0, g = 1, hidden = true;
    toDraw = PIC[idx];
}

Ball::~Ball()
{
    for(int i = 0; i < pic_num; i++) al_destroy_bitmap(PIC[i]);
}

void Ball::set_pos(int x, int y)
{
    pos.set_pos(x, y);
    center.set_pos(x+pos.get_r(), y+pos.get_r());
}

void Ball::set_v(int x, int y)
{
    vx = x, vy = y;
}

bool Ball::collide(Object *obj)
{
    Circle objpos = obj->get_pos();
    return center.collide(objpos);
}

bool Ball::Move()  // return still exist
{
    int cx = pos.get_x(), cy = pos.get_y();
    int nx = cx+vx, ny = cy+vy;
    if(nx < 0 || nx > WIN_W || ny > WIN_H) return false;
    if(--cd == 0)
    {
        vy += g;
        if(vx > 0) idx = (idx+1)%pic_num;
        else idx = (idx-1+pic_num)%pic_num;
        cd = CD;
    }
    set_pos(nx, ny);
    return true;
}

void Ball::toggleHidden()
{
    hidden ^= 1;
}

void Ball::draw()
{
    if(!hidden) al_draw_bitmap(PIC[idx], (float)pos.get_x(), (float)pos.get_y(), 0);
}
