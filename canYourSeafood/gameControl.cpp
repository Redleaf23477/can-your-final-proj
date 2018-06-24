#include "gameControl.h"

gameControl::gameControl()
{
    ctrl_stat = STAT_INIT;
    game_scene = NULL;
    display = NULL;
    ocean = NULL;
    srand(time(NULL));
}

gameControl::~gameControl()
{
}

void gameControl::run()
{
    allegro_init();
    game_init();
    while(ctrl_stat != STAT_EXIT)
    {
        switch(ctrl_stat)
        {
        case STAT_OPENING:
            game_run();
            break;
        case STAT_NAMING:
            game_run();
            break;
        case STAT_GAMING:
            game_run();
            break;
        case STAT_ENDING:
            game_run();
            break;
        default:
            dbg << "!! Unknown stat=" << ctrl_stat << " !!" << endl;
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

    dbg << "Allegro Initializing" << endl;

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font_lib.load();       // load my fucking font library

    al_reserve_samples(5); // at most 5 music at a time
}

void gameControl::game_init()
{
    display = al_create_display(WIN_W, WIN_H);
    game_scene = new Opening(display);
    ctrl_stat = STAT_OPENING;
    ocean = load_bgm("../assets/music/ocean.ogg", ALLEGRO_PLAYMODE_LOOP);
    al_play_sample_instance(ocean);
}

void gameControl::game_run()
{
    int res = game_scene->run();
    if(res == INTER_DONE)
    {
        Interface *bye = game_scene; delete bye; game_scene = NULL;
        dbg << "old Interface killed" << endl;
        switch(ctrl_stat)
        {
        case STAT_OPENING: ctrl_stat = STAT_NAMING; game_scene = new Naming(display); break;
        case STAT_NAMING:  ctrl_stat = STAT_GAMING; game_scene = new Gaming(display); break;
        case STAT_GAMING:  ctrl_stat = STAT_ENDING; game_scene = new Ending(display); al_stop_sample_instance(ocean); break;
        case STAT_ENDING:  ctrl_stat = STAT_EXIT; game_scene = NULL; break;
        default:
            dbg << "!! Unknown stat=" << ctrl_stat << " !!" << endl;
            assert(false);
            break;
        }
    }
    else if(res == INTER_EXIT)
    {
        ctrl_stat = STAT_EXIT;
    }
}

void gameControl::game_destroy()
{
    al_destroy_display(display);
    font_lib.destroy();
    al_stop_sample_instance( ocean );
    if(ocean)
        al_destroy_sample_instance( ocean );
}
