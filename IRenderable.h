#ifndef IRENDERABLE_H
#define IRENDERABLE_H
#include "timerevent.h"
#include "glm/glm.hpp"
namespace Vision {
class IFrameRenderable{
public:
    virtual void onRender(const FrameEvent&) = 0;
    virtual void onRender(const int& width,const int& height,const FrameEvent&) = 0;
};
class IModelRenderable{
public:
    virtual void onRender(const FrameEvent&,const glm::mat4&) = 0;
};

}

#endif // IRENDERABLE_H
