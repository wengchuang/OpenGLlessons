#include "baserender.h"
#ifdef UBUNTU_WITH_GL
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#ifdef WIN_WITH_OPENGL_ES2
typedef int GLint;
typedef unsigned int GLuint;
#include <gles2/gl2.h>
#endif
#include <QDebug>
#include "comshaderprover.h"
BaseRender::BaseRender(IRenderObserver* observer)
{
    mIobserver = observer;
    mShader = NULL;
    mVertArrObj = 0;
    for(int i=0;i<NUM_BUFFERS;i++){
        mVertArrBuffers[i] = 0;
    }
}
int BaseRender::init(){
    int ret = -1;
    qDebug()<<"init render begin...";
    ShaderInfo* infos = onLoadShaderInfo();
    mShader = new Shader;
    if(!infos){
        COMShaderProver* prover = new COMShaderProver();
        infos = prover->getShaderInfo();
    }
    mShaderMap = mShader->shaderInit(infos);
    if(mShader != NULL){
       ret = 0;
    }
    qDebug()<<"init render end...";
    return ret;
}
void BaseRender::update(IRenderObserver* observer){
    IRenderObserver* tmpObserver = observer;
    if(mShader){
        if(tmpObserver == NULL){
           tmpObserver = mIobserver;
        }else{

        }
        if(tmpObserver != NULL){
            mShader->bindShader();
            onUpdate(mShader,tmpObserver->observerViewMatrix(),
                 tmpObserver->observerModelMatrix());
             glFlush();
           // mShader->unbindShader();
        }
    }

}

BaseRender::~BaseRender(){
    if(mVertArrBuffers[0] > 0){
#ifdef UBUNTU_WITH_GL

         glDeleteBuffers(NUM_BUFFERS,mVertArrBuffers);
#endif
    }

    if(mVertArrObj > 0){
    #ifdef UBUNTU_WITH_GL

        glDeleteVertexArrays(1,&mVertArrObj);
#endif
    }
}
