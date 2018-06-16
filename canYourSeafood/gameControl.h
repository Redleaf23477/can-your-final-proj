#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "global.h"
#include "Interface.h"
#include "Opening.h"
#include "Naming.h"

class gameControl
{
private:
    int stat;
    Interface *game_scene;

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
