#include "windowadapter.h"
#include "trianglerender.h"
#include "pyramidrender.h"
#include "prismrender.h"
#include "baserender.h"
#include "mesh.h"
#include <QDebug>
static Mesh* cusMesh = NULL;
static BaseRender* mRender = NULL;


static void display(void){
    if(cusMesh){
        cusMesh->update();
    }

}
static void shapeFun(int width,int height){
    if(cusMesh){
        cusMesh->onSurfaceChanaged(width,height);
    }

}
void keyEvent(unsigned char c, int code1, int code2 ){
    Q_UNUSED(code1);
    Q_UNUSED(code2);
    if(cusMesh){
        switch(c){
        case 'a':
        case 'A':
            cusMesh->roteZf(-10.0f);
            break;
        case 'd':
        case 'D':
            cusMesh->roteZf(10.0f);
            break;

        case 'w':
        case 'W':
            cusMesh->transYf(.1f);
            break;

        case 's':
        case 'S':
            cusMesh->transYf(-.1f);
            break;

        case 'z':
        case 'Z':
            cusMesh->scaleXf(1.5f);
            break;
        case 'x':
        case 'X':
            cusMesh->scaleXf(0.5f);
            break;
        }

        cusMesh->update();
    }
}
static struct WindowEventCallBacks callBacks;
struct WindowEventCallBacks* getCusWindowEventCallBacks(void){
    callBacks.onDisplay     = display;
    callBacks.onResize      = shapeFun;
    callBacks.onKeyEvent    = keyEvent;
    return &callBacks;
}

static int cusAdapterInit(){


    mRender = new PrismRender;
    qDebug()<<"cusAdapterInit...\n";

    cusMesh = new Mesh(mRender);
    qDebug()<<"cusAdapterInit end \n";

    return cusMesh->meshInit();
}
static int cusAdapterUninit(){
    delete cusMesh;
    delete mRender;
    return 0;
}

static WindowAdapter cusAdapter;

struct WindowAdapter*getWindowAdapter(){
    cusAdapter.adapterInit = cusAdapterInit;
    cusAdapter.adapterUninit = cusAdapterUninit;
    cusAdapter.getWindowEventCallBacks = getCusWindowEventCallBacks;

    return (WindowAdapter*)&cusAdapter;
}
