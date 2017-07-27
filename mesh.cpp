#include "mesh.h"
#include <string.h>
#include <QDebug>

Mesh::Mesh():mVertArrObj(0)
{
    glClearColor(0.0f,.0f,.0f,1.0f);
    memset(mVertArrBuffers,0,sizeof(mVertArrBuffers));
    mTransform= new Transform();
    shader = new Shader;
    camera = new Camera;
}
int Mesh::initData(){

    if(shader->shaderInit()<0){
        qDebug()<<"initData() error!";
        return -1;
    }
    return onInitData();
}
void Mesh::setProjectionMatrix(const GLsizei& width,const GLsizei& height){
    glViewport(0,0,width,height);
    mRatio = (float)width/(float)height;
    camera->setProjection(60.0f,mRatio,3.0,7.0f);
}
void Mesh::onSurfaceChanaged(const GLsizei& width,const GLsizei& height){
    setProjectionMatrix(width,height);
    onResize(width,height);
}


void Mesh::onDraw(){
    glClear(GL_COLOR_BUFFER_BIT);
    shader->bindShader();
    shader->update(*mTransform,*camera);
    onRender();
    glFlush();
}
Mesh::~Mesh(){
    delete shader;
    delete camera;
    delete mTransform;

    if(mVertArrBuffers[0] > 0){
         glDeleteBuffers(NUM_BUFFERS,mVertArrBuffers);
    }

    if(mVertArrObj > 0){
        glDeleteVertexArrays(1,&mVertArrObj);
    }
    qDebug()<<"~Mesh()";
}
