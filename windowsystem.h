#ifndef WINDOWSYSTEM_H
#define WINDOWSYSTEM_H
#include <QString>
#include "windowadapter.h"

struct WindowEventCallBacks{
    void (*onDisplay)(void);
    void (*onResize)(int width,int height);
    void (*onKeyEvent)(unsigned char, int, int );
};

class WindowSystem
{
public:
    WindowSystem(int argc,char*argv[],const char* winTitle);
    int windowInit(const int& width,const int&height);
    void setWindowCallBacks(WindowEventCallBacks* callbacks);
    int exec();
private:
    QString title;
    WindowEventCallBacks* callBacks;
};

#endif // WINDOWSYSTEM_H
