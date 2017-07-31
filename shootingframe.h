#ifndef SHOOTINGFRAME_H
#define SHOOTINGFRAME_H
#include "iglesframegenerator.h"
class ShootingFrame : public GLESFrame
{
    friend class ShootingFrameGenerator;
protected:
    ShootingFrame(){}
protected:

    void renderSelf(int width, int height,void*usrData);

};
class ShootingFrameGenerator:public IGLESFrameGenerator{
public:
    GLESFrame* generateGLESFrame(){
        return new ShootingFrame;
    }
};
#endif // SHOOTINGFRAME_H
