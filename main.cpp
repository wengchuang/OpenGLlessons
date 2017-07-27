#include <QDebug>
#include "windowadapter.h"
#include "windowsystem.h"

int main(int argc,char*argv[])
{

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
    return 0;
}

