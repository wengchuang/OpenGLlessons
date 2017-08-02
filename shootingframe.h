#ifndef SHOOTINGFRAME_H
#define SHOOTINGFRAME_H
#include "iglesframegenerator.h"
#include "textureresource.h"

class ShootingFrame : public GLESFrame
{
    friend class ShootingFrameGenerator;
public:
    ~ShootingFrame(){
        delete mShaderInfo;
    }
protected:
    ShootingFrame(){mShaderInfo= NULL;}
protected:
    ShaderInfo* onLoadShaderInfo();
    void renderSelf(int width, int height,void*usrData);
    int onFrameInit();
private:
    Texture2dId    texture;
    ShaderInfo*    mShaderInfo;
};
class ShootingFrameGenerator:public IGLESFrameGenerator{
public:
    GLESFrame* generateGLESFrame(){
        return new ShootingFrame;
    }
};
#endif // SHOOTINGFRAME_H
