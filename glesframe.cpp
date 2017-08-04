#include "glesframe.h"
#include "comshaderprover.h"
#include <QDebug>
using namespace std;

GLESFrame::GLESFrame()
{
    mShader = NULL;
}
int GLESFrame::frameInit(){
    int ret = -1;
    if(mShader){
        return 0;
    }
    ShaderInfo* mShaderInfo = onLoadShaderInfo();
    if(!mShader){
        mShader = new Shader;
    }
    COMShaderProver* prover =NULL;
    if(!mShaderInfo){
        prover = new COMShaderProver();
        mShaderInfo = prover->getShaderInfo();
    }
    mShaderMap = mShader->shaderInit(mShaderInfo);
    if(mShader == NULL){
        return  ret;
    }
    delete prover;
    return onFrameInit();
}
GLESFrame::~GLESFrame(){
    for(ChildList::iterator it  = childs.begin(); it != childs.end(); )
    {
         FrameItem* item  =   *it;
         it = childs.erase(it);
         delete item;
    }
    delete mShader;

}
void GLESFrame::onRender(int width, int height){
    mShader->bindShader();
    renderSelf(width,height);
    ChildList::iterator itr = childs.begin();
    for ( ;itr != childs.end() ; )
    {
        FrameItem* item  =   *itr;
        item->onRender(width,height,onGetPVMat());
        ++itr;
    }

    mShader->unbindShader();
    glutSwapBuffers();
}
void GLESFrame::addChild(FrameItem* item){
    if(item)
        childs.push_back(item);
}
void GLESFrame::onMouseMove(int absx, int absy, int  absz){
    ChildList::iterator itr = childs.begin();
    for ( ;itr != childs.end() ; )
    {
        FrameItem* item  =   *itr;
        item->onMouseMove(absx,absy,absz);
        ++itr;
    }

}

void GLESFrame::onMousePress(int absx, int absy, MouseButton id){
    ChildList::iterator itr = childs.begin();
    for ( ;itr != childs.end() ; )
    {
        FrameItem* item  =   *itr;
        item->onMousePress(absx,absy,id);
        ++itr;
    }
}
/**
*   鼠标双击
*/
void GLESFrame::onMouseDbPress(int absx, int absy, MouseButton id){
    ChildList::iterator itr = childs.begin();
    for ( ;itr != childs.end() ; )
    {
        FrameItem* item  =   *itr;
        item->onMouseDbPress(absx,absy,id);
        ++itr;
    }
}
/**
*   鼠标释放
*/
void GLESFrame::onMouseRelease(int absx, int absy, MouseButton id){
    ChildList::iterator itr = childs.begin();
    for ( ;itr != childs.end() ; )
    {
        FrameItem* item  =   *itr;
        item->onMouseRelease(absx,absy,id);
        ++itr;
    }
}
/**
*   键盘按下
*/
void GLESFrame::onKeyPress(KeyCode key, int text){
    ChildList::iterator itr = childs.begin();
    for ( ;itr != childs.end() ; )
    {
        FrameItem* item  =   *itr;
        item->onKeyPress(key,text);
        ++itr;
    }
}
/**
*   键盘抬起
*/
void GLESFrame::onKeyRelease(KeyCode key){
    ChildList::iterator itr = childs.begin();
    for ( ;itr != childs.end() ; )
    {
        FrameItem* item  =   *itr;
        item->onKeyRelease(key);
        ++itr;
    }
}
/**
*   输入
*/
void GLESFrame::onChar(int ch){
    ChildList::iterator itr = childs.begin();
    for ( ;itr != childs.end() ; )
    {
        FrameItem* item  =   *itr;
        item->onChar(ch);
        ++itr;
    }
}
