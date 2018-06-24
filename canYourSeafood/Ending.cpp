#include "Ending.h"

Ending::Ending(ALLEGRO_DISPLAY *dis):Interface(dis)
{
    stat = INTER_CONTINUE;
    start_but = new ButtonRD(WIN_W/2, WIN_H/2, 50);
    start_but->set_str("end");
    vis_objs.push_back(start_but);
    mouse = new Object(0, 0, 1);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_reserve_samples(10);
    //machine_sound = load_bgm("");
    blood_sound[0] = al_load_sample("../assets/end/music/blood1.wav");
    blood_sound[1] = al_load_sample("../assets/end/music/blood2.wav");
    screaming = al_load_sample("../assets/end/music/scream.wav");
    //trumpet = al_load_sample("");
    lightUP_sound = al_load_sample("../assets/end/music/switch2.wav");
    ai_chi_wei = al_load_sample("../assets/end/music/ai_chi_wei.wav");
    //ED = load_bgm("");

    img_fish_meat[0] = load_bitmap_at_size("../assets/end/meat/fish1.png", 50, 50);
    img_fish_meat[1] = load_bitmap_at_size("../assets/end/meat/fish2.png", 80, 80);
    img_fish_meat[2] = load_bitmap_at_size("../assets/end/meat/fish1.png", 60, 60);  // TO BE REVISED!!!
    img_fish_meat[3] = load_bitmap_at_size("../assets/end/meat/fish2.png", 85, 85);  // TO BE REVISED!!!
    img_fish_meat[4] = load_bitmap_at_size("../assets/end/meat/fish1.png", 65, 65);  // TO BE REVISED!!!

    machine_img[0] = load_bitmap_at_size("../assets/end/machine/0.png", 714*0.5, 536*0.5);
    machine_img[1] = load_bitmap_at_size("../assets/end/machine/1.png", 714*0.5, 536*0.5);
    machine_img[2] = load_bitmap_at_size("../assets/end/machine/2.png", 714*0.5, 536*0.5);

    blood[0] = load_bitmap_at_size("../assets/end/blood/0.png", 1000*0.4, 864*0.4);
    blood[1] = load_bitmap_at_size("../assets/end/blood/1.png", 800, 600);
    blood[2] = load_bitmap_at_size("../assets/end/blood/2q.png", 640*0.8, 480*0.8);

    // create all EndingObjs
    ALLEGRO_BITMAP* fish_img = load_bitmap_at_size("../assets/fish/bubble_fish/9.png", 300*0.5, 329*0.5);
    fish = new EndingObj(WIN_W/2, 0+al_get_bitmap_height(fish_img)/2, 70, fish_img, FISH);
    machine = new EndingObj(WIN_W/2, WIN_H/2, 135, machine_img[0], MACHINE);
    vis_obj_ending.push_back(fish);
    vis_obj_ending.push_back(machine);

    for(int i = 0; i < numOfFishMeat; i++){  // create fish meats
        fish_meat[i] = new EndingObj(WIN_W/2, WIN_H/2+110-i*70, 1, img_fish_meat[i], FISH_MEAT);
        fish_meat[i]->rotate_r = (i+1)%2;
        fish_meat[i]->rotate_l = i%2;
        fish_meat[i]->set_vangle(3);
        vis_obj_ending.push_back(fish_meat[i]);
    }

    light = new EndingObj(200, 250, 1, load_bitmap_at_size("../assets/end/spotlight/6.jpg", 956, 640), LIGHT);
    can = new EndingObj(195, 440, 1, load_bitmap_at_size("../assets/end/can/can1.png", 551*0.25, 467*0.25), CAN);
    vis_obj_ending.push_back(light);
    vis_obj_ending.push_back(can);

    bike = new EndingObj(WIN_W/2, WIN_H/2, 1, load_bitmap_at_size("../assets/button/machine.png", 714*0.5, 536*0.5), BIKE);
    vis_obj_ending.push_back(bike);
}

Ending::~Ending()
{
    delete mouse;
    delete start_but;
}

int Ending::run()
{
    if(!al_is_event_queue_empty(event_queue))
    {
        stat = process();
        draw();
    }
    return stat;
}

