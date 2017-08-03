#ifndef IRENDERABLE_H
#define IRENDERABLE_H
#include <stdio.h>
#include "glm/glm.hpp"
class IRenderable{
public:
    virtual void onRender(int width,int height) = 0;
};
class IModelRenderable{
public:
    virtual void onRender(int width,int height,const glm::mat4& pvMat) = 0;
};
#endif // IRENDERABLE_H
