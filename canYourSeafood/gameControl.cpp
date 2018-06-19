#include "gameControl.h"


gameControl::gameControl()
{
    stat = STAT_INIT;
    game_scene = NULL;
    display = NULL;
    srand(time(NULL));
}

gameControl::~gameControl()
{
}

void gameControl::run()
{
    allegro_init();
    while(stat != STAT_EXIT)
    {
        switch(stat)
        {
        case STAT_INIT:
            cout << "stat=init" << endl;
            game_init();
            break;
        case STAT_OPENING:
            cout << "stat=opening" << endl;
            game_run();
            break;
        case STAT_NAMING:
            cout << "stat=naming" << endl;
            game_run();
            break;
        case STAT_GAMING:
            cout << "stat=gaming" << endl;
            game_run();
            break;
        case STAT_ENDING:
            cout << "stat=ending" << endl;
            game_run();
            break;
        default:
            cout << "!! Unknown stat=" << stat << " !!" << endl;
            assert(false);
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
    display = al_create_display(WIN_W, WIN_H);
    game_scene = new Opening(display);
    stat = STAT_OPENING;
}

void gameControl::game_run()
{
    int res = game_scene->run();
    if(res == INTER_DONE)
    {
        Interface *bye = game_scene; delete bye; game_scene = NULL;
        dbg << "hi" << endl;
        switch(stat)
        {
        case STAT_OPENING: stat = STAT_NAMING; game_scene = new Naming(display); break;
        case STAT_NAMING:  stat = STAT_EXIT; game_scene = NULL; break;
//        case STAT_NAMING:  stat = STAT_GAMING; game_scene = new Gaming; break;
//        case STAT_GAMING:  stat = STAT_ENDING; game_scene = new Ending; break;
//        case STAT_ENDING:  stat = STAT_EXIT; game_scene = NULL; break;
        default:
            dbg << "!! Unknown stat=" << stat << " !!" << endl;
            assert(false);
            break;
        }
    }
    else if(res == INTER_EXIT)
    {
        stat = STAT_EXIT;
    }
}

void gameControl::game_destroy()
{
    al_destroy_display(display);
}
