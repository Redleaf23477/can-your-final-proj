#ifndef ENDING_H
#define ENDING_H

#include "Interface.h"
#include "EndingObj.h"
#include "Button.h"
#include "textbox.h"

#define numOfObj 10
#define numOfFishMeat 5

class Ending : public Interface
{
protected:
    Object *mouse;
    Object *light_area;
    ButtonRD *start_but;
    vector<EndingObj*> vis_obj_ending;
    vector<Textbox*> txtboxes;

    ALLEGRO_SAMPLE_INSTANCE* ED = NULL;
    ALLEGRO_SAMPLE_INSTANCE* ED2 = NULL;
    ALLEGRO_SAMPLE_INSTANCE* machine_sound = NULL;
    ALLEGRO_SAMPLE* blood_sound[2] = {NULL};
    ALLEGRO_SAMPLE* screaming = NULL;
    ALLEGRO_SAMPLE* dead = NULL;
    ALLEGRO_SAMPLE* lightUP_sound = NULL;
    ALLEGRO_SAMPLE* ai_chi_wei = NULL;
    ALLEGRO_SAMPLE* play_light = NULL;
    ALLEGRO_BITMAP* img_fish_meat[5];
    ALLEGRO_BITMAP* machine_img[3];
    ALLEGRO_BITMAP* blood[4];
    int blood_mode = 0;
    int blood_count = 0;
    int blood_cd = 40;
    EndingObj* fish;
    bool fish_paused = false;
    int fish_pause_counter = 0;
    EndingObj* bike;
    EndingObj* machine;
    EndingObj* fish_meat[5];
    EndingObj* light;
    EndingObj* can;
    Textbox* list_title[10];
    Textbox* list_name[10];
    Textbox* txtbox_can = NULL;
    int v_list = 0;
    bool passing = false;
    int passing_counter = 0;
    bool dead_played = false;
    int red_filter_cd = 5;
    int red_filter_last = 5;
    bool red_filter = false;
    bool draw_slogan1 = false;
    bool draw_slogan2 = false;
    bool draw_but = false;
    bool play_ED2 = false;
    bool play_light_effect = false;
    bool play_se = false;

    int machine_cd = 3;
    int machine_frame_count = 0;

    void draw();
    int process();
    void update();
    void set_StaffList();

public:
    Ending(ALLEGRO_DISPLAY*);
    void set_txtbox_can(Textbox* p){ txtbox_can = p; }
    ~Ending();
    int run();
};

#endif // ENDING_H

