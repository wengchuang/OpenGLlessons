#ifndef PLAYER_H
#define PLAYER_H
#include "frameitem.h"
#include "visionnode.h"
#include "textureresource.h"
class player:public FrameItem
{
public:
    player(ShaderMap* shaderMap);
    void setPos(glm::vec3& pos);

    virtual void onRender(int width,int height,const glm::mat4& pvMat);
protected:
    virtual void onChar(int ch);
    virtual void onMousePress(int, int, MouseButton);
    virtual void onMouseRelease(int, int, MouseButton);
    virtual void onMouseMove(int, int, int);
private:
    Vision::VisionNode _nodeBody;
    Texture2dId        _plant;
    ShaderMap*         mShaderMap;
    bool               bLeftPress;

};

#endif // PLAYER_H
