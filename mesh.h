#ifndef MESH_H
#define MESH_H
#include <GL/glew.h>
#include <GL/glut.h>
#include <QDebug>
#include "shader.h"
#include "camera.h"
#include "baserender.h"

class Mesh
{
public:
    Mesh(BaseRender* render = NULL);
    void onDraw();
    int initData();
    void onSurfaceChanaged(const GLsizei& width,const GLsizei& height);
    inline void setRender(BaseRender* render){
        this->mRender = render;
    }
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
    inline float getRatio(){return mRatio;}
private:
    void setProjectionMatrix(const GLsizei& width,const GLsizei& height);
private:
    float  mRatio;
    Shader* shader;
    Camera* camera;
    Transform *mTransform;
    BaseRender* mRender;

};

#endif // MESH_H
