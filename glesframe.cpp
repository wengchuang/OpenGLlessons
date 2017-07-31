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
    ShaderInfo* info = onLoadShaderInfo();
    if(!mShader){
        mShader = new Shader;
    }
    if(!info){
        COMShaderProver* prover = new COMShaderProver();
        info = prover->getShaderInfo();
    }
    ret = mShader->shaderInit(info);
    return ret;
}
GLESFrame::~GLESFrame(){
    delete mShader;
}
void GLESFrame::onRender(int width, int height,void*usrData){
    renderSelf(width,height,usrData);
    ChildList::iterator itr = childs.begin();
    for ( ;itr != childs.end() ; )
    {
        FrameItem* item  =   *itr;
        item->onRender(width,height,usrData);
        ++itr;
    }

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
