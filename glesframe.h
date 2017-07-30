#ifndef GLESFRAME_H
#define GLESFRAME_H
#include "iglinput.h"

class GLESFrame : public IGLInput
{
public:
    GLESFrame();
    virtual ~GLESFrame(){}
    virtual void onRender(){}
    virtual void    onMouseMove(int absx, int absy, int absz){

    }

    virtual void    onMousePress(int absx, int absy, MouseButton id){

    }
    /**
    *   鼠标双击
    */
    virtual void    onMouseDbPress(int absx, int absy, MouseButton id){

    }
    /**
    *   鼠标释放
    */
    virtual void    onMouseRelease(int absx, int absy, MouseButton id){

    }
    /**
    *   键盘按下
    */
    virtual void    onKeyPress(KeyCode key, int text){

    }
    /**
    *   键盘抬起
    */
    virtual void    onKeyRelease(KeyCode key){

    }
    /**
    *   输入
    */
    virtual void    onChar(int ch){

    }
};

#endif // GLESFRAME_H
