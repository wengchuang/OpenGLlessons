#include "absgles2app.h"
GLESAppContext*AbsGLES2App::mCtx =NULL;

int AbsGLES2App::exec(){
    int errCode = 0;
    errCode =  initWindows();
    if(!errCode){
       errCode = onInitOpenGLES();
        if(!errCode){
            mCtx = initAppcontext();
            if(mCtx != NULL){
                if(esFrame = onCreateGLESFrame()){
                    if(esFrame != NULL){
                        registerSupportEvents(esFrame);
                        return mainLoop();
                        delete esFrame;
                        delete mCtx;
                        onDestroyOpenGLES();
                    }
                }
            }
        }
    }
}
void AbsGLES2App::update(){
    esFrame->onRender();
}
GLESAppContext* AbsGLES2App::getGLESAppContext(){
    return mCtx;
}
GLESAppContext* AbsGLES2App::initAppcontext(){
    return new GLESAppContext;
}
AbsGLES2App::~AbsGLES2App(){

}
