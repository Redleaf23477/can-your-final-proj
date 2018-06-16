#ifndef NAMING_H
#define NAMING_H

#include "Interface.h"
#include "Button.h"

class Naming : public Interface
{
protected:
    Object *mouse;
    int stat;
    ButtonRD *start_but;
//    TextBox *txt;

    int process();

public:
    Naming();
    ~Naming();
    int run();
};

#endif // NAMING_H
