#ifdef UBUNTU_WITH_GL

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
        GLUWindowCallBacks::getInstance()->setResizeFun<GLES2WithGLU,void,const int&,const int&>(this,&GLES2WithGLU::resize);
    }
    return ret;
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
#endif
