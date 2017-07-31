#ifndef GLESFRAME_H
#define GLESFRAME_H
#include "frameitem.h"
#include "absglframe.h"
#include "shader.h"
#include <vector>

class GLESFrame : public AbsGLFrame
{
public:
    GLESFrame();
    int frameInit();
    virtual ~GLESFrame();
    virtual void onRender(int width, int height,void*usrData = NULL);
    virtual void onMouseMove(int absx, int absy, int  absz);

    virtual void onMousePress(int absx, int absy, MouseButton id);
    /**
    *   鼠标双击
    */
    virtual void onMouseDbPress(int absx, int absy, MouseButton id);
    /**
    *   鼠标释放
    */
    virtual void onMouseRelease(int absx, int absy, MouseButton id);
    /**
    *   键盘按下
    */
    virtual void onKeyPress(KeyCode key, int text);
    /**
    *   键盘抬起
    */
    virtual void onKeyRelease(KeyCode key);
    /**
    *   输入
    */
    virtual void onChar(int ch);

protected:
    inline Shader* getShader(){
        return mShader;
    }
    virtual ShaderInfo* onLoadShaderInfo(){return NULL;}
    virtual void renderSelf(int /*width*/, int /*height*/,void*){}
private :
      Shader *mShader;
      typedef std::vector<FrameItem*>   ChildList;
      ChildList  childs;

};

#endif // GLESFRAME_H
