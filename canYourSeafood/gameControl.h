#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "global.h"
#include "Interface.h"

class gameControl
{
private:
    static const int WIN_W = 800;
    static const int WIN_H = 600;
    int stat;
    Interface *game_scene;
    ALLEGRO_DISPLAY *display;

    void allegro_init();
    void game_init();
    void game_run();
    void game_destroy();

public:
    gameControl();
    ~gameControl();
    void run();
};

#endif // GAMECONTROL_H
