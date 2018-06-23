#ifndef GLOBAL_H
#define GLOBAL_H

// everything in c++ library
#include <bits/stdc++.h>
using namespace std;

// allegro library
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

// my macros
#define pw2(x) ((x)*(x))
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define dbg cout<<"file="<<__FILENAME__<<", line="<<__LINE__<<", func="<<__func__<<endl

// constants
#define WIN_W 800
#define WIN_H 600
#define FPS 60.0
#define PI 3.1415926


// game status
enum Stat
{
    STAT_INIT,
    STAT_OPENING,
    STAT_NAMING,
    STAT_GAMING,
    STAT_ENDING,
    STAT_EXIT,

    INTER_DONE,
    INTER_CONTINUE,
    INTER_EXIT
};

// load ALLEGRO stuffs
/*
    ALLEGRO_PLAYMODE_ONCE
    ALLEGRO_PLAYMODE_LOOP
*/
ALLEGRO_SAMPLE_INSTANCE* load_bgm(const char *filename, const ALLEGRO_PLAYMODE);
ALLEGRO_BITMAP* load_bitmap_at_size(const char *filename, int w, int h);

double angle_radius(double degree);

#endif // GLOBAL_H
