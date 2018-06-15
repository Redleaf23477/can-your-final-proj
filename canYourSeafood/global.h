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

// game states
enum Stat
{
    STAT_INIT,
    STAT_OPENING,
    STAT_NAMING,
    STAT_GAMING,
    STAT_ENDING,
    STAT_EXIT
};


#endif // GLOBAL_H
