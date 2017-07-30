#ifndef ABSGLES2APP_H
#define ABSGLES2APP_H
#include "iglapp.h"
#include "glesframe.h"
#include "glesappcontext.h"
#include "string.h"
class AbsGLES2App : public IGLApp
{
public:
    AbsGLES2App(int argc ,char**argv,unsigned int platdata= 0):
        IGLApp(argc ,argv,platdata= 0)
    {
        mX = 0;
        mY = 0;
        mWidth = 640;
        mHeight = 480;
        strncpy(mTitle,"GLES2AppIGLApp",sizeof(mTitle));
        //自定义的类 操作系统无关类
        esFrame = NULL;
        mCtx = NULL;

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
    int exec();
    static GLESAppContext* getGLESAppContext();
    virtual ~AbsGLES2App();
protected:
    virtual int onInitOpenGLES() = 0;
    virtual void onDestroyOpenGLES() = 0;

    virtual GLESFrame* onCreateGLESFrame() = 0;
    virtual void registerSupportEvents(IGLInput* input) = 0;
    virtual int initWindows() = 0;
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
    GLESFrame* esFrame;
    static GLESAppContext* mCtx;
    char mTitle[32];
};

#endif // ABSGLES2APP_H
