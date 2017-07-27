#include "mesh.h"
#include <string.h>
#include <QDebug>

Mesh::Mesh(BaseRender* render):mRender(render)
{
    glClearColor(0.0f,.0f,.0f,1.0f);
    mTransform= new Transform();
    shader = new Shader;
    camera = new Camera;
}
int Mesh::initData(){
    int ret = 0;
    if(shader->shaderInit()<0){
        qDebug()<<"initData() error!";
        return -1;
    }
    return ret;
}
void Mesh::setProjectionMatrix(const GLsizei& width,const GLsizei& height){
    glViewport(0,0,width,height);
    mRatio = (float)width/(float)height;
    camera->setProjection(60.0f,mRatio,3.0,7.0f);
}
void Mesh::onSurfaceChanaged(const GLsizei& width,const GLsizei& height){
    setProjectionMatrix(width,height);
    if(mRender){
        mRender->onSurfaceChanaged(width,height);
    }
}


void Mesh::onDraw(){
    if(mRender){
        glClear(GL_COLOR_BUFFER_BIT);
        shader->bindShader();
        shader->update(*mTransform,*camera);
        mRender->onRender();
        glFlush();
    }
}
Mesh::~Mesh(){
    delete shader;
    delete camera;
    delete mTransform;
    qDebug()<<"~Mesh()";
}
