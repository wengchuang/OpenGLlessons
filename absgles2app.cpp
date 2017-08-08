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
          mCtx = new GLESAppContext;
            if(mCtx != NULL){
                timerManger = mCtx->getTimerManagerResource();
                if(generator == NULL){
                    generator = new GLESFrameGenerator;
                }
                if(generator){
                    esFrame = generator->generateGLESFrame();
                    errCode = esFrame->frameInit(mWidth,mHeight);
                    if(!errCode){
                        onInputDeviceChanaged(esFrame);
                        errCode = mainLoop();
                    }
                    qDebug()<<"delete esFrame begin...............\n";
                    delete esFrame;
                    esFrame = NULL;
                    generator = NULL;
                    qDebug()<<"delete esFrame ...............\n";

                    delete mCtx;
                    mCtx = NULL;
                    qDebug()<<"delete mCtx...............\n";
                    onDestroyOpenGLES();
                    qDebug()<<"onDestroyOpenGLES()...............\n";
                    //while(1);
                }
            }
        }
    }
    return errCode;
}
void AbsGLES2App::resize(const int& width,const int&height){
    this->mWidth = width;
    this->mHeight = height;
    qDebug()<<"resize...";
    syncFrameTime();
    esFrame->onRender(mWidth,mHeight,_event);
}
void AbsGLES2App::update(){
    syncFrameTime();
    esFrame->onRender(_event);
}
GLESAppContext* AbsGLES2App::getGLESAppContext(){
    return mCtx;
}

void AbsGLES2App::syncFrameTime(){

    _event._frameTime  =   (float)_timestap.getElapsedSecond();
    _timestap.update();
    // 更新定时器

    qDebug()<<"elapsed time:"<<_event._frameTime;

    timerManger->update(_event._frameTime);
}

AbsGLES2App::~AbsGLES2App(){

}
