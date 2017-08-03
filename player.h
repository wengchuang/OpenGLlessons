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
private:
    Vision::VisionNode _nodeBody;
    Texture2dId        _plant;
    ShaderMap*         mShaderMap;

};

#endif // PLAYER_H
