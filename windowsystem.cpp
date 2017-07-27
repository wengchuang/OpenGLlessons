#include "windowsystem.h"
#include <GL/glew.h>
#include <GL/glut.h>

WindowSystem::WindowSystem(int argc,char*argv[],const char* winTitle)
{
    glutInit(&argc, argv);
    this->title = QString(winTitle);
}
int WindowSystem::windowInit(const int& width,const int&height){
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(600, 300);
    glutInitWindowSize(width, height);
    glutCreateWindow(title.toLocal8Bit().data());
    return glewInit();
}
void WindowSystem::setWindowCallBacks(WindowEventCallBacks* callbacks){
    this->callBacks = callbacks;
    if(callbacks->onDisplay)
        glutDisplayFunc(callbacks->onDisplay);
    if(callbacks->onResize)
        glutReshapeFunc(callbacks->onResize);
    if(callbacks->onKeyEvent)
        glutKeyboardFunc(callbacks->onKeyEvent);
}
int WindowSystem::exec(){
    glutMainLoop();
    return 0;
}
