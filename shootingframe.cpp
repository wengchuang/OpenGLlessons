#include "shootingframe.h"
#include "shader.h"
#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <QDebug>

void ShootingFrame::renderSelf(int width ,int height ,void*){
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0,0,width,height);

    static Shader* mShader = NULL;

    if(!mShader){
        mShader = getShader();
    }
#if 1
    mShader->bindShader();
    {
        glm::mat4 Projection = glm::ortho(0.0f,(float)width,(float)height,0.0f);
        mShader->setPVMmatrix(Projection);

        GLfloat mVertices[12];
        mVertices[0] = 100.0;
        mVertices[1] = 100.0;
        mVertices[2] = 0.8f;


        mVertices[3] = 200;
        mVertices[4] = 100;
        mVertices[5] = 0.8f;

        mVertices[6] = 100;
        mVertices[7] = 200;
        mVertices[8] = 0.8f;

        mVertices[9]  =  200;
        mVertices[10] =  200;
        mVertices[11] = 0.8f;
        glVertexAttribPointer (0,3,GL_FLOAT, GL_FALSE, 0, mVertices);
        glDrawArrays(GL_TRIANGLE_STRIP,0,4);


    }
   mShader->unbindShader();

#endif


}
