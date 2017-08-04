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
    void setPos(glm::vec3& pos);
    virtual void onRender(int width,int height,const glm::mat4& pvMat);
    void addBullet();
    ~player();
protected:
    virtual void onChar(int ch);
    virtual void onMousePress(int, int, MouseButton);
    virtual void onMouseRelease(int, int, MouseButton);
    virtual void onMouseMove(int, int, int);
private:
    void renderChildren(const glm::mat4& pvMat);
private:
    typedef std::vector<Bullet*>   BulletList;
    Vision::VisionNode _nodeBody;
    Texture2dId        _plant;
    ShaderMap*         mShaderMap;
    bool               bLeftPress;
    BulletList         bulletList;
    Timer              *mTimer;
    int                 times;

};

#endif // PLAYER_H
