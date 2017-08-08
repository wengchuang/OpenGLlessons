#ifndef CLOCKPOINTER_H
#define CLOCKPOINTER_H
#include "frameitem.h"
#include "visionnode.h"
#include "textureresource.h"

class ClockPointer:public FrameItem
{
public:
    ClockPointer(ShaderMap* shaderMap,FrameItem* parent = 0);
protected:
    void onDrawSelf(const Vision::FrameEvent&,const glm::mat4& pvMat);
private:
    Texture2dId             pointerBg;
};

#endif // CLOCKPOINTER_H
