#ifndef IGLINPUT_H
#define IGLINPUT_H
#include "mousebutton.h"
#include "keycode.h"
class   IGLInput{
    public:
        virtual	~IGLInput(){}
        /**
        *   鼠标移动
        */
        virtual void    onMouseMove(int absx, int absy, int absz)  =   0;
        /**
        *   鼠标按下
        */
        virtual void    onMousePress(int absx, int absy, MouseButton id)  =   0;
        /**
        *   鼠标双击
        */
        virtual void    onMouseDbPress(int absx, int absy, MouseButton id) =   0;
        /**
        *   鼠标释放
        */
        virtual void    onMouseRelease(int absx, int absy, MouseButton id)  =   0;
        /**
        *   键盘按下
        */
        virtual void    onKeyPress(KeyCode key, int text)  =   0;
        /**
        *   键盘抬起
        */
        virtual void    onKeyRelease(KeyCode key)  =   0;
        /**
        *   输入
        */
        virtual void    onChar(int ch)  =   0;
    };

#endif // IGLINPUT_H
