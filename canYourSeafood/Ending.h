#ifndef ENDING_H
#define ENDING_H

#include "Interface.h"
#include "EndingObj.h"
#include "Button.h"

#define numOfObj 10
#define numOfFishMeat 5

class Ending : public Interface
{
protected:
    Object *mouse;
    int stat;
    ButtonRD *start_but;
    vector<EndingObj*> vis_obj_ending;

    ALLEGRO_SAMPLE_INSTANCE* ED = NULL;
    ALLEGRO_SAMPLE_INSTANCE* machine_sound = NULL;
    ALLEGRO_SAMPLE* blood_sound[2] = {NULL};
    ALLEGRO_SAMPLE* screaming = NULL;
    ALLEGRO_SAMPLE* trumpet = NULL;
    ALLEGRO_SAMPLE* lightUP_sound = NULL;
    ALLEGRO_SAMPLE* ai_chi_wei = NULL;
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
    bool passing = false;
    int passing_counter = 0;

    int machine_cd = 3;
    int machine_frame_count = 0;

    void draw();
    int process();
    void update();

public:
    Ending(ALLEGRO_DISPLAY*);
    ~Ending();
    int run();
};

#endif // ENDING_H

