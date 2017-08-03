#include "gluwindowcallbacks.h"
#include "iglinput.h"
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
GLUWindowCallBacks *gInstance = NULL;
static void onDisplay(void){
    gInstance->update();
}
static void onResize(int width,int height){
    gInstance->resizeCallBack(width,height);
}

static void onKeyEvent(unsigned char ch, int, int ){
    IGLInput* mInput = gInstance->getInput();
    if(mInput){
        mInput->onChar(ch);
    }

}
static MouseButton BtnId(MouseButton::None);
static void mouseFunCb(int button, int state, int x, int y){
    IGLInput* mInput = gInstance->getInput();

    switch (button) {
    case GLUT_LEFT_BUTTON:
        BtnId = MouseButton(MouseButton::Left);
        break;
    case GLUT_RIGHT_BUTTON:
        BtnId = MouseButton(MouseButton::Right);
    default:
        break;
    }


    if(BtnId.toValue() != MouseButton::None){
        switch (state) {
        case GLUT_DOWN:
            mInput->onMousePress(x, y,BtnId);
            break;
        case GLUT_UP:
            mInput->onMouseRelease(x, y,BtnId);
            BtnId = MouseButton(MouseButton::None);
            break;
        default:
            break;
        }
    }
}
static void mouseMotionCB(int x, int y){
    if(BtnId.toValue() != MouseButton::None){
       IGLInput* mInput = gInstance->getInput();
       mInput->onMouseMove(x,y,0);
    }

}
GLUWindowCallBacks *GLUWindowCallBacks::instance = NULL;
GLUWindowCallBacks::GLUWindowCallBacks()
{
    glutDisplayFunc(onDisplay);
    glutReshapeFunc(onResize);
    glutKeyboardFunc(onKeyEvent);
    glutMouseFunc(mouseFunCb);
    glutMotionFunc(mouseMotionCB);
    mInput = NULL;

}
GLUWindowCallBacks* GLUWindowCallBacks::getInstance(){
    if(!instance){
        instance = new GLUWindowCallBacks;
        gInstance = instance;
    }
    return instance;
}
