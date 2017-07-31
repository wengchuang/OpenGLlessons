#ifndef GLESFRAMEGENERATOR_H
#define GLESFRAMEGENERATOR_H
#include "iglesframegenerator.h"

class GLESFrameGenerator:public IGLESFrameGenerator
{
public:
    GLESFrame* generateGLESFrame();
};

#endif // GLESFRAMEGENERATOR_H
