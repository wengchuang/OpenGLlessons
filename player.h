#ifndef PLAYER_H
#define PLAYER_H
#include "frameitem.h"
#include "visionnode.h"
#include "textureresource.h"
#include "bullet.h"
#include <vector>
#include "timer.h"
class player:public FrameItem
{
public:
    player(ShaderMap* shaderMap);
    inline void setPos(glm::vec3& pos){
        _nodeBody.setPosition(pos);
    }
    virtual void onRender(const Vision::FrameEvent&,const glm::mat4& pvMat);
    int addBullet(Vision::VisionTimer* timer,const float& elapsed);
    ~player();
protected:
    virtual void onChar(int ch);
    virtual void onMousePress(int, int, MouseButton);
    virtual void onMouseRelease(int, int, MouseButton);
    virtual void onMouseMove(int, int, int);
private:
    void renderChildren(const Vision::FrameEvent&_event,const glm::mat4& pvMat);
private:
    typedef std::vector<Bullet*>   BulletList;
    Vision::VisionNode      _nodeBody;
    Texture2dId             _plant;
    ShaderMap*              mShaderMap;
    bool                    bLeftPress;
    BulletList              bulletList;
    Vision::VisionTimer*     mTimer;
};

#endif // PLAYER_H
