#ifndef INTERFACE_H
#define INTERFACE_H

#include "global.h"

class Interface
{
protected:
//    vector<*Object> objs;            // an array that stores every pointer of obj in the interface

    virtual void init() = 0;
    virtual void process() = 0;
    virtual void destroy() = 0;
    virtual void draw();

public:
    Interface();
    virtual ~Interface();
    virtual void run() = 0;
//    Circle mouse;
};



#endif // INTERFACE_H
