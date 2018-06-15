#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "global.h"
#include "Interface.h"

class gameControl
{
private:

    enum Stat
    {
        STAT_INIT,
        STAT_OPENING,
        STAT_NAMING,
        STAT_GAMING,
        STAT_ENDING,
        STAT_EXIT
    };

    int stat;
    Interface *game_scene;

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
