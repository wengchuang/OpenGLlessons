#include "shootingframe.h"
#include "shader.h"
#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <QDebug>
#include "textureresource.h"
#include "absgles2app.h"

int ShootingFrame::onFrameInit(){
    int ret = 0;
    texture = AbsGLES2App::getGLESAppContext()->getTextureResource()->getTexture("./data/image/main.tex");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return ret;
}
void ShootingFrame::renderSelf(int width ,int height ,void*){
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0,0,width,height);

    static Shader* mShader = NULL;

    if(!mShader){
        mShader = getShader();
    }

    mShader->bindShader();
    {
        glm::mat4 Projection = glm::ortho(0.0f,(float)width,(float)height,0.0f);

        float   x   =   0;
        float   y   =   0;
        float   w   =   (float)width;
        float   h   =   (float)height;
        static  float   vv  =   0;
        GLfloat vert[]   =
        {
            x,      y,     0,   0, vv,
           (x+w),   y,     0,   1, vv,
            x   ,   (y+h), 0,   0, 1+vv,
           (x+w),   (y+h), 0,   1, 1+vv
        };
        vv  +=  0.001f;
        glActiveTexture(GL_TEXTURE0 + 0);
        glBindTexture(GL_TEXTURE_2D,texture._texture);
        GLint ref = getShaderMap()->getUniformRef("pvmMat");
        glUniformMatrix4fv(ref,1,GL_FALSE,&Projection[0][0]);

        glUniform1i(getShaderMap()->getUniformRef("_uv"), 0);
        glVertexAttribPointer(0,  3,  GL_FLOAT,   false,  5*sizeof(GLfloat),vert);
        glVertexAttribPointer(1,  2,  GL_FLOAT,   false, 5*sizeof(GLfloat),
                              &vert[3]);

        glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    }
   mShader->unbindShader();
}


ShaderInfo* ShootingFrame::onLoadShaderInfo(){
    if(!mShaderInfo){
        mShaderInfo = new ShaderInfo;
        mShaderInfo->setFsFileName("./shootingframe.fsh");
        mShaderInfo->setVsFileName("./shootingframe.vsh");
        mShaderInfo->addVertex("position");
        mShaderInfo->addVertex("_uv");
        mShaderInfo->addUniform("pvmMat");
        mShaderInfo->addUniform("_texture");
    }
    return mShaderInfo;
}
