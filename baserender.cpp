#include "baserender.h"


BaseRender::BaseRender(const IRenderObserver observer)
{
    mIobserver = observer;
    mShader = NULL;
    mVertArrObj = 0;
    for(int i=0;i<NUM_BUFFERS;i++){
        mVertArrBuffers[i] = 0;
    }
}
int BaseRender::renderInit(){
    int ret = -1;
    QList<ShaderInfo*> infos = onLoadShaderInfo();
    mShader = new Shader;
    ret = mShader->shaderInit(infos);
    if(ret == 0){
        onCompileShaderProgramSuccessful(mShader);
    }
    return ret;
}
void BaseRender::update(const IRenderObserver* observer){
    IRenderObserver* tmpObserver = observer;
    if(mShader){
        if(tmpObserver == NULL){
           tmpObserver = mIobserver;
        }else{

        }
        mShader->bindShader();
        onUpdate(tmpObserver);
        commitUpdate();
    }

}
void BaseRender::commitUpdate(){
     glFulsh();
}
BaseRender::~BaseRender(){
    if(mVertArrBuffers[0] > 0){
         glDeleteBuffers(NUM_BUFFERS,mVertArrBuffers);
    }

    if(mVertArrObj > 0){
        glDeleteVertexArrays(1,&mVertArrObj);
    }
}
