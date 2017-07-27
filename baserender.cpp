#include "baserender.h"

BaseRender::BaseRender()
{
}
BaseRender::~BaseRender(){
    if(mVertArrBuffers[0] > 0){
         glDeleteBuffers(NUM_BUFFERS,mVertArrBuffers);
    }

    if(mVertArrObj > 0){
        glDeleteVertexArrays(1,&mVertArrObj);
    }
}
