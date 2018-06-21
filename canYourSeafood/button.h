#ifndef BUTTON_H
#define BUTTON_H

#include "global.h"
#include "Object.h"
#include "fonts.h"

// round button
class ButtonRD:public Object
{
private:
    bool hidden;
    int button_id;
    ALLEGRO_BITMAP *pic;
    ALLEGRO_FONT *font;
    string str;

public:
    ButtonRD(int, int, int, int, const char*);
    ButtonRD(int, int, int);
    ~ButtonRD();
    int click();
    void toggleHidden();
    void set_str(string);
    void draw() override;
};

#endif // OBJECT_H
