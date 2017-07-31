#include "baserender.h"
#include <GL/glew.h>
#include <GL/glut.h>
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
    ret = mShader->shaderInit(infos);
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
            commitUpdate();
           // mShader->unbindShader();
        }
    }

}
void BaseRender::commitUpdate(){
     glFlush();
}
BaseRender::~BaseRender(){
    if(mVertArrBuffers[0] > 0){
         glDeleteBuffers(NUM_BUFFERS,mVertArrBuffers);
    }

    if(mVertArrObj > 0){
        glDeleteVertexArrays(1,&mVertArrObj);
    }
}
