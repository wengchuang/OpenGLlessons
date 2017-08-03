#include "absgles2app.h"
#include "glesframegenerator.h"
#include <QDebug>
GLESAppContext*AbsGLES2App::mCtx =NULL;

int AbsGLES2App::exec(){
    int errCode = -1;
    errCode =  initWindows();
    if(!errCode){
        errCode = onInitOpenGLES();
        if(!errCode){
            mCtx = initAppcontext();
            if(mCtx != NULL){
                if(generator == NULL){
                    generator = new GLESFrameGenerator;
                }
                if(generator){
                    esFrame = generator->generateGLESFrame();
                    errCode = esFrame->frameInit();
                    if(!errCode){
                        onInputDeviceChanaged(esFrame);
                        errCode = mainLoop();
                    }
                    delete esFrame;
                    delete mCtx;
                    onDestroyOpenGLES();
                }
            }
        }
    }
    return errCode;
}
void AbsGLES2App::update(){
    esFrame->onRender(mWidth,mHeight);
}
GLESAppContext* AbsGLES2App::getGLESAppContext(){
    return mCtx;
}
GLESAppContext* AbsGLES2App::initAppcontext(){
    if(mCtx == NULL){
        mCtx = new GLESAppContext;
    }
    return mCtx;
}
AbsGLES2App::~AbsGLES2App(){

}
