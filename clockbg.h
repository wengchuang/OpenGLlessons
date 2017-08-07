#ifndef CLOCKBG_H
#define CLOCKBG_H
#include "frameitem.h"
#include "visionnode.h"
#include "textureresource.h"
class ClockBg:public FrameItem
{
public:
    ClockBg(ShaderMap* shaderMap);
    virtual void onRender(const Vision::FrameEvent&,const glm::mat4& pvMat);
private:
    Texture2dId             clockBg;
    Texture2dId             pointerBg;
    Vision::VisionNode      _nodeBody;
    Vision::VisionNode      _pointerBody;
};

#endif // CLOCKBG_H
