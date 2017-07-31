#ifndef IRENDERABLE_H
#define IRENDERABLE_H
#include <stdio.h>
class IRenderable{
public:
    virtual void onRender(int width,int height,void*usrData=NULL) = 0;
};
#endif // IRENDERABLE_H
