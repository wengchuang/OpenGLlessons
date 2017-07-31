#include "shootingframe.h"
#include "shader.h"
#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <QDebug>
ShootingFrame::ShootingFrame(){

}
void ShootingFrame::renderSelf(int width ,int height ,void*){
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0,0,width,height);
    glm::mat4  projection = glm::ortho(0.0f,float(width),float(height),0.0f);

    static Shader* mShader = NULL;

    if(mShader){
        mShader = getShader();
    }
#if 1
    mShader->bindShader();
    {
       // mShader->setPVMmatrix(projection);
    }
    //mShader->unbindShader();
#endif


}
