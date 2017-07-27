#ifndef MESH_H
#define MESH_H
#include <GL/glew.h>
#include <GL/glut.h>
#include <QDebug>
#include "shader.h"
#include "camera.h"

class Mesh
{
public:
    Mesh();
    void onDraw();
    int initData();
    void onSurfaceChanaged(const GLsizei& width,const GLsizei& height);
    inline void update(){
        onDraw();
    }
    inline void roteXf(const GLfloat& angle){
        mTransform->setRote(*mTransform->getRote()+glm::vec3(angle,0,0));
    }
    inline void roteYf(const GLfloat& angle){
        mTransform->setRote(*mTransform->getRote()+glm::vec3(0,angle,0));
    }
    inline void roteZf(const GLfloat& angle){
         mTransform->setRote(*mTransform->getRote()+glm::vec3(0,0,angle));
    }

    inline void transXf(const GLfloat& value){
        mTransform->setPos(*mTransform->getPos()+glm::vec3(value,0,0));
    }
    inline void transYf(const GLfloat& value){
        mTransform->setPos(*mTransform->getPos()+glm::vec3(0,value,0));
    }
    inline void transZf(const GLfloat& value){
         mTransform->setPos(*mTransform->getPos()+glm::vec3(0,0,value));;
    }
    inline void scaleXf(const GLfloat& value){
        mTransform->setScale(*mTransform->getScale()*glm::vec3(value,1.0f,1.0f));;
    }
    inline void scaleYf(const GLfloat& value){
        mTransform->setScale(*mTransform->getScale()*glm::vec3(1.0f,value,1.0f));;
    }
    inline void scaleZf(const GLfloat& value){
        mTransform->setScale(*mTransform->getScale()*glm::vec3(1.0f,1.0f,value));;
    }
    virtual ~Mesh();
protected:
    enum VERTBUFFERTYPE{
        POSITION_VB,
        NUM_BUFFERS
    };
protected:
    virtual void onRender()=0;
    virtual int  onInitData(){return 0;}
    virtual void onResize(const GLsizei& width,const GLsizei& height){
        Q_UNUSED(width);
        Q_UNUSED(height);
        return;
    }
    inline float getRatio(){return mRatio;}
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
    void setProjectionMatrix(const GLsizei& width,const GLsizei& height);


private:
    float  mRatio;
    GLuint mVertArrObj;
    GLuint mVertArrBuffers[NUM_BUFFERS];
    Shader* shader;
    Camera* camera;
    Transform *mTransform;


};

#endif // MESH_H
