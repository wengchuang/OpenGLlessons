#ifndef BASERENDER_H
#define BASERENDER_H
#include <GL/glew.h>
#include <QtGlobal>
class BaseRender
{
public:
    BaseRender();
    virtual void onRender()=0;
    virtual void onSurfaceChanaged(const GLsizei& width,const GLsizei& height){
        Q_UNUSED(width);
        Q_UNUSED(height);
    }
    virtual ~BaseRender();
protected:
    enum VERTBUFFERTYPE{
        POSITION_VB,
        NUM_BUFFERS
    };
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
    GLuint mVertArrObj;
    GLuint mVertArrBuffers[NUM_BUFFERS];
};

#endif // BASERENDER_H
