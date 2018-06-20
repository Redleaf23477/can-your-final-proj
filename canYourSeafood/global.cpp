#include "global.h"

ALLEGRO_SAMPLE_INSTANCE* load_bgm(const char *filename, const ALLEGRO_PLAYMODE mode)
{
    ALLEGRO_SAMPLE *sample = al_load_sample(filename);
    ALLEGRO_SAMPLE_INSTANCE *bgm = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(bgm, mode);
    al_attach_sample_instance_to_mixer(bgm, al_get_default_mixer());
    return bgm;
}

ALLEGRO_BITMAP* load_bitmap_at_size(const char *filename, int w, int h)
{
    ALLEGRO_BITMAP *resized_bmp, *loaded_bmp, *prev_target;

    resized_bmp = al_create_bitmap(w, h);
    if (!resized_bmp) return NULL;

    loaded_bmp = al_load_bitmap(filename);
    if (!loaded_bmp)
    {
        al_destroy_bitmap(resized_bmp);
        return NULL;
    }

    prev_target = al_get_target_bitmap();
    al_set_target_bitmap(resized_bmp);

    al_draw_scaled_bitmap(loaded_bmp,
                          0, 0,
                          al_get_bitmap_width(loaded_bmp),
                          al_get_bitmap_height(loaded_bmp),
                          0, 0,
                          w, h, 0 );

    al_set_target_bitmap(prev_target);
    al_destroy_bitmap(loaded_bmp);

    return resized_bmp;
}