void Ending::update(){
    // update all EndingObjs
    if(!bike->hidden && bike->get_angle() >= 180){
        passing_counter++;
        bike->set_vangle(0);
        cout << passing_counter << endl;
        if(passing_counter >= 30){
            bike->hidden = true;
            fish->hidden = false;
            machine->hidden = false;
            passing_counter = 0;
        }
    }
    else if(!bike->hidden && !bike->rotate_r){
        if(passing_counter >= 30){
            bike->rotate_r = 1;
            bike->set_vangle(1);
            passing_counter = 0;
        }
        passing_counter++;
    }

    bike->update();

    fish->update();
    if(fish->beneath(machine)){  // control fish animation
        if(!fish_paused){
            fish_paused = true;
            fish->set_speed(0, 0);
            fish->rotate_l = 1;
            al_play_sample(screaming, 1.5, 0, 1.25, ALLEGRO_PLAYMODE_ONCE, 0);
        }
        else if(fish_paused){
            if(fish_pause_counter >= 20){
                fish->set_speed(0, 1);
                fish->count_frame_cd();

                if(fish_pause_counter == 25)
                    al_play_sample(blood_sound[0], 1.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                if(blood_count == blood_cd){  // control blood animation
                    blood_mode++;
                    blood_cd = rand()%21+40;
                    blood_count = 0;
                    if(blood_mode <= 5)
                        al_play_sample(blood_sound[(blood_mode+1)%2], (blood_mode+1)%2 == 0 ? 1.5 : 2.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    //cout<<blood_cd;
                    //cout<<blood_mode<<endl;
                }
                blood_count++;
            }
            fish_pause_counter++;
        }
    }
    if(fish->get_posy() > WIN_H + al_get_bitmap_height(fish->get_pic())/2){
        fish->hidden = true;
    }

    for(int i = 0; i < numOfFishMeat; i++)
        fish_meat[i]->update();

    if(blood_mode == 6){  // move machine upward
        machine->set_speed(0, -3);

        for(int i = 0; i < numOfFishMeat; i++){
            fish_meat[i]->hidden = false;
            if(blood_count <= 15){
                fish_meat[i]->set_speed(0, blood_count/4);
            }
            else if(blood_count <= 26){
                fish_meat[i]->set_speed(0, (-blood_count+26)/2);
            }
            else{
                fish_meat[i]->set_speed(0, 0);
                fish_meat[i]->set_gravity(0);
            }
        }
    }

    if(machine->get_posy()+al_get_bitmap_height(machine->get_pic())/2 < 0)
        passing_counter++;
    if(passing_counter == 120){
        cout<<"drop";
        for(int i = 0; i < numOfFishMeat; i++){
            fish_meat[i]->set_speed(0, 1);
            fish_meat[i]->set_gravity(GRAVITY_END+3);
        }
    }

    machine->update();
    machine_cd--;
    if(machine_cd == 0){
        machine_cd = 3;
        machine_frame_count = (machine_frame_count+1)%3;
    }
    machine->set_pic(machine_img[machine_frame_count]);

    light->update();
    can->update();
    if(passing_counter == 240){
        al_play_sample(lightUP_sound, 3.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    }
    if(passing_counter == 245){
        light->hidden = false;
        can->hidden = false;
    }
    if(passing_counter == 300)
        al_play_sample(ai_chi_wei, 2.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    /*if(passing_counter == 420){
        al_play_sample_instance(ED);
    }*/

}

void Ending::draw(){
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // draw all EndingObjs
    bike->draw();

    fish->draw();
    if(!fish->hidden) al_draw_filled_rectangle(200, 265, 600, 800, al_map_rgb(0, 0, 0));

    for(int i = 0; i < numOfFishMeat; i++){
        fish_meat[i]->draw();
    }

    if(!fish_meat[0]->hidden)
        al_draw_filled_rectangle(200, machine->get_posy()-248, 600, machine->get_posy()+105, al_map_rgb(0, 0, 0));
    machine->draw();

    switch(blood_mode){
    //case 7:
    case 6:
    case 5:
    case 4:
    case 3:
        al_draw_bitmap(blood[2], -130, -50, 0);
    case 2:
        al_draw_bitmap(blood[1], 0, 0, 0);
    case 1:
        al_draw_bitmap(blood[0], 80, 0, 0);
    case 0:
        break;
    default:
        break;
    }

    light->draw();
    can->draw();

    //========== ADDING TEXTBOX ==========//

}

int Ending::process()
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return INTER_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_TIMER)
    {
        update();
        al_flip_display();
        cout << bike->get_angle() << endl;
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse->set_pos(event.mouse.x, event.mouse.y);
    }
    /*else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if(event.mouse.button == 1)
        {
            if(start_but->mouse_in(mouse)) return INTER_DONE;
        }
    }*/
    return INTER_CONTINUE;
}
