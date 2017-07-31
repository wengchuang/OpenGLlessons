#include <QDebug>
#include "windowadapter.h"
#include "windowsystem.h"

#include "iglapp.h"
#include "gles2withglu.h"
#include "shootingframe.h"

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
#if 1
    GLES2WithGLU* app = new GLES2WithGLU(argc,argv);
    app->setWidowsArea(600,150,640, 480);
    ShootingFrameGenerator* generator = new ShootingFrameGenerator;
    app->setGLESFrameGenerator(generator);
    app->exec();
    delete generator;
    delete app;
#endif
    return 0;
}

