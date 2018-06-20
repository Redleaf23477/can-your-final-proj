#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "global.h"
#include "Interface.h"
#include "Opening.h"
#include "Naming.h"
#include "Gaming.h"
#include "Ending.h"

class gameControl
{
private:
    int ctrl_stat;
    Interface *game_scene;
    ALLEGRO_DISPLAY *display;

    void allegro_init();
    void game_init();
    void game_run();
    void game_reset();
    void game_destroy();

public:
    gameControl();
    ~gameControl();

    void run();
};

#endif // GAMECONTROL_H
