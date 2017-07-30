#include <QDebug>
#include "windowadapter.h"
#include "windowsystem.h"

#include "iglapp.h"
#include "gles2withglu.h"

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
    IGLApp* app = new GLES2WithGLU(argc,argv);
    app->exec();
    delete app;

    return 0;
}

