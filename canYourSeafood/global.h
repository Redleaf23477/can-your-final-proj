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

#endif // GLOBAL_H
