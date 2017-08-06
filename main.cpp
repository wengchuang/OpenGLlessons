#include <QDebug>
#include "windowadapter.h"
#include "windowsystem.h"

#include "iglapp.h"
#include "gles2withglu.h"
#include "shootingframe.h"
#ifdef WIN32_WITH_OPENGL_ES2
#pragma comment  (lib,"User32.lib")
#pragma comment  (lib,"Gdi32.lib")
#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include "wingles2app.h"
int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
    )
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);


    AllocConsole();
    freopen("conout$","w",stdout) ;
    printf("hello hplonline!-_-\n") ;
    std::cout<<"i'm cout"<<std::endl;
    freopen("conout$","w",stderr) ;
    std::cerr<<"i'm cerr"<<std::endl;

    WinGles2App* app = new WinGles2App(hInstance);
    app->setWidowsArea(600,100,400, 800);
    app->setWindowsTitle("ShootingApp");
    ShootingFrameGenerator* generator = new ShootingFrameGenerator;

    app->setGLESFrameGenerator(generator);
    app->exec();
    delete generator;
    delete app;
    return 0;
}
#else
int main(int argc,char*argv[])
{
#if 0
    WindowSystem* win = new WindowSystem(argc,argv,"OpenGL View Demo");
    if(win->windowInit(640, 480) != 0){
        qDebug()<<"init glew failed!";
        return  -1;
    }
    WindowAdapter*adapter = getWindowAdapter();
    adapter->adapterInit();
    win->setWindowCallBacks(adapter->getWindowEventCallBacks());
    win->exec();
    adapter->adapterUninit();
    delete win;
#endif
#ifdef UBUNTU_WITH_GL
    GLES2WithGLU* app = new GLES2WithGLU(argc,argv);
    app->setWidowsArea(600,100,400, 800);
    app->setWindowsTitle("ShootingApp");
    ShootingFrameGenerator* generator = new ShootingFrameGenerator;
    app->setGLESFrameGenerator(generator);
    app->exec();
    delete generator;
    delete app;
#endif

    return 0;
}
#endif
