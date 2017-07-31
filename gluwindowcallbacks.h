#ifndef GLUWINDOWCALLBACKS_H
#define GLUWINDOWCALLBACKS_H
#include <GL/glew.h>
#include <GL/glut.h>
#include "iglinput.h"
#include "delegate.hpp"
#include <QDebug>

class GLUWindowCallBacks
{
private:
    GLUWindowCallBacks();
public:
    static GLUWindowCallBacks* getInstance();
    inline void setInput(IGLInput* input){
        this->mInput = input;
    }
    void update(){
        mUpdateDelegate();
    }
    inline IGLInput*getInput(){
        return mInput;
    }
    template<typename T,typename R>
    inline void setUpdateFun(T*object, R (T::*method)()){
        mUpdateDelegate.bind(object,method);
    }
    template<typename T,typename R,typename A1,typename A2>
    inline void setResizeFun(T* object, R (T::*method)( A1,A2 )){
        mResizeFun.bind(object,method);
    }
    inline void resizeCallBack(int width,int height){
        mResizeFun(width,height);
    }
private:
    IGLInput* mInput;
    Delegate<void> mUpdateDelegate;
    Delegate2<void,int,int> mResizeFun;
    static GLUWindowCallBacks* instance;
};

#endif // GLUWINDOWCALLBACKS_H
