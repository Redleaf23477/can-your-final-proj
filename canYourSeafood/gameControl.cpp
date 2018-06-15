#include "gameControl.h"
#include "global.h"
#include "Interface.h"
#include "Opening.h"

gameControl::gameControl()
{
    stat = STAT_INIT;
    game_scene = NULL;
}

gameControl::~gameControl()
{
    delete game_scene;
}

void gameControl::run()
{
    while(stat != STAT_EXIT)
    {
        switch(stat)
        {
        case STAT_INIT:
            allegro_init();
            game_init();
            break;
        case STAT_OPENING:
            game_run();
            break;
        case STAT_NAMING:
            break;
        case STAT_GAMING:
            break;
        case STAT_ENDING:
            break;
        default:
            break;
        }
    }
    game_destroy();
}

void gameControl::allegro_init()
{
    if(!al_init())
    {
        cout << "al_init failed" << endl;
        assert(false);
    }

    cout << "Game init" << endl;

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
}

void gameControl::game_init()
{
    srand(time(NULL));
    game_scene = new Opening;

    stat = STAT_OPENING;
}

void gameControl::game_run()
{
    int res = game_scene->run();
    if(res == 0) stat = STAT_EXIT;
}

void gameControl::game_destroy()
{
}
