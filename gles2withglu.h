#ifndef GLES2WITHGLU_H
#define GLES2WITHGLU_H
#include "absgles2app.h"

class GLES2WithGLU : public AbsGLES2App
{
public:
    GLES2WithGLU(int argc ,char**argv,unsigned int platdata= 0);
protected:
    int initWindows();
    int onInitOpenGLES();
    void onDestroyOpenGLES();
    GLESFrame* onCreateGLESFrame();
    void registerSupportEvents(IGLInput* input);
    int mainLoop();
};

#endif // GLES2WITHGLU_H
