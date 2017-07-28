#ifndef BASERENDER_H
#define BASERENDER_H
#include <GL/glew.h>
#include <QtGlobal>
#include <glm/glm.hpp>
#include <QList>
#include "shader.h"
#include "meshaccessory.h"

class IRenderObserver{
    virtual glm::mat4 observerViewMatrix() = 0;
    virtual glm::mat4 observerModelMatrix() = 0;
    virtual ~IRenderControler(){}
};

class BaseRender:public MeshAccessory
{
public:
    BaseRender(const IRenderObserver* = NULL);
    int renderInit();
    void update(const IRenderObserver* = NULL);
    //这是一个不好的实现，应该注册为一个监听器
    virtual void onSurfaceChanaged(const GLsizei& width,const GLsizei& height){
        Q_UNUSED(width);
        Q_UNUSED(height);
    }
    inline void setObserver(const IRenderObserver* observer){
        this->mIobserver = observer;
    }
    virtual ~BaseRender();
protected:
    enum VERTBUFFERTYPE{
        POSITION_VB,
        NUM_BUFFERS
    };
    virtual QList<ShaderInfo*> onLoadShaderInfo()= 0;
    virtual void onCompileShaderProgramSuccessful(Shader* shader) = 0;
    virtual void onUpdate(IRenderObserver* tmpObserver) = 0;
    inline const GLuint& getVertArrObj(){
        if(mVertArrObj == 0){
            glGenVertexArrays(1,&mVertArrObj);
        }
        return mVertArrObj;
    }
    inline const GLuint& getVertArrBuffer(VERTBUFFERTYPE type){
        if(mVertArrBuffers[0] == 0){
            glGenBuffers(NUM_BUFFERS,mVertArrBuffers);
        }
        return mVertArrBuffers[type];
    }
private:
    //这里封装函数 为了屏蔽刷新的差异
    void commitUpdate();
private:
    Shader* mShader;
    IRenderObserver* mIobserver;
    GLuint mVertArrObj;
    GLuint mVertArrBuffers[NUM_BUFFERS];
};

#endif // BASERENDER_H
