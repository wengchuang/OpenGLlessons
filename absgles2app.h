#ifndef ABSGLES2APP_H
#define ABSGLES2APP_H
#include "iglapp.h"
#include "iglesframegenerator.h"
#include "glesappcontext.h"
#include "string.h"
#include <QDebug>

class AbsGLES2App : public IGLApp
{
public:
    AbsGLES2App()
    {
        mX = 0;
        mY = 0;
        mWidth = 640;
        mHeight = 480;
        strncpy(mTitle,"GLES2AppIGLApp",sizeof(mTitle));
        //自定义的类 操作系统无关类
        esFrame = NULL;
        mCtx = NULL;
        generator = NULL;

    }
    inline void setWidowsArea(const int&x,const int&y,const int& width,const int& height ){
            mX = x;
            mY = y;
            mWidth = width;
            mHeight = height;
    }
    void setWindowsTitle(const char* title){
        strncpy(mTitle,title,sizeof(mTitle));
    }
    inline int setGLESFrameGenerator(IGLESFrameGenerator* ig){
        int ret = -1;
        GLESFrame* tmpFrame = NULL;
        if(esFrame != NULL){// system has been inited
            if(ig){
                tmpFrame = ig->generateGLESFrame();
                ret = tmpFrame->frameInit();
                if(!ret){
                    onInputDeviceChanaged(tmpFrame);
                    delete this->esFrame;
                    this->esFrame = tmpFrame;
                    this->generator =ig;
                }
            }
        }else{ //system has not init
            if(ig){
                ret = 0;
                //record generateor
                this->generator =ig;
            }else{
                ret = -1;
            }
        }
        return ret;

    }
    int exec();
    static GLESAppContext* getGLESAppContext();
    virtual ~AbsGLES2App();
protected:
    virtual int onInitOpenGLES() = 0;
    virtual void onDestroyOpenGLES() = 0;
    virtual int initWindows() = 0;
    virtual void onInputDeviceChanaged(IGLInput* input) = 0;
    //用于在子类更新界面的回调
    void update();
    virtual int mainLoop() = 0;

    inline  void getWindowInfo(int*x,int*y,int* width,int* height){
        *x = mX;
        *y = mY;
        *width = mWidth;
        *height = mHeight;
    }
    inline const char* getTitle()const{
        return mTitle;
    }
private:
    GLESAppContext* initAppcontext();
private:
    int mX ,mY,mWidth,mHeight;
    IGLESFrameGenerator* generator;
    GLESFrame* esFrame;
    static GLESAppContext* mCtx;
    char mTitle[32];
};

#endif // ABSGLES2APP_H
