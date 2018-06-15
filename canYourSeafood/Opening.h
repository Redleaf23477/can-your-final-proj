#ifndef OPENING_H
#define OPENING_H

#include "Interface.h"
#include "Object.h"
#include "Button.h"

class Opening : public Interface
{
protected:
    enum Stat
    {
        OP_DONE,
        OP_CONTINUE
    };

    Object *mouse;
    int stat;
    ButtonRD *start_but;

    int process();

public:
    Opening();
    ~Opening();
    bool run();
};

#endif // OPENING_H
