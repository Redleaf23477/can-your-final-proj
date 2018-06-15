#include "gameControl.h"
#include "global.h"
#include "Interface.h"
#include "Opening.h"

gameControl::gameControl()
{
    stat = STAT_INIT;
    game_scene = NULL;
    display = NULL;
}

gameControl::~gameControl()
{
    delete game_scene;
    delete display;
}

void gameControl::run()
{
    allegro_init();
    game_init();
    game_run();
    game_destroy();
}

void gameControl::allegro_init()
{
    if(!al_init())
    {
        cout << "al_init failed" << endl;
        assert(false);
    }

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
    display = al_create_display(WIN_W, WIN_H);
}

void gameControl::game_run()
{
    game_scene->run();
    /*
    while(stat != STAT_EXIT)
    {
        switch(stat)
        {
        case STAT_INIT:
            break;
        case STAT_OPENING:
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
    */
}

void gameControl::game_destroy()
{
}
