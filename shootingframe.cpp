#include "shootingframe.h"
#include "shader.h"
#ifdef UBUNTU_WITH_GL
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#ifdef WIN32_WITH_OPENGL_ES2
typedef int GLint;
typedef unsigned int GLuint;
#include <gles2/gl2.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <QDebug>
#include "textureresource.h"
#include "absgles2app.h"
#include "player.h"
#include "visionmath.hpp"
#include "clockbg.h"

int ShootingFrame::onFrameInit(){
    int ret = 0;
#ifdef UBUNTU_WITH_GL
    glEnable(GL_BLEND|GL_DOUBLE|GL_ALPHA_TEST);
#endif
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   pvmMatRef = getShaderMap()->getUniformRef("pvmMat");
   uvUniformRef = getShaderMap()->getUniformRef("_texture");

   texture = AbsGLES2App::getGLESAppContext()->getTextureResource()->getTexture("./data/image/main.tex");
#if 1
   player* p;


    p = new player(getShaderMap());
    glm::vec3 pos = glm::vec3(100,100,0);
    p->setPos(pos);
    addChild( p);

    p = new player(getShaderMap());
    pos = glm::vec3(100,200,0);
    p->setPos(pos);
    addChild( p);

    p = new player(getShaderMap());
    pos = glm::vec3(200,300,0);
    p->setPos(pos);
    addChild( p);
#endif
#if 1
    ClockBg* bg = new ClockBg(getShaderMap());
    addChild( bg);
#endif
    return ret;
}

void ShootingFrame::renderSelf(const Vision::FrameEvent& _event){
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

   // qDebug()<<"mWidth:"<<mWidth<<"      "<<"mHeight:"<<mHeight;
    glViewport(0,0,mWidth,mHeight);

    mPVMat = glm::ortho(0.0f,(float)mWidth,(float)mHeight,0.0f);
    float   x   =   0;
    float   y   =   0;
    float   w   =   (float)mWidth;
    float   h   =   (float)mHeight;
    static  float   vv  =   0;

    vv  +=  0.001f;

    float vert[]   =
    {
        x,      y,     0.0f,    1.0f,  0, vv,
       (x+w),   0,     0.0f,    1.0f,  1, vv,
        0   ,   (y+h), 0.0f,    1.0f,  0, 1+vv,
       (x+w),   (y+h), 0.0f,    1.0f,  1, 1+vv
    };


    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D,texture._texture);
    glUniformMatrix4fv(pvmMatRef,1,GL_FALSE,&mPVMat[0][0]);
    glUniform1i(uvUniformRef, 0);
    glVertexAttribPointer(getShaderMap()->getVertexRef("position"),  4,  GL_FLOAT,   false,  6*sizeof(float),vert);
    glVertexAttribPointer(getShaderMap()->getVertexRef("_uv"),  2,  GL_FLOAT,   false, 6*sizeof(float),&vert[4]);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

}


ShaderInfo* ShootingFrame::onLoadShaderInfo(){
    if(!mShaderInfo){
        mShaderInfo = new ShaderInfo;
        #ifdef WIN32_WITH_OPENGL_ES2
        mShaderInfo->setFsFileName("./shootingframe_win.fsh");
        mShaderInfo->setVsFileName("./shootingframe_win.vsh");
        #endif
        #ifdef UBUNTU_WITH_GL
        mShaderInfo->setFsFileName("./shootingframe_ubuntu.fsh");
        mShaderInfo->setVsFileName("./shootingframe_ubuntu.vsh");
        #endif
        mShaderInfo->addVertex("position");
        mShaderInfo->addVertex("_uv");
        mShaderInfo->addUniform("pvmMat");
        mShaderInfo->addUniform("_texture");

    }
    return mShaderInfo;
}
ShootingFrame::~ShootingFrame(){
    qDebug()<<"ShootingFrame::~ShootingFrame() begin ...";
    delete mShaderInfo;
    qDebug()<<"ShootingFrame::~ShootingFrame() end ...";
}
