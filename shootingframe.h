#ifndef SHOOTINGFRAME_H
#define SHOOTINGFRAME_H
#include "iglesframegenerator.h"
#include "textureresource.h"
#include "timer.h"

class ShootingFrame : public GLESFrame
{
    friend class ShootingFrameGenerator;
public:
    ~ShootingFrame();
protected:
    ShootingFrame(){
        mShaderInfo= NULL;
                   }
protected:
    ShaderInfo* onLoadShaderInfo();
    void renderSelf(const Vision::FrameEvent& _event);
    int onFrameInit();
    glm::mat4& onGetPVMat(){
        return mPVMat;
    }
private:
    Texture2dId    texture;
    GLint          pvmMatRef;
    GLint          uvUniformRef;
    ShaderInfo*    mShaderInfo;
    glm::mat4      mPVMat;
};
class ShootingFrameGenerator:public IGLESFrameGenerator{
public:
    GLESFrame* generateGLESFrame(){
        return new ShootingFrame;
    }
};
#endif // SHOOTINGFRAME_H
