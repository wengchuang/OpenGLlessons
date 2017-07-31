#ifndef IGLAPP_H
#define IGLAPP_H


//抽象app 屏蔽不同操作系统之间，窗口初始化的异同

class IGLApp{
public:
    virtual void setWidowsArea(const int&x,const int&y,const int& width,const int& height ) = 0;
    virtual void setWindowsTitle(const char* title) = 0;
    virtual int exec() = 0;
    virtual ~IGLApp(){}
};

#endif // IGLES2APP_H
