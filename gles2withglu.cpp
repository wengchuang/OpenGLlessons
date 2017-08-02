#include "gles2withglu.h"
#include "gluwindowcallbacks.h"
#include <QDebug>
GLES2WithGLU::GLES2WithGLU(int argc ,char**argv)
{
    glutInit(&argc, argv);
}
int GLES2WithGLU::initWindows(){
    int ret ;
    int x ,y,width,height;
    this->getWindowInfo(&x ,&y,&width,&height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(x, y);
    glutInitWindowSize(width, height);
    glutCreateWindow(this->getTitle());


    ret =  glewInit();
    if(ret == 0){
        GLUWindowCallBacks::getInstance()->setUpdateFun<GLES2WithGLU,void>(this,&GLES2WithGLU::update);
        GLUWindowCallBacks::getInstance()->setResizeFun<GLES2WithGLU,void,int,int>(this,&GLES2WithGLU::onWindowsSizeChanaged);
    }
    return ret;
}

void GLES2WithGLU::onWindowsSizeChanaged(int width,int height){
    int x ,y,mWidth,mHeight;
    this->getWindowInfo(&x ,&y,&mWidth,&mHeight);
    this->setWidowsArea(x,y,width,height);
    this->update();
}
void GLES2WithGLU::onInputDeviceChanaged(IGLInput* input){
    GLUWindowCallBacks::getInstance()->setInput(input);

    return ;
}
int GLES2WithGLU::mainLoop(){
    glutMainLoop();
    return 0;
}


int GLES2WithGLU::onInitOpenGLES(){

    return 0;
}
void GLES2WithGLU::onDestroyOpenGLES(){
    return ;
}
