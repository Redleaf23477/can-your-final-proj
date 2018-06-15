#ifndef OPENING_H
#define OPENING_H

#include "Interface.h"

class Opening : public Interface
{
protected:
    void init();
    void process();
    void destroy();

public:
    void run();
};

#endif // OPENING_H
