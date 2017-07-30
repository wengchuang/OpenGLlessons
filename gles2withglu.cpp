#include "gles2withglu.h"
#include <GL/glew.h>
#include <GL/glut.h>

GLES2WithGLU::GLES2WithGLU(int argc ,char**argv,unsigned int platdata):
    AbsGLES2App(argc ,argv,platdata)
{
    glutInit(&argc, argv);
}
int GLES2WithGLU::initWindows(){
    int x ,y,width,height;
    this->getWindowInfo(&x ,&y,&width,&height);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(x, y);
    glutInitWindowSize(width, height);
    glutCreateWindow(this->getTitle());
    return glewInit();
}
int GLES2WithGLU::onInitOpenGLES(){

    return 0;
}
void GLES2WithGLU::onDestroyOpenGLES(){
    return ;
}
GLESFrame* GLES2WithGLU::onCreateGLESFrame(){
   return  new GLESFrame();
}

void GLES2WithGLU::registerSupportEvents(IGLInput* input){
    //glutKeyboardFunc(input->onKeyPress);
    return ;
}
int GLES2WithGLU::mainLoop(){
    glutMainLoop();
    return 0;
}
