#include "mesh.h"
#include <string.h>
#include <QDebug>

Mesh::Mesh(BaseRender* render,Shader*shader,
           Camera*camera,
           Transform *transform)
{
    mAccessorys[RENDER_ACCESSORY] = render;
    mAccessorys[SHADER_ACCESSORY] = shader;
    mAccessorys[CAMERA_ACCESSORY] = camera;
    mAccessorys[TRANSFORM_ACCESSORY] = transform;
}

void Mesh::setProjectionMatrix(const GLsizei& width,const GLsizei& height){
    glViewport(0,0,width,height);
    mRatio = (float)width/(float)height;
    Camera*mCamera = (Camera*) mAccessorys[CAMERA_ACCESSORY];
    if(mCamera){

        mCamera->setProjection(60.0f,mRatio,3.0,7.0f);
    }
}
void Mesh::onSurfaceChanaged(const GLsizei& width,const GLsizei& height){
    setProjectionMatrix(width,height);
    BaseRender* mRender = (BaseRender*)mAccessorys[RENDER_ACCESSORY];
    if(mRender){
        mRender->onSurfaceChanaged(width,height);
    }
}


void Mesh::update(){
    BaseRender* mRender = (BaseRender*)mAccessorys[RENDER_ACCESSORY];
    Shader* mShader = (Shader*)mAccessorys[SHADER_ACCESSORY];
    if(mRender && mShader){
        glClear(GL_COLOR_BUFFER_BIT);
        mShader->bindShader();
        Camera*mCamera = (Camera*) mAccessorys[CAMERA_ACCESSORY];
        Transform*mTransform = (Transform*)mAccessorys[TRANSFORM_ACCESSORY];
        if(mTransform && mCamera){
            mShader->update(*mTransform,*mCamera);
        }
        mRender->onRender();
        glFlush();
    }
}
Mesh::~Mesh(){
    qDebug()<<"~Mesh()";
}
