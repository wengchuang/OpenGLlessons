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
    player(ShaderMap* shaderMap,FrameItem*parent = 0);
    inline void setPos(glm::vec3& pos){
        this->setpos(pos);
    }
    int addBullet(Vision::VisionTimer* timer,const float& elapsed);
    ~player();
protected:
    void onDrawSelf(const Vision::FrameEvent&,const glm::mat4& pvMat);
    void drawBullets(const Vision::FrameEvent&_event,const glm::mat4& pvMat);
    virtual void onChar(int ch);
    virtual void onMousePress(int, int, MouseButton);
    virtual void onMouseRelease(int, int, MouseButton);
    virtual void onMouseMove(int, int, int);
private:
    std::vector<Bullet*>    bulletList;
    Texture2dId             _plant;
    bool                    bLeftPress;
    Vision::VisionTimer*     mTimer;
};

#endif // PLAYER_H
