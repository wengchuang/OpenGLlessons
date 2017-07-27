#include "windowadapter.h"
#include "mesh.h"
#include "trianglemesh.h"
#include "pyramidmesh.h"
#include <QDebug>
static Mesh* cusMesh = NULL;

static void display(void){
    if(cusMesh){
        cusMesh->onDraw();
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
    cusMesh = new PyramidMesh;
    return cusMesh->initData();
}
static int cusAdapterUninit(){
    delete cusMesh;
    return 0;
}

static WindowAdapter cusAdapter;

struct WindowAdapter*getWindowAdapter(){
    cusAdapter.adapterInit = cusAdapterInit;
    cusAdapter.adapterUninit = cusAdapterUninit;
    cusAdapter.getWindowEventCallBacks = getCusWindowEventCallBacks;

    return (WindowAdapter*)&cusAdapter;
}
