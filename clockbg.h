#if 1
#ifndef CLOCKBG_H
#define CLOCKBG_H
#include "frameitem.h"
#include "visionnode.h"
#include "textureresource.h"

class ClockBg:public FrameItem
{
public:
    ClockBg(ShaderMap* shaderMap,FrameItem* parent = 0);
protected:
    void onDrawSelf(const Vision::FrameEvent&,const glm::mat4& pvMat);
private:
    Texture2dId             clockBg;
};

#endif // CLOCKBG_H
#endif
