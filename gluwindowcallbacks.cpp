#include "gluwindowcallbacks.h"
#if 0
FGAPI void    FGAPIENTRY glutKeyboardFunc( void (* callback)( unsigned char, int, int ) );
FGAPI void    FGAPIENTRY glutSpecialFunc( void (* callback)( int, int, int ) );
FGAPI void    FGAPIENTRY glutReshapeFunc( void (* callback)( int, int ) );
FGAPI void    FGAPIENTRY glutVisibilityFunc( void (* callback)( int ) );
FGAPI void    FGAPIENTRY glutDisplayFunc( void (* callback)( void ) );
FGAPI void    FGAPIENTRY glutMouseFunc( void (* callback)( int, int, int, int ) );
FGAPI void    FGAPIENTRY glutMotionFunc( void (* callback)( int, int ) );
FGAPI void    FGAPIENTRY glutPassiveMotionFunc( void (* callback)( int, int ) );
FGAPI void    FGAPIENTRY glutEntryFunc( void (* callback)( int ) );

FGAPI void    FGAPIENTRY glutKeyboardUpFunc( void (* callback)( unsigned char, int, int ) );
FGAPI void    FGAPIENTRY glutSpecialUpFunc( void (* callback)( int, int, int ) );
FGAPI void    FGAPIENTRY glutJoystickFunc( void (* callback)( unsigned int, int, int, int ), int pollInterval );
FGAPI void    FGAPIENTRY glutMenuStateFunc( void (* callback)( int ) );
FGAPI void    FGAPIENTRY glutMenuStatusFunc( void (* callback)( int, int, int ) );
FGAPI void    FGAPIENTRY glutOverlayDisplayFunc( void (* callback)( void ) );
FGAPI void    FGAPIENTRY glutWindowStatusFunc( void (* callback)( int ) );

FGAPI void    FGAPIENTRY glutSpaceballMotionFunc( void (* callback)( int, int, int ) );
FGAPI void    FGAPIENTRY glutSpaceballRotateFunc( void (* callback)( int, int, int ) );
FGAPI void    FGAPIENTRY glutSpaceballButtonFunc( void (* callback)( int, int ) );
FGAPI void    FGAPIENTRY glutButtonBoxFunc( void (* callback)( int, int ) );
FGAPI void    FGAPIENTRY glutDialsFunc( void (* callback)( int, int ) );
FGAPI void    FGAPIENTRY glutTabletMotionFunc( void (* callback)( int, int ) );
FGAPI void    FGAPIENTRY glutTabletButtonFunc( void (* callback)( int, int, int, int ) );
#endif

static void onDisplay(void){
    qDebug()<<"glutDisplayFunc....";
    GLUWindowCallBacks::getInstance()->update();
}
static void onResize(int width,int height){
    qDebug()<<"glutReshapeFunc....";
    GLUWindowCallBacks::getInstance()->resizeCallBack(width,height);

}
static void onKeyEvent(unsigned char, int, int ){

}
GLUWindowCallBacks *GLUWindowCallBacks::instance = NULL;
GLUWindowCallBacks::GLUWindowCallBacks()
{
 qDebug()<<"consturcting ...";
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onResize);
    glutKeyboardFunc(onKeyEvent);

}
GLUWindowCallBacks* GLUWindowCallBacks::getInstance(){
    if(!instance){
        qDebug()<<"getinstance ...";
        instance = new GLUWindowCallBacks;
    }
    return instance;
}
