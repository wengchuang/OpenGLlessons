#ifndef IGLESFRAMEGENERATOR_H
#define IGLESFRAMEGENERATOR_H
#include "glesframe.h"

class IGLESFrameGenerator
{
public:
    virtual GLESFrame* generateGLESFrame() = 0;
};

#endif // IGLESFRAMEGENERATOR_H
