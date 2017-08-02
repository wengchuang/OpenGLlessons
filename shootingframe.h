#ifndef SHOOTINGFRAME_H
#define SHOOTINGFRAME_H
#include "iglesframegenerator.h"
#include "textureresource.h"
#include "timer.h"

class ShootingFrame : public GLESFrame
{
    friend class ShootingFrameGenerator;
public:
    ~ShootingFrame(){
        delete mShaderInfo;
        delete mTimer;
    }
protected:
    ShootingFrame(){mShaderInfo= NULL;
                    mTimer = NULL;
                   }
protected:
    ShaderInfo* onLoadShaderInfo();
    void renderSelf(int width, int height,void*usrData);
    int onFrameInit();
private:
    void onRender();
private:
    Texture2dId    texture;
    GLint          pvmMatRef;
    GLint          uvUniformRef;
    ShaderInfo*    mShaderInfo;
    Timer* mTimer;
    float mWidth ;
    float mHeight;
};
class ShootingFrameGenerator:public IGLESFrameGenerator{
public:
    GLESFrame* generateGLESFrame(){
        return new ShootingFrame;
    }
};
#endif // SHOOTINGFRAME_H
